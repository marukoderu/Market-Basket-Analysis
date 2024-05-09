#ifndef MARKETBASKET_H
#define MARKETBASKET_H

// Node untuk Trie
typedef struct TrieNode {
    char name[50]; // Nama barang
    int count; // Jumlah transaksi mengandung barang tersebut
    struct TrieNode* children;
} TrieNode;

// Node untuk Linked List Itemset
typedef struct ItemsetNode {
    char item[50]; // Nama barang dalam itemset
    struct ItemsetNode* next; // Pointer ke node berikutnya dalam linked list
} ItemsetNode;

// Fungsi untuk membuat node baru dalam Trie
TrieNode* createNode(const char* name);

// Fungsi untuk menambahkan transaksi ke Trie
void addTransaction(TrieNode* root, const char* transaction[], int size);

// Fungsi untuk mencari node berdasarkan nama barang
TrieNode* searchNode(TrieNode* root, const char* name);

// Fungsi untuk menghitung support dari satu item
float calculateSupport(TrieNode* root, const char* itemName, int totalTransactions);

// Fungsi untuk menghitung confidence
float calculateConfidence(TrieNode* root, const char* item1, const char* item2);

// Fungsi untuk menampilkan aturan asosiasi
void printAssociationRules(TrieNode* root, float minSupport, float minConfidence, int totalTransactions);

// Fungsi untuk menghitung support dari dua item
float calculateSupportTwoItems(TrieNode* root, const char* item1, const char* item2, int totalTransactions);


#endif
