#ifndef APRIORI_H
#define APRIORI_H
#include "trie.h"

// Fungsi untuk menghitung support dari satu item
float calculateSupport(TrieNode* root, const char* itemName, int totalTransactions);

// Fungsi untuk menghitung support dari dua item
float calculateSupportTwoItems(TrieNode* root, const char* item1, const char* item2, int totalTransactions);

// Fungsi untuk menghitung confidence
float calculateConfidence(TrieNode* root, const char* item1, const char* item2);

#endif