#include "apriori.h"

// Support = Transactions including item A / Total transactions
float calculateSupport(TrieNode *root, const char *itemName, int totalTransactions){
    float support;
    int transactionsCount;
    while (root != NULL){
        if (root->name == itemName){
            transactionsCount += 1;
            
        }

    }
    return support;
}