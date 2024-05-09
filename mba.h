#ifndef MBA_H
#define MBA_H

#include "linkedlist.h"

// Trie Data Structure
typedef struct TrieNode {
    char namaItem[20];
    struct TrieNode *fc, *nb, *pr;
    bool terminal;
} Trie;

// Membuat Node Trie Baru
Trie *createTrieNode(const char *namaItem);

// Menambahkan transaksi ke Trie
void addTransaction(Trie *root, const char *namaItem);

// Fungsi untuk mendapatkan transaksi dari linked list dan membuat Trie
void getTransaction(Trie *root, transactionsNode *firstTransaction);

// Mencari node di Trie berdasarkan nama item
Trie *searchItem(Trie *root, const char *namaItem);

// Mencetak isi Trie
// void printTrie(Trie *root);

// Menambahkan item ke Trie
void addItemtoTrie(char namaItem[], Trie **root);

// Fungsi rekursif untuk mencetak isi Trie dengan format tertentu
void printTrieFormatted(Trie *node, int level);

// Fungsi untuk mencetak Trie dalam format tertentu
void printTrieFormatted(Trie *root);

#endif /* MBA_H */