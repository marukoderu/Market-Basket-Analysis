#include "apriori.h"
#include "linkedlist.h"
#include <string.h>

// Support = Transactions including item A / Total transactions
float calculateSupport(transactionsNode *root, const char itemName[]) {
    float support;
    int transactionsCount = 0, itemCount = 0;
    transactionsNode *currentNode = root;

    // Cek apakah ada transaksi atau tidak.
    if (currentNode == NULL) {
        printf("Tidak ada transaksi yang telah dilakukan. \n");
        return 0.0;
    }

    while (currentNode != NULL) {
    // Count the number of transactions.
        transactionsCount++;
        itemsetNode *currentItem = currentNode->transactionItem;
        while (currentItem != NULL) {
            if (strcmp(currentItem->item, itemName) == 0) {
                itemCount++;
                break; 
            }
            currentItem = currentItem->next;
        }
        currentNode = currentNode->nextTransaction;
    }
    support = (float)itemCount / transactionsCount;

    // printf("itemCount: %d\n", itemCount);
    // printf("transactionCount: %d\n", transactionsCount);
    // printf("support: %d / %d = %f\n", itemCount, transactionsCount, support);
    printf("support for %s is %f\n", itemName, support);

    return support;
}