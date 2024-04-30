#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Node untuk Linked List Itemset
typedef struct ItemsetNode {
    char item[50]; // Nama barang dalam itemset
    struct ItemsetNode* next; // Pointer ke node berikutnya dalam linked list
} ItemsetNode;

// Fungsi untuk membuat node baru dalam linked list itemset
ItemsetNode* createItemsetNode(const char* item);

// Fungsi untuk menambahkan node baru ke linked list itemset
void addItemsetNode(ItemsetNode** head, const char* item);

// Fungsi untuk membersihkan linked list itemset
void clearItemsetList(ItemsetNode** head);

#endif /* LINKEDLIST_H */
