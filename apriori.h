#ifndef APRIORI_H
#define APRIORI_H
// #include "trie.h"
#include "linkedlist.h"
#include "stdio.h" // NULL identifier

// Fungsi untuk menghitung support dari satu item
// Support = Transactions including item A / Total transactions
// Kalo bisa satu function ini bisa hitung support buat >= 1 item
float calculateSupport(transactionsNode* root, char *itemCombination[]);

// Fungsi untuk menghitung confidence
float calculateConfidence(transactionsNode* root, char *itemCombination[]);

// Mengambil jumlah item dalam kombinasi
int countIteminCombination(char *itemCombination[]);

bool compareSupport(transactionsNode *root, float supportThreshold, char *items[]);

bool compareConfidence(transactionsNode *root, float confidenceThreshold, char *items[]);
#endif