#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>

//  Representasi daftar transaksi
//  |ID|nextTransaction|transactionItem| --> |item|next| --> ||
//              ||
//              \/
//  |ID|nextTransaction|transactionItem| --> ||
// Node untuk Linked List Itemset

typedef struct itemsetNode {
    char item[50]; // Nama barang dalam itemset
    struct itemsetNode* next; // Pointer ke node berikutnya dalam linked list
} itemsetNode;

typedef struct transactionsNode{
    int ID;
    transactionsNode *nextTransaction;
    itemsetNode *transactionItem;
} transactionsNode;


// Fungsi untuk membuat list item dengan supportnya
void generateItemList(itemsetNode **root, itemsetNode *items);

void printItemList(itemsetNode* root);

// Fungsi untuk membuat node transaksi baru.
transactionsNode* createTransactionsNode();

// Fungsi untuk menambahkan transaksi baru.
void newTransaction(transactionsNode* *firstTransaction, transactionsNode* *lastTransaction, itemsetNode* items);

// Fungsi untuk membuat node item baru.
itemsetNode* createItemNode(const char* item);

// Fungsi untuk menambahkan item ke dalam satu transaksi.
void addItem(itemsetNode* *itemlist, char item[]);

// Fungsi untuk mendapatkan pointer ke item terakhir dalam list item.
itemsetNode* getLastItem(itemsetNode* firstItem);

// Fungsi untuk mencetak barang-barang dalam sebuah transaksi.
void printItems(transactionsNode* transaction);

// Fungsi untuk mencari sebuah transaksi by ID
transactionsNode* searchTransaction(int transactionID, transactionsNode* firstTransaction);

// Fungsi untuk mencetak semua transaksi dan barang-barangnya.
void printAllTransactions(transactionsNode* firstTransaction);

// Fungsi untuk mengambil pointer ke transaksi terakhir.
transactionsNode *getLastTransaction(transactionsNode* firstTransaction);

// Fungsi untuk menyimpan data transaksi ke dalam sebuah file.
void saveTransactions(transactionsNode* firstTransaction);

#endif /* LINKEDLIST_H */
