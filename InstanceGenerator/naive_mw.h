//
//  naive_mw.h
//  InstanceGenerator
//
//  Created by Dragos Ciocan on 5/26/13.
//  Copyright (c) 2013 Dragos Ciocan. All rights reserved.
//

#ifndef __InstanceGenerator__naive_mw__
#define __InstanceGenerator__naive_mw__

#include <cmath>
#include <ext/hash_map>
#include <fstream>
#include <iostream>
#include <vector>

#include "instance.h"

using namespace std;

struct KnapsackRatio {
    long double ratio;
    long double coefficient;
    int impression_index;
    int advertiser_index;
    
    bool operator <(const KnapsackRatio &r) const {
        return ratio > r.ratio;
    }
};

namespace distributed_solver {
class NaiveMW {
    int num_impressions_;
    int num_advertisers_;
    long double bid_sparsity_;
    long double max_bid_;
    long double advertiser_indegree_;
    long double epsilon_;
    long double width_;
    int num_iterations_;
    vector<long double> impression_weights_, advertiser_weights_;
    vector<long double> impression_slacks_, advertiser_slacks_;
    vector<long double> impression_avg_slacks_, advertiser_avg_slacks_;
    vector<KnapsackRatio> ratios_;
    long double weighted_budget_;
    vector<long double>* budgets_;
    vector<__gnu_cxx::hash_map<int, pair<long double, long double> > >* solution_;
    vector<__gnu_cxx::hash_map<int, long double> >* bids_matrix_;
    vector<__gnu_cxx::hash_map<int, long double> >* transpose_bids_matrix_;

public:
    NaiveMW(int num_impressions, int num_advertisers, long double max_bid,
            long double epsilon, long double width, long double bid_sparsity,
            vector<__gnu_cxx::hash_map<int, pair<long double, long double> > >* solution,
            vector<__gnu_cxx::hash_map<int, long double> >* bids_matrix,
            vector<__gnu_cxx::hash_map<int, long double> >* transpose_bids_matrix,
            vector<long double>* budgets);
    void NaiveMWPrimal();
    void CreateRatios();
    void UpdateRatios();
    void RunNaiveMW(int num_iterations);
    
private:
    void UpdateWeightedBudget();
    void UpdateAdvertiserWeights();
    void UpdateImpressionWeights();
    void UpdateAdvertiserSlacks();
    void UpdateImpressionSlacks();
    void ResetPrimal();
    void UpdateAvgSlacks(int t);
    void ReportWorstInfeasibility(int t);
    void CalculateRevenue();
};
}

#endif /* defined(__InstanceGenerator__naive_mw__) */
