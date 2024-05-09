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
        newTransaction->ID = 1;
    } else {
        newTransaction->ID = (*lastTransaction)->ID + 1;
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

    if (*itemList == NULL){
        *itemList = newItem;
    } else {
        lastItem = getLastItem(lastItem);
        (*lastItem).next = newItem;
    }
}

// Cetak List Item dalam sebuah transaksi
// Mengambil pointer ke sebuah transaksi.
void printItems(transactionsNode* transaction) {
    printf("Items in Transaction #%d : ", transaction->ID);
    
    // Check if transactionItem is not NULL before accessing its members
    if (transaction->transactionItem != NULL) {
        itemsetNode* currentItem = transaction->transactionItem;
        while (currentItem != NULL) {
            printf("%s ", currentItem->item);
            currentItem = currentItem->next;
        }
    } else {
        printf("No items in this transaction.");
    }
}



// Search transaksi
// Menerima ID sebuah transaksi (int), kemudian return pointer ke transaksi dengan ID tersebut.
transactionsNode* searchTransaction(int transactionID, transactionsNode* firstTransaction) {
    transactionsNode* searchedTransaction = firstTransaction;

    while (searchedTransaction != NULL && searchedTransaction->ID != transactionID) {
        searchedTransaction = searchedTransaction->nextTransaction;    
    }
    return searchedTransaction;
}

// Mengambil pointer item terakhir dalam sebuah list Item.
itemsetNode *getLastItem(itemsetNode* firstItem){
    if (firstItem->next == NULL){
        return firstItem;
    }
    return getLastItem(firstItem->next);
}
