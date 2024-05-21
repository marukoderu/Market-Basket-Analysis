#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mba.h"
#include "linkedlist.h"
#include "apriori.h"

// Membuat Node Trie Baru
Trie *createTrieNode(const char *namaItem) {
    Trie *newNode = (Trie *)malloc(sizeof(Trie));
    if (newNode == NULL) {
        printf("Maaf! Alokasi memori penuh :(");
        exit(1);
    }

    strcpy(newNode->namaItem, namaItem);
    newNode->support = 0;
    newNode->fc = NULL;
    newNode->nb = NULL;
    newNode->pr = NULL;
    return newNode;
}

// Mencari node di Trie berdasarkan nama item
Trie *searchItem(Trie *root, const char *namaItem) {
    Trie *pT = root;

    // Traverse Trie untuk mencari nama item
    while (pT != NULL) {
        if (strcmp(pT->namaItem, namaItem) == 0) {
            return pT; // Jika ditemukan, kembalikan node saat ini
        }
        pT = pT->nb; // Lanjut ke sibling berikutnya
    }

    return NULL; // Jika tidak ditemukan, kembalikan NULL
}

// Menambahkan Itemsets ke bentuk Trie
// 
void addItemtoTrie(Trie **root, itemsetNode* items) {
    // Penunjuk ROOT
    Trie *currentRoot = *root;
    while (items != NULL) {
        // Penunjuk node fc dari root / parent
        Trie *currentNode = currentRoot->fc;
        // Node sebelumnya
        Trie *previousNode = NULL;

        // compare nama item dengan yang akan di tambahkan
        // jika sama, maka jangan ditambahkan tapi ganti pointer ke node tersebut
        while (currentNode != NULL && strcmp(currentNode->namaItem, items->item) != 0) {
            printf("asdasad\n");
            previousNode = currentNode;
            currentNode = currentNode->nb;
        }

        // jika currentNode nya NULL
        // artinya item tersebut belum ada di Trie
        if (currentNode == NULL) {
            // Buat Trie Node dari Itemset
            Trie *newNode = createTrieNode(items->item);
            // Jika prev node masih NULL
            // newNode akan menjadi fc dari root / parent
            if (previousNode == NULL) {
                currentRoot->fc = newNode;
            } else { 
                previousNode->nb = newNode;
            }

            newNode->pr = currentRoot;
            currentNode = newNode;
        }
        items = items->next;
        currentRoot = currentNode;
    }
}

// Fungsi rekursif untuk mencetak isi Trie dengan format tertentu
void printTrieFormatted(Trie *node, int level) {
    if (node == NULL) {
        return;
    }

    // Cetak indentasi dan '|----' sesuai dengan level
    for (int i = 0; i < level; i++) {
        printf("  ");
        if (i > 0) {
            printf("|");
        }
        printf("----");
    }

    // Cetak nama item pada node saat ini
    printf(" %s ", node->namaItem);
    printf("\n");

    // Rekursif untuk mencetak anak-anak dari node saat ini
    printTrieFormatted(node->fc, level + 1);

    // Rekursif untuk mencetak saudara dari node saat ini
    printTrieFormatted(node->nb, level);
}

// Fungsi untuk mencetak Trie dalam format tertentu
void printTrieFormatted(Trie *root) {
    printf("* (ROOT)\n");
    // Memanggil fungsi rekursif untuk mencetak isi Trie dimulai dari root
    printTrieFormatted(root->fc, 1);
}

// Fungsi rekursif untuk mencetak semua kombinasi dari transaksi tertentu
void printTransactionCombination(char *items[], int start, int length) {
    for (int i = start; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            printf("%s, %s\n", items[i], items[j]);
        }
    }
}

// Fungsi rekursif untuk mengambil kombinasi item dari Trie
void getItemCombinationRecursive(Trie *root, char *prefix, int prefixLength) {
    if (prefixLength > 0) {
        printf("%s", prefix);
        printf("\n");
    }

    Trie *child = root->fc;
    while (child != NULL) {
        char newPrefix[50];
        strcpy(newPrefix, prefix);
        strcat(newPrefix, child->namaItem);
        strcat(newPrefix, ", ");
        getItemCombinationRecursive(child, newPrefix, prefixLength + 1);
        child = child->nb;
    }
}

// Fungsi untuk mengambil kombinasi item dari Trie
void getItemCombination(Trie *root) {
    if (root == NULL) return;
    char prefix[50] = ""; // Buat string kosong untuk dijadikan prefix awal
    getItemCombinationRecursive(root, prefix, 0);
}

// hitung support untuk tiap item
// untuk item yang supportnya > usersupport
    // masukkan ke trie
// hitung support untuk kombinasi item yang sudah ada dalam trie
    // masuk ke trie

// while (items != NULL){
//     calculatesupport(items->item)
//     untuk item yang supportnya > threshold 
//         -> createlistitem

//     addItemtoTrie(root, )
//     items = items->next
// }
void generateFirstLevelItems(Trie **root, itemsetNode *uniqueItems, transactionsNode *transactions, float support) {
    itemsetNode *currentItem = uniqueItems;
    char *itemArray[2]; // Array to hold single item and null terminator
    
    while (currentItem != NULL) {
        itemArray[0] = currentItem->item;
        itemArray[1] = NULL;

        if (compareSupport(transactions, support, itemArray)) {
            float itemSupport = calculateSupport(transactions, itemArray);
            addSingleItemtoTrie(root, currentItem->item, itemSupport);
            printf("added %s to trie \n", currentItem->item);
        }
        printf("Current item: %s\n", currentItem->item);
        currentItem = currentItem->next;
    }
    printf("Break loop\n");
}

void addSingleItemtoTrie(Trie **parent, char item[], float support) {
    Trie *newNode, *currentNode;

    // Create new Trie node
    newNode = createTrieNode(item);
    newNode->support = support;

    if ((*parent)->fc == NULL) {
        // If the first child of the parent is NULL, set it to newNode
        (*parent)->fc = newNode;
    } else {
        // Traverse the sibling list to find the last sibling
        currentNode = (*parent)->fc;
        while (currentNode->nb != NULL) {
            currentNode = currentNode->nb;            
        }
        // Add newNode as the next sibling
        currentNode->nb = newNode;
    }
}
