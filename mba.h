#ifndef MBA_H
#define MBA_H

#include "linkedlist.h"

// Trie Data Structure
typedef struct TrieNode {
    char namaItem[20];
    float support;
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

void addSingleItemtoTrie(Trie **parent, char item[], float support);
#endif /* MBA_H */