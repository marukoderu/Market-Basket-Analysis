#ifndef APRIORI_H
#define APRIORI_H
#include "trie.h"
#include "linkedlist.h"
#include "stdio.h" // NULL identifier

// Fungsi untuk menghitung support dari satu item
// Support = Transactions including item A / Total transactions
// Kalo bisa satu function ini bisa hitung support buat >= 1 item
float calculateSupport(transactionsNode* root, const char itemName[]);

// Fungsi untuk menghitung support dari dua item
float calculateSupportTwoItems(TrieNode* root, const char* item1, const char* item2, int totalTransactions);

// Fungsi untuk menghitung confidence
float calculateConfidence(TrieNode* root, const char* item1, const char* item2);

#endif