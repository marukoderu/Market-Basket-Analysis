#ifndef MBA_H
#define MBA_H

#include "linkedlist.h"

// Trie Data Structure
typedef struct TrieNode {
    char namaItem[20];
    struct TrieNode *fc, *nb, *pr;
} Trie;

// Membuat Node Trie Baru
Trie *createTrieNode(const char *namaItem);

// Mencari node di Trie berdasarkan nama item
Trie *searchItem(Trie *root, const char *namaItem);

// Menambahkan item ke Trie
void addItemtoTrie(Trie **root, itemsetNode* items);

// Fungsi rekursif untuk mencetak isi Trie dengan format tertentu
void printTrieFormatted(Trie *node, int level);

// Fungsi untuk mencetak Trie dalam format tertentu
void printTrieFormatted(Trie *root);

// Fungsi untuk mengambil kombinasi item dari Trie
void getItemCombination(Trie *root);

void printTransactionCombination(char *items[], int start, int length);

void generateFirstLevelItems(Trie **root, itemsetNode *uniqueItems, transactionsNode *transactionsNode, float support);

void addSingleItemtoTrie(Trie *parent, char item[], float support);

void deallocateTrie(Trie* root);

void updateTrie(Trie **root, itemsetNode *uniqueItems, transactionsNode *transactions, float support);

void printAllItemCombination(Trie *root);

void getItemComb(Trie *firstItem, Trie *secondItem, char *itemCombination[]);

void generateAssociationRules(Trie *root, transactionsNode *transactions, float confidence);

void searchItemsInTrie(Trie *root, char *items[], int itemCount);

// Function to generate and save association rules to a file
void generateAndSaveAssociationRules(Trie *root, transactionsNode *transactions, const float *confidenceThresholds, int numThresholds);

// Update the function declaration
void writeAssociationRulesToFile(const float *confidenceThresholds, int numThresholds, const char *filename);

#endif /* MBA_H */