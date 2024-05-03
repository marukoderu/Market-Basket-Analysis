#ifndef TRIE_H
#define TRIE_H

// Node untuk Trie
typedef struct TrieNode {
    char name[50]; // Nama barang
    bool endofCombination; // Ujung trie?
    struct TrieNode* children;
} TrieNode;

// Fungsi untuk membuat node baru dalam Trie
TrieNode* createNode(const char* name);

// Fungsi untuk menambahkan transaksi ke Trie
void addTransaction(TrieNode* root, const char* transaction[], int size);

// Fungsi untuk mencari node berdasarkan nama barang
TrieNode* searchNode(TrieNode* root, const char* name);

#endif /* TRIE_H */
