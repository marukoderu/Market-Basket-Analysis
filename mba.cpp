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
    Trie *pT = root->fc;

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

void getItemComb(Trie *firstItem, Trie *secondItem, char *itemCombination[]) {
    if ((firstItem == NULL) || (secondItem == NULL)) return;

    int i = 0;

    while (firstItem != NULL) {
        itemCombination[i] = (char*) malloc(strlen(firstItem->namaItem) + 1);
        strcpy(itemCombination[i++], firstItem->namaItem);
        firstItem = firstItem->fc;
    }
    

    if (secondItem != NULL) {
        itemCombination[i] = (char*) malloc(strlen(secondItem->namaItem) + 1);
        strcpy(itemCombination[i++], secondItem->namaItem);
    }
    
    itemCombination[i] = NULL;
}

void printAllItemCombination(Trie *root) {
    char *itemCombination[20]; // Assuming a maximum of 20 item combinations
    Trie *currentNode = root->fc;
    Trie *firstNode, *secondNode;

    

    while (currentNode != NULL) {
        firstNode = currentNode;
        secondNode = firstNode->nb;
        
        printf("%s \n", firstNode->namaItem);

        while (secondNode != NULL){
            getItemComb(firstNode, secondNode, itemCombination);

            for (int i = 0; itemCombination[i] != NULL; i++){
                if (strcmp(itemCombination[i], itemCombination[i-1])!=0){
                    printf("%s ", itemCombination[i]);
                }
            }
            printf("\n");
            secondNode = secondNode->nb;
        }

        currentNode = currentNode->nb;
    }
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

// Function to generate the first level items in the Trie
void generateFirstLevelItems(Trie **root, itemsetNode *uniqueItems, transactionsNode *transactions, float support) {
    itemsetNode *currentItem = uniqueItems;
    char *itemArray[2];  // Array to hold single item and null terminator

    // Iterate through all unique items
    while (currentItem != NULL) {
        itemArray[0] = currentItem->item;
        itemArray[1] = NULL;  // Null terminator for the array
        printf("Adding %s to trie \n", itemArray[0]);

        // Check if the item passes the support threshold
        bool isItemPassedSupportThreshold = compareSupport(transactions, support, itemArray);
        float itemSupport = calculateSupport(transactions, itemArray);  // Calculate support for the item

        // debug
        printf("Support for %s is %f \n", itemArray[0], itemSupport);
        if (isItemPassedSupportThreshold) {
            printf("%s with the support of %f passed the support threshold of %f \n", itemArray[0], itemSupport, support);
        } else {
            printf("%s with the support of %f didnt pass the support threshold of %f \n", itemArray[0], itemSupport, support);
        }

        if (isItemPassedSupportThreshold) {
            addSingleItemtoTrie(*root, currentItem->item, itemSupport);  // Add item to the Trie
            printf("Added %s to trie \n", currentItem->item);  // Log addition to the Trie
        }
        printf("Current item: %s\n", currentItem->item);  // Log current item being processed
        currentItem = currentItem->next;  // Move to the next item
    }
}

void addSingleItemtoTrie(Trie *parent, char item[], float support) {
    Trie *newNode, *currentNode;

    // Create new Trie node
    newNode = createTrieNode(item);
    if (newNode == NULL) {
        // Handle memory allocation failure
        printf("Error: Memory allocation failed\n");
        return;
    }
    newNode->support = support;
    printf("anak %s = %s\n", parent->namaItem, parent->fc->namaItem);
    // Check if the parent has no children
    if (strcmp(parent->namaItem, newNode->namaItem)==0){
        free(newNode);
        return;
    }
    if (parent->fc == NULL) {
        parent->fc = newNode; // Set newNode as the first child of the parent
        printf("Berhasil menambahkan %s sebagai fc %s\n", parent->fc->namaItem, parent->namaItem);
    } else {
        // Traverse the sibling list to check for duplicates and find the last sibling
        printf("%s sudah beranak \n", parent->namaItem);
        currentNode = parent->fc;
        printf("Sedang membandingkan %s dengan %s \n", currentNode->namaItem, item);
        while ((currentNode->nb != NULL) && (strcmp(currentNode->namaItem, newNode->namaItem) != 0)) {
            printf("pindah ke nb dari %s \n", currentNode->namaItem);
            currentNode = currentNode->nb; // Move to the next sibling
        }
        // Add newNode as the next sibling
        if ((strcmp(currentNode->namaItem, newNode->namaItem) == 0)){
            printf("%s sama dengan %s \n", currentNode->namaItem, newNode->namaItem);
            free(newNode);
            return;
        }
        currentNode->nb = newNode;
    }
    newNode->pr = parent; // Set parent node for newNode
}


void updateTrie(Trie **root, itemsetNode *uniqueItems, transactionsNode *transactions, float support){
    Trie *currentNode, *firstNode, *secondNode;
    char *itemCombination[20];

    deallocateTrie(*root);
    (*root) = createTrieNode("*");
    generateFirstLevelItems(root, uniqueItems, transactions, support);
    
    currentNode = (*root)->fc;
     while (currentNode != NULL) {
        firstNode = currentNode;
        secondNode = firstNode->nb;

        while (secondNode != NULL){
            getItemComb(firstNode, secondNode, itemCombination);
            printf("ItemCombination: ");
            for (int i = 0; itemCombination[i]!= NULL; i++){
                printf("%s ", itemCombination[i]);
            }
            printf("\n");
            
            bool isPassedSupportThreshold = compareSupport(transactions, support, itemCombination);
            float itemSupport = calculateSupport(transactions, itemCombination);

            printf("Support is %f \n", itemSupport);
            if (isPassedSupportThreshold) {
                printf("itemcombination with the support of %f passed the support threshold of %f \n", itemSupport, support);
            } else {
                printf("itemcombination with the support of %f didnt pass the support threshold of %f \n", itemSupport, support);
            }

            if (isPassedSupportThreshold) {
                Trie *parent = searchItem(*root, itemCombination[0]);
                for (int i = 0; itemCombination[i] != NULL; i++) {
                    if (parent->fc != NULL){
                    parent = parent->fc;
                    }
                    if (itemCombination[i+1] != NULL) {
                        // Add the next item to the Trie under the current parent
                        addSingleItemtoTrie(parent, itemCombination[i+1], itemSupport);
                    }
                }
            }

            secondNode = secondNode->nb;
        }

        currentNode = currentNode->nb;
    }
}

void deallocateTrie(Trie* root) {
    if (root == NULL) return;

    // Recursively deallocate the first child
    deallocateTrie(root->fc);

    // Recursively deallocate the next brother
    deallocateTrie(root->nb);

    // Deallocate the current node
    root->fc = NULL;
    root->nb = NULL;
    root->pr = NULL;
    free(root);
}