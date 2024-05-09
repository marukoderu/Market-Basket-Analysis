#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "marketbasket.h"

// Fungsi untuk membuat node baru dalam Trie
TrieNode* createNode(const char* name) {
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    strcpy(newNode->name, name);
    newNode->count = 0;
    newNode->children = NULL;
    return newNode;
}

// Fungsi untuk menambahkan transaksi ke Trie
void addTransaction(TrieNode* root, const char* transaction[], int size) {
    TrieNode* temp = root;
    for (int i = 0; i < size; i++) {
        TrieNode* child = temp->children;
        TrieNode* prev = NULL;
        while (child != NULL && strcmp(child->name, transaction[i]) != 0) {
            prev = child;
            child = child->children;
        }
        if (child == NULL) {
            TrieNode* newNode = createNode(transaction[i]);
            if (prev == NULL) {
                temp->children = newNode;
            } else {
                prev->children = newNode;
            }
            temp = newNode;
        } else {
            temp = child;
        }
    }
    temp->count++;
}

// Fungsi untuk mencari node berdasarkan nama barang
TrieNode* searchNode(TrieNode* root, const char* name) {
    TrieNode* temp = root->children;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->children;
    }
    return temp;
}

// Fungsi untuk membuat node baru dalam linked list itemset
ItemsetNode* createItemsetNode(const char* item) {
    ItemsetNode* newNode = (ItemsetNode*)malloc(sizeof(ItemsetNode));
    strcpy(newNode->item, item);
    newNode->next = NULL;
    return newNode;
}

// Fungsi untuk menambahkan node baru ke linked list itemset
void addItemsetNode(ItemsetNode** head, const char* item) {
    ItemsetNode* newNode = createItemsetNode(item);
    if (*head == NULL) {
        *head = newNode;
    } else {
        ItemsetNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Fungsi untuk membersihkan linked list itemset
void clearItemsetList(ItemsetNode** head) {
    ItemsetNode* current = *head;
    ItemsetNode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}


// Fungsi untuk menghitung support dari satu item
float calculateSupport(TrieNode* root, const char* itemName, int totalTransactions) {
    TrieNode* node = searchNode(root, itemName);
    if (node == NULL) {
        return 0.0;
    }
    return (float) node->count / totalTransactions;
}

// Fungsi untuk menghitung confidence
float calculateConfidence(TrieNode* root, const char* item1, const char* item2) {
    char itemset[100];
    sprintf(itemset, "%s %s", item1, item2);
    int supportItemset = searchNode(root, itemset) != NULL ? searchNode(root, itemset)->count : 0;
    int supportItem1 = searchNode(root, item1) != NULL ? searchNode(root, item1)->count : 0;
    if (supportItem1 == 0) {
        return 0.0;
    }
    return (float) supportItemset / supportItem1;
}

// Fungsi untuk menghitung support dari dua item
float calculateSupportTwoItems(TrieNode* root, const char* item1, const char* item2, int totalTransactions) {
    char itemset[100];
    sprintf(itemset, "%s %s", item1, item2);
    TrieNode* node = searchNode(root, itemset);
    if (node == NULL) {
        return 0.0;
    }
    return (float) node->count / totalTransactions;
}


// Fungsi untuk menampilkan aturan asosiasi
void printAssociationRules(TrieNode* root, float minSupport, float minConfidence, int totalTransactions) {
    // Loop melalui setiap barang tunggal
    for (TrieNode* item1 = root->children; item1 != NULL; item1 = item1->children) {
        // Hitung support untuk item tunggal
        float suppItem1 = calculateSupport(root, item1->name, totalTransactions);

        // Loop melalui setiap barang lainnya
        for (TrieNode* item2 = item1->children; item2 != NULL; item2 = item2->children) {
            if (item1 != item2) {
                // Hitung support untuk kombinasi dua item
                float suppTwoItems = calculateSupportTwoItems(root, item1->name, item2->name, totalTransactions);

                // Hitung confidence
                float conf = suppTwoItems / suppItem1;

                // Cek kriteria support dan confidence
                if (suppTwoItems >= minSupport && conf >= minConfidence) {
                    printf("%s -> %s: Support=%.2f, Confidence=%.2f\n", item1->name, item2->name, suppTwoItems, conf);
                }
            }
        }
    }
}
