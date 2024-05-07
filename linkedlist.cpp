#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>

// Buat node untuk transaksi
// ID = 0, nextTransaction = NULL, transactionItem = NULL
transactionsNode* createTransactionsNode(){
    transactionsNode* newNode = (transactionsNode*) malloc(sizeof(transactionsNode));
    newNode->ID = 0;
    newNode->nextTransaction = NULL;
    newNode->transactionItem = NULL;
    return newNode; 
}

// Menambahkan transaksi baru
// Menerima pointer ke list transaksi (root) dan pointer ke list item yang dibeli (items)
// Jika sudah ada transaksi maka, sambungkan newNode ke ujung list transaksi
void newTransaction(transactionsNode* *firstTransaction, transactionsNode* *lastTransaction, itemsetNode* items){
    transactionsNode* newTransaction = createTransactionsNode();
    if ((*firstTransaction == NULL) && (*lastTransaction == NULL)){
        (*firstTransaction) = newTransaction; 
    } else {
        (*lastTransaction)->nextTransaction = newTransaction;
    }
    *lastTransaction = newTransaction;
    newTransaction->transactionItem = items;
}

// Buat node untuk item
// Menerima string item
// next = NULL
itemsetNode* createItemNode(char item[]){
    itemsetNode* newItem = (itemsetNode*) malloc(sizeof(itemsetNode));
    strcpy(newItem->item, item);
    newItem->next = NULL;
    return newItem;
}

// Buat list item
// Menerima pointer ke list item yang ada dan nama item baru
// Cek eksistensi itemlist -> buat node item -> sambungkan item baru ke list
// Memanggil modul createItemNode untuk membuat node.
void addItem(itemsetNode* *itemList, char item[]){    
    itemsetNode* newItem = createItemNode(item);
    itemsetNode* lastItem = *itemList;

    if (itemList == NULL){
        *itemList = newItem;
    } else {
        while (lastItem->next != NULL){
            lastItem = lastItem->next;
        }
        (*lastItem).next = newItem;
    }
    
}

