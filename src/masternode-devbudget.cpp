// Copyright (c) 2018-2019 The Digi Dinar Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <masternode-devbudget.h>

CDevBudget devbudget;

void CDevBudget::PrepareBudget() {
    CBitcoinAddress address = CBitcoinAddress(Params().BonusPoolAddress());
    payee = GetScriptForDestination(address.Get());

    LogPrint("debug","CDevBudget::PrepareBudget(): %s\n", address.ToString());
}

bool CDevBudget::IsTransactionValid(const CTransaction& txNew, int nBlockHeight)
{
    PrepareBudget();

    CBlockIndex* pindexPrev = chainActive.Tip();
    if (!pindexPrev){
        return false;
    }

    if(txNew.IsZerocoinSpend()){
        return true;
    }

    CAmount blockreward = GetBlockValue(pindexPrev->nHeight);
    CAmount budgetPayment = GetDevelopersPayment(pindexPrev->nHeight, blockreward);

    bool found = false;
    int i = 0;
    if(budgetPayment > 0){
        BOOST_FOREACH (CTxOut out, txNew.vout) {
            if (payee == out.scriptPubKey) {
                if (i > 0 && out.nValue >= budgetPayment) {
                    found = true;
                }
                else{
                    LogPrintf("CDevBudget::IsTransactionValid - Found valid Dev Budget address, but nHeight:%d amount %d expected:%d\n", pindexPrev->nHeight, out.nValue, budgetPayment);
                }
            }
            i++;
        }
    }
    else{
        LogPrint("debug","CDevBudget::IsTransactionValid - Skipping validate devbudget, because is 0\n");
        found = true;
    }

    if (!found) {
        LogPrint("debug","CDevBudget::IsTransactionValid - Missing required payment %d for block %d\n", budgetPayment, pindexPrev->nHeight);
    }

    return found;
}

void CDevBudget::FillBlockPayee(CMutableTransaction& txNew, int64_t nFees, bool fProofOfStake)
{
    LogPrint("debug","Entered in CDevBudget::FillBlockPayee\n");

    CBlockIndex* pindexPrev = chainActive.Tip();
    if (!pindexPrev){
        return;
    }

    PrepareBudget();

    unsigned int i = txNew.vout.size();

    if(fProofOfStake && i > 1 && txNew.vout[1].IsZerocoinMint()){
        return;
    }

    if (txNew.vout[i - 1].nValue > 0) {
        CAmount blockreward = GetBlockValue(pindexPrev->nHeight);
        CAmount budgetPayment = GetDevelopersPayment(pindexPrev->nHeight, blockreward);

        if(budgetPayment > 0) {
            txNew.vout.resize(i + 1);
            txNew.vout[i].scriptPubKey = payee;
            txNew.vout[i].nValue = budgetPayment;

            //subtract budget payment from mn reward
            txNew.vout[i - 1].nValue -= budgetPayment;

            LogPrint("debug","Dev budget payment of %s to %s\n", FormatMoney(budgetPayment).c_str(), Params().BonusPoolAddress().c_str());
        }
        else{
            LogPrint("debug","Dev budget payment equals 0\n");
        }
    }
    else{
        LogPrint("debug","Can't insert dev budget payment: vout value equals 0\n");
    }
}
