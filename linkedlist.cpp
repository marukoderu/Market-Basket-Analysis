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

    while (lastItem != NULL){
        if (strcmp(lastItem->item, item) == 0){
            return;
        }
        lastItem = lastItem->next;
    }

    lastItem = *itemList;

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
    printf("\n");
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

// Mengambil pointer transaksi terakhir dalam sebuah list transaksi.
transactionsNode *getLastTransaction(transactionsNode* firstTransaction){
    if(firstTransaction->nextTransaction == NULL){
        return firstTransaction;
    }
    return getLastTransaction(firstTransaction->nextTransaction);
}

// Print semua transaksi beserta dengan itemnya/
void printAllTransactions(transactionsNode* firstTransaction) {
    transactionsNode* currentTransaction = firstTransaction;

    if (currentTransaction == NULL) {
        printf("Tidak ada transaksi yang telah dilakukan. \n");
        return;
    }

    while (currentTransaction != NULL) {
        printItems(currentTransaction);
        currentTransaction = currentTransaction->nextTransaction;
    }
    printf("\n");
}

// Menyimpan data transaksi kedalam file
// !!!WIP!!!
// To-Do: stop the loop.
void saveTransactions(transactionsNode* firstTransaction){
    FILE *file = fopen("TransactionsData.dat", "a+");
    if (file == NULL){
        printf("File can't be opened. \n");
    }
    while (firstTransaction != NULL){
        fwrite(firstTransaction, sizeof(transactionsNode), 1, file);
    }
    fclose(file);
}

// Buat node untuk item
// Menerima string item
// next = NULL
itemsetNode* createItemList(char item[]){
    itemsetNode* newItem = (itemsetNode*) malloc(sizeof(itemsetNode));
    strcpy(newItem->item, item);
    newItem->next = NULL;
    return newItem;
}

itemsetNode* searchIteminList(itemsetNode *root, char item[]){
    itemsetNode* itemAddress = root;

    while (itemAddress != NULL && strcmp(itemAddress->item, item) != 0) {
        itemAddress = itemAddress->next;    
    }
    return itemAddress;
}

void generateItemList(itemsetNode **root, itemsetNode *items) {
    if (items == NULL) {
        return;
    }

    itemsetNode* currentItem;
    
    // Initialize root if it's NULL
    if (*root == NULL) {
        *root = createItemList(items->item);
        currentItem = *root;
        items = items->next;
    } else {
        currentItem = *root;
        while (currentItem->next != NULL) {
            currentItem = currentItem->next;
        }
    }

    while (items != NULL) {
        if (searchIteminList(*root, items->item) == NULL) {
            currentItem->next = createItemList(items->item);
            currentItem = currentItem->next;
        }
        items = items->next;
    }

    printf("gen item list \n");
}


void printItemList(itemsetNode* root){
    printf("printitemlist \n");
    // printf("item: %s", root->item);
    // Check if transactionItem is not NULL before accessing its members
    if (root != NULL) {
        itemsetNode* currentItem = root;
        while (currentItem != NULL) {
            printf("%s ", currentItem->item);
            currentItem = currentItem->next;
        }
    } else {
        printf("No items in this transaction.");
    }
    printf("\n");
}

void listtoArray(itemsetNode *list, char *array[]){
    int i = 0;
    while (list != NULL){
        strcpy(array[i], list->item);
        list = list->next;
        i++;
    }
    array[i] = NULL;
}