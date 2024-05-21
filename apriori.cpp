#include "apriori.h"
#include "linkedlist.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Support = Transactions including item A / Total transactions
float calculateSupport(transactionsNode *root, char *itemCombination[]) {
    float support;
    int transactionsCount = 0, itemCount = 0;
    transactionsNode *currentNode = root;
    itemsetNode* currentItem;

    // Cek apakah ada transaksi
    if (currentNode == NULL) {
        printf("Tidak ada transaksi yang telah dilakukan. \n");
        return 0.0;
    }

    // Hitung jumlah transaksi
    while (currentNode != NULL) {
        transactionsCount++;
        int i = 0;
        int itemFound = 0;
        currentItem = currentNode->transactionItem;
        // looping untuk membandingkan item dalam transaksi dengan item dalam kombinasi
        while (itemCombination[i] != NULL) {
            while (currentItem != NULL) {
                if (strcmp(currentItem->item, itemCombination[i]) == 0) {
                    itemFound++;
                    break; 
                }
                currentItem = currentItem->next;
            }
            i++;
            currentItem = currentNode->transactionItem; // Kembali ke item pertama
        }
        if (itemFound == i) {
            itemCount++;
        }
        currentNode = currentNode->nextTransaction; // Pindah ke transaksi selanjutnya
    }

    support = (float)itemCount / transactionsCount;

    printf("support for ");
    int i = 0;
    while (itemCombination[i] != NULL) {
        printf("%s ", itemCombination[i]);
        i++;
    }
    printf("is %.1f \n", support);

    return support;
}

float calculateConfidence(transactionsNode *root, char *itemCombination[]) {
    float confidence;
    char *firstCombination[20];
    int i;

    // Hitung jumlah item dalam kombinasi
    int items = countIteminCombination(itemCombination);

    // Jika item hanya satu
    if (items == 1){
        confidence = (float)calculateSupport(root, itemCombination) / getLastTransaction(root)->ID;
        return confidence;
    }

    // Cek apakah jumlah item ganjil atau genap
    int halfItems = (items % 2 == 0) ? (items / 2) : (items / 2 + 1);

    // Copy setengah item dalam kombinasi
    for (i = 0; i < halfItems; i++) {
        firstCombination[i] = (char*) malloc(strlen(itemCombination[i]) + 1); // +1 for null terminator
        if (firstCombination[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        strcpy(firstCombination[i], itemCombination[i]);
    }
    // agar looping berhasil
    firstCombination[i] = NULL;

    // Calculate confidence(A -> B)
    confidence = (float)calculateSupport(root, itemCombination) / calculateSupport(root, firstCombination);

    // Free allocated memory
    for (i = 0; i < halfItems; i++) {
        free(firstCombination[i]);
    }

    return confidence;
}


// Mengambil jumlah item dalam kombinasi
int countIteminCombination(char *itemCombination[]){
    int count = 0;

    while (itemCombination[count] != NULL){
        count++;
    }

    return count;
}

bool compareSupport(transactionsNode *root, float supportThreshold, char *items[]){
    bool passedThreshold = false;
    if (calculateSupport(root, items) >= supportThreshold){
        passedThreshold = true;
    }
    return passedThreshold;
}