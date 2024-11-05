// --------------------------------------------------------------------- //
// For part B, you will need to modify this file.                        //
// You may add any code you need, as long as you correctly implement the //
// three required BPred methods already listed in this file.             //
// --------------------------------------------------------------------- //

// bpred.cpp
// Implements the branch predictor class.

#include "bpred.h"
#include <iostream>

/**
 * Construct a branch predictor with the given policy.
 * 
 * In part B of the lab, you must implement this constructor.
 * 
 * @param policy the policy this branch predictor should use
 */
BPred::BPred(BPredPolicy policy)
{
    // TODO: Initialize member variables here.
    // As a reminder, you can declare any additional member variables you need
    // in the BPred class in bpred.h and initialize them here.

    /* initialize branch policy*/
    this->policy = policy;

    /* initialize GHR and PHT */
    GHR = 0;
    for (int i = 0; i < 4096; i++) {
        PHT[i] = 2;
    }

}

/**
 * Get a prediction for the branch with the given address.
 * 
 * In part B of the lab, you must implement this method.
 * 
 * @param pc the address (program counter) of the branch to predict
 * @return the prediction for whether the branch is taken or not taken
 */
BranchDirection BPred::predict(uint64_t pc)
{
    // TODO: Return a prediction for whether the branch at address pc will be
    // TAKEN or NOT_TAKEN according to this branch predictor's policy.

    // Note that you do not have to handle the BPRED_PERFECT policy here; this
    // function will not be called for that policy.

    /* if its BPRED_GSHARE */
    if (policy == BPRED_GSHARE) {
        return PHT[(pc ^ GHR) & 0x0FFF] >= 2 ? TAKEN : NOT_TAKEN;
    }

    /* if its BPRED_PERFECT */
    return TAKEN;

}


/**
 * Update the branch predictor statistics (stat_num_branches and
 * stat_num_mispred), as well as any other internal state you may need to
 * update in the branch predictor.
 * 
 * In part B of the lab, you must implement this method.
 * 
 * @param pc the address (program counter) of the branch
 * @param prediction the prediction made by the branch predictor
 * @param resolution the actual outcome of the branch
 */
void BPred::update(uint64_t pc, BranchDirection prediction,
                   BranchDirection resolution)
{
    // TODO: Update the stat_num_branches and stat_num_mispred member variables
    // according to the prediction and resolution of the branch.

    /* update branch count */
    stat_num_branches++;

    /* update mispredicted count */
    if (prediction != resolution) {
        stat_num_mispred++;
    }

    if (policy == BPRED_GSHARE) {
        /* get PHT index */
        int pht_index = (pc ^ GHR) & 0x0FFF;

        /* update PHT counter */
        if (resolution == TAKEN) {
            PHT[pht_index] = sat_increment(PHT[pht_index], 3);
        } else if (resolution == NOT_TAKEN) {
            PHT[pht_index] = sat_decrement(PHT[pht_index]);
        }

        /* update GHR */
        GHR = (GHR << 1) | (resolution & 1);
    }



    // TODO: Update any other internal state you may need to keep track of.

    // Note that you do not have to handle the BPRED_PERFECT policy here; this
    // function will not be called for that policy.
}
