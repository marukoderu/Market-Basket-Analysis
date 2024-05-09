#include "apriori.h"
#include "linkedlist.h"
#include <string.h>

// Support = Transactions including item A / Total transactions
float calculateSupport(transactionsNode *root, char *itemCombination[]) {
    float support;
    int transactionsCount = 0, itemCount = 0;
    transactionsNode *currentNode = root;

    // Check if there are any transactions.
    if (currentNode == NULL) {
        printf("Tidak ada transaksi yang telah dilakukan. \n");
        return 0.0;
    }

    // Count the number of transactions.
    while (currentNode != NULL) {
        transactionsCount++;
        int i = 0;
        int itemFound = 0;
        itemsetNode *currentItem = currentNode->transactionItem;
        while (itemCombination[i] != NULL) {
            while (currentItem != NULL) {
                if (strcmp(currentItem->item, itemCombination[i]) == 0) {
                    itemFound++;
                    break; 
                }
                currentItem = currentItem->next;
            }
            i++;
            currentItem = currentNode->transactionItem; // Reset currentItem for next item in combination
        }
        if (itemFound == i) {
            itemCount++;
        }
        currentNode = currentNode->nextTransaction;
    }

    support = (float)itemCount / transactionsCount;

    printf("support for ");
    int i = 0;
    while (itemCombination[i] != NULL) {
        printf("%s ", itemCombination[i]);
        i++;
    }
    printf("is %f \n", support);

    return support;
}