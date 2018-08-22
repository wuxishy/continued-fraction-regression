/************************
 * FILE: optimize.cpp
 * AUTHOR: Haoyuan Sun
 * Date: July, 2018
 ************************/

// performing local search

#include "optimize.hpp"

#include "eval.hpp" 

#include <map>

#include <cmath>

#include <iostream>

optimize::optimize(data_store& td, fraction& f) : 
        test_data(td), frac(f) {
    buf = frac; 

    ndim = 1;
    var_map.push_back({0, 0}); //for convenience
    for(size_t i = 0; i < frac.repr.size(); ++i) {
        for(size_t j = 0; j < frac.repr[i].coeff.size(); ++j) {
            if(frac.repr[i].feature[j]) {
                ++ndim;
                var_map.push_back({i, j});
            }
        }
    }
}

double optimize::run (int type) {
    switch(type) {
        case 1:
            return nelder_mead();
        default:
            return 0;
    }
}

double optimize::eval_fit(const vector<double>& vec) {
    buf.constant = vec[0];
    for(int i = 1; i < ndim; ++i) {
        pii& pos = var_map[i];
        buf.repr[pos.first].coeff[pos.second] = vec[i];
    }
    evaluator e(test_data);

    return e.eval_fit(buf);
    /*
    using std::sin;
    using std::pow;
    return pow(sin(3*M_PI*vec[0]),2)+pow(vec[0]-1, 2)*(1+pow(sin(3*M_PI*vec[1]),2))+pow(vec[1]-1, 2)*(1+pow(sin(2*M_PI*vec[1]),2));
    */
}

// simplified nelder mead for speed
double optimize::nelder_mead () {
    using coord = vector<double>;
    
    // simplex operations
    auto refl = [this](const coord& a, const coord& b) {
        coord ret(ndim);
        for(int i = 0; i < ndim; ++i) {
            ret[i] = 2 * a[i] - b[i];
        }
        return ret;
    };
    
    auto expa = [this](const coord& a, const coord& b) {
        coord ret(ndim);
        for(int i = 0; i < ndim; ++i) {
            ret[i] = 3 * a[i] - 2 * b[i];
        }
        return ret;
    };
    
    auto contr = [this](const coord& a, const coord& b) {
        coord ret(ndim);
        for(int i = 0; i < ndim; ++i) {
            ret[i] = 0.5 * (a[i] + b[i]);
        }
        return ret;
    };


    // centroid;
    coord cent(ndim);
    double cent_fit;
    // simplex, ordered from worst to best
    std::multimap<double, coord, std::greater<double>> simplex;

    // http://www.scholarpedia.org/article/Nelder-Mead_algorithm#Initial_simplex
    double step = 0.5;
    coord tmp(ndim);
    tmp[0] = frac.constant;
    for(int i = 1; i < ndim; ++i) {
        pii& pos = var_map[i];
        tmp[i] = frac.repr[pos.first].coeff[pos.second];
    }
    simplex.insert({eval_fit(tmp), tmp});

    for(int i = 0; i < ndim; ++i) {
        tmp[i] += step;
        simplex.insert({eval_fit(tmp), tmp});
        tmp[i] -= step;
    }

    for (int i = 0; i < ndim; ++i) {
        cent[i] = 0;
        for (auto it = ++simplex.begin(); it != simplex.end(); ++it)
            cent[i] += it->second[i] / ndim;
    }
    cent_fit = eval_fit(cent);

    // either converge, or reach max number of iterations
    int iter = 0;
    while(simplex.begin()->first - (--simplex.end())->first > 1e-3
            && iter < 5000 ) {

        for(auto it = simplex.begin(); it != simplex.end(); ++it) {
            std::cerr << it->first << '\n';
            for(int i = 0; i < ndim; ++i)
                std::cerr << it->second[i] << ' ';
            std::cerr << '\n';
        }
        std::cerr << cent_fit << '\n';
        for(int i = 0; i < ndim; ++i)
            std::cerr << cent[i] << ' ';
        std::cerr << '\n';
        std::cerr << '\n';

        coord& vw = simplex.begin()->second;
        double vw_fit = simplex.begin()->first;
        coord& vsw = (++simplex.begin())->second;
        double vsw_fit = (++simplex.begin())->first;
        coord& vb = (--simplex.end())->second;

        coord vr = refl(cent, vw);
        double vr_fit = eval_fit(vr);
        coord ve = expa(cent, vw);

        coord vtmp;
        if (vr_fit < vw_fit) {
            if(eval_fit(ve) < cent_fit) {
                if(vr_fit < cent_fit)
                    vtmp = contr(vr, ve);
                else 
                    vtmp = contr(refl(cent, vr), cent);
            }
            else 
                vtmp = cent;

            vtmp = contr(contr(vtmp, cent), ve);
        }
        else {
            if (vsw_fit < cent_fit)
                vtmp = vb;
            else
                vtmp = cent;

            if (eval_fit(contr(refl(cent, ve), contr(vtmp, cent))) 
                    < cent_fit)
                vtmp = refl(cent, vr);
            else
                vtmp = cent;

            if (eval_fit(vtmp) < cent_fit)
                vtmp = vr;
            else
                vtmp = contr(cent, vw);

            vtmp = contr(vw, contr(vtmp, cent));
        }

        // replace the worst
        simplex.erase(simplex.begin());
        simplex.insert({eval_fit(vtmp), vtmp});

        // recompute the centroid
        for (int i = 0; i < ndim; ++i) {
            cent[i] = 0;
            for (auto it = ++simplex.begin(); it != simplex.end(); ++it)
                cent[i] += it->second[i] / ndim;
        }
        cent_fit = eval_fit(cent);

        ++iter;
    }
    std::cerr << iter << '\n';
    //if (iter >= 10000) std::cerr << "RICH!!!\n";

    double ret = eval_fit((--simplex.end())->second);
    // now buf contains the best
    frac = buf;
    //for(func& f : frac.repr) f.find_feature();
      
    /*
    std::cout << (--simplex.end())->first << '\n';
    for(int i = 0; i < ndim; ++i)
        std::cout << (--simplex.end())->second[i] << ' ';
    std::cout << '\n';
    */
    
    evaluator e(test_data);
    return e.adjust_fit(frac, ret);
}
