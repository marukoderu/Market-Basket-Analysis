#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>

//  Representasi daftar transaksi
//  |ID|nextTransaction|transactionItem| --> |item|next| --> ||
//              ||
//              \/
//  |ID|nextTransaction|transactionItem| --> ||
// Node untuk Linked List Itemset
typedef struct transactionsNode{
    int ID;
    transactionsNode *nextTransaction;
    itemsetNode *transactionItem;
} transactionsNode;

typedef struct itemsetNode {
    char item[50]; // Nama barang dalam itemset
    struct itemsetNode* next; // Pointer ke node berikutnya dalam linked list
} itemsetNode;

// Fungsi untuk membuat node transaksi baru.
transactionsNode* createTransactionsNode();

// Fungsi untuk menambahkan transaksi baru.
void newTransaction(transactionsNode* *firstTransaction, transactionsNode* *lastTransaction, itemsetNode* *items);

// Fungsi untuk membuat node item baru.
itemsetNode* createItemNode(const char* item);

// Fungsi untuk menambahkan item ke dalam satu transaksi.
void addItem(itemsetNode* *itemlist, char item[]);


// Fungsi untuk menambahkan node baru ke linked list itemset
void addItemsetNode(itemsetNode** head, const char* item);

// Fungsi untuk membersihkan linked list itemset
void clearItemsetList(itemsetNode** head);

#endif /* LINKEDLIST_H */
