/************************
 * FILE: optimize.cpp
 * AUTHOR: Haoyuan Sun
 * Date: July, 2018
 ************************/

#include <map>
#include "optimize.hpp"
#include "fraction.hpp"

optimize::optimize(data_store& td) : test_data(td) {}

void optimize::set_dim (int n, const vector<bool>& v) {
    ndim = n;
    vdim = v;
}

void optimize::run (int type, fraction& frac, vector<double>& coeff) {
    switch(type) {
        case 1:
            nelder_mead(frac, coeff);
            break;
        default:
            break;
    }
}

double optimize::eval_fit(fraction& frac, vector<double>& coeff, 
        const vector<double>& vars) {
    int k = 0;
    for(size_t i = 0; i < coeff.size(); ++i) {
        if (vdim[i]) coeff[i] = vars[k++];
        else coeff[i] = 0;
    }
    
    return test_data.eval_fit(frac);
}

void optimize::nelder_mead (fraction& frac, vector<double>& coeff) {
    using coord = vector<double>;

    auto add = [this](const coord& a, const coord& b) -> coord {
        coord ret;
        for(int i = 0; i < ndim; ++i)
            ret.push_back(a[i] + b[i]);
        return ret;
    };
    auto sub = [this](const coord& a, const coord& b) -> coord {
        coord ret;
        for(int i = 0; i < ndim; ++i)
            ret.push_back(a[i] - b[i]);
        return ret;
    };
    auto mul = [this](double c, const coord& a) -> coord {
        coord ret;
        for(int i = 0; i < ndim; ++i)
            ret.push_back(c * a[i]);
        return ret;
    };

    std::multimap<double, coord, std::greater<double>> simplex;

    coord tmp = coord(0);
    for(size_t i = 0; i < coeff.size(); ++i) {
        if(vdim[i]) tmp.push_back(coeff[i]);
    }
    
    coord cent = tmp;
    for(int i = 0; i < ndim; ++i)
        cent[i] += 2.0/(ndim + 1);

    for(int i = 0; i <= ndim; ++i) {
        simplex.insert({eval_fit(frac, coeff, tmp), tmp});
        if(i > 0) tmp[i-1] -= 2;
        if(i < ndim) tmp[i] += 2;
    }

    int num = 0;
    while (simplex.begin()->first - (--simplex.end())->first > 1
           && num < 100) {
        auto vw = simplex.begin();
        coord vtmp = sub(cent, vw->second);
        coord vnew;

        if(eval_fit(frac, coeff, add(cent, vtmp)) < vw->first) {
            if(eval_fit(frac, coeff, add(cent, mul(2, vtmp))) < 
                    eval_fit(frac, coeff, cent))
                vnew = add(cent, mul(1.375, vtmp));
            else vnew = add(cent, vtmp);
        }
        else vnew = sub(cent, mul(0.625, tmp));

        cent = add(cent, mul(1.0/(ndim+1), sub(vnew, vw->second)));
        simplex.erase(vw);
        simplex.insert({eval_fit(frac, coeff, vnew), vnew});

        ++num;
    }

    eval_fit(frac, coeff, (--simplex.end())->second);
}
