#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <direct.h>
#include <time.h>
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
    newNode->fc = NULL;
    newNode->nb = NULL;
    newNode->pr = NULL;
    newNode->support = 0;
    return newNode;
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
    printf(" (%.0f%%) ", node->support * 100);
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

// // Fungsi rekursif untuk mencetak semua kombinasi dari transaksi tertentu
// void printTransactionCombination(char *items[], int start, int length) {
//     for (int i = start; i < length; i++) {
//         for (int j = i + 1; j < length; j++) {
//             printf("%s, %s\n", items[i], items[j]);
//         }
//     }
// }

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

// Fungsi untuk mengambil kombinasi item dari Trie
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

// Fungsi untuk print semua kombinasi item dari Trie
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

// Function to generate the first level items in the Trie
void generateFirstLevelItems(Trie **root, itemsetNode *uniqueItems, transactionsNode *transactions, float support) {
    itemsetNode *currentItem = uniqueItems;
    char *itemArray[2];  // Array to hold single item and null terminator

    // Iterate through all unique items
    while (currentItem != NULL) {
        itemArray[0] = currentItem->item;
        itemArray[1] = NULL;  // Null terminator for the array

        // Check if the item passes the support threshold
        bool isItemPassedSupportThreshold = compareSupport(transactions, support, itemArray);
        float itemSupport = calculateSupport(transactions, itemArray);  // Calculate support for the item

        if (isItemPassedSupportThreshold) {
            addSingleItemtoTrie(*root, currentItem->item, itemSupport);  // Add item to the Trie
        }
        currentItem = currentItem->next;  // Move to the next item
    }
}

// Masukkan nilai support ke item dalam trie
void addSupporttoItem(transactionsNode *transaction, Trie *root){
    if (root == NULL) return;

    Trie *currentNode = root;
    int i;
    char *itemCombination[20];
    itemCombination[1] = NULL;

    // tambahkan support untuk level pertama
    while (currentNode != NULL){
        itemCombination[0] = (char*) malloc(strlen(currentNode->namaItem)+1);
        // printf("adding support \n");
        strcpy(itemCombination[0], currentNode->namaItem);
        // printf("adding support for %s", itemCombination[0]);
        currentNode->support = calculateSupport(transaction, itemCombination);
        // printf("Support added \n");
        // printf("support = %.1f", currentNode->support);
        currentNode = currentNode->nb;
    }
for (int j = 0; j < 1; j++) {
            free(itemCombination[j]);
            itemCombination[j] = NULL; // Reset pointer to NULL
        }

    i = 0;

    // Trie *branch = root;
    // while (branch != NULL){
        currentNode = root; 
        while (currentNode != NULL) {
            printf("adding support \n");
            itemCombination[i] = (char*) malloc(strlen(currentNode->namaItem) + 1);
            strcpy(itemCombination[i++], currentNode->namaItem);
            printf("adding support for %s \n", itemCombination[i-1]);

            if (currentNode->fc != NULL){
                currentNode = currentNode->fc;
            } else break;
        }
        itemCombination[i] = NULL;
        for (i = 0; itemCombination[i]!=NULL; i++){
            printf("%s ", itemCombination[i]);
        }
        currentNode->support = calculateSupport(transaction, itemCombination);
    //     branch = branch->nb;
    // }
    // currentNode->support = calculateSupport(transaction, currentNode->namaItem)
}

// Fungsi untuk update Trie sesuai dengan item yang memiliki nilai support yang melebihi threshold
void updateTrie(Trie **root, itemsetNode *uniqueItems, transactionsNode *transactions, float support){
    Trie *currentNode, *firstNode, *secondNode;
    char *itemCombination[20];

    deallocateTrie(*root);
    (*root) = createTrieNode("*");
    generateFirstLevelItems(root, uniqueItems, transactions, support);
    addSupporttoItem(transactions, (*root)->fc);
    currentNode = (*root)->fc;
     while (currentNode != NULL) {
        firstNode = currentNode;
        secondNode = firstNode->nb;

        while (secondNode != NULL){
            getItemComb(firstNode, secondNode, itemCombination);
            
            bool isPassedSupportThreshold = compareSupport(transactions, support, itemCombination);
            float itemSupport = calculateSupport(transactions, itemCombination);

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

            addSupporttoItem(transactions, currentNode);
            secondNode = secondNode->nb;
        }
        addSupporttoItem(transactions, currentNode);
        currentNode = currentNode->nb;
    }
}

// Fungsi untuk menambahkan sebuah item ke Trie
void addSingleItemtoTrie(Trie *parent, char item[], float support) {
    Trie *newNode, *currentNode;

    // Create new Trie node
    newNode = createTrieNode(item);

    // Hitung Support
    

    if (newNode == NULL) {
        // Handle memory allocation failure
        printf("Error: Memory allocation failed\n");
        return;
    }

    // Check if the parent is the same as newNode
    if (strcmp(parent->namaItem, newNode->namaItem)==0){
        free(newNode);
        return;
    }

    // Check if the parent has no children
    if (parent->fc == NULL) {
        parent->fc = newNode; // Set newNode as the first child of the parent
    } else {
        // Traverse the sibling list to check for duplicates and find the last sibling
        currentNode = parent->fc;
        while ((currentNode->nb != NULL) && (strcmp(currentNode->namaItem, newNode->namaItem) != 0)) {
            currentNode = currentNode->nb; // Move to the next sibling
        }
        // Add newNode as the next sibling
        if ((strcmp(currentNode->namaItem, newNode->namaItem) == 0)){
            free(newNode);
            return;
        }
        currentNode->nb = newNode;
    }
    newNode->pr = parent; // Set parent node for newNode
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

void generateAssociationRules(Trie *root, transactionsNode *transactions, float confidence) {
    Trie *currentBranch = root->fc;
    Trie *currentNode;
    char *itemCombination[10];
    char *associatedItems[20];
    int i = 0, k = 0;
    bool isPassedConfidenceThreshold;

    printf("Association Rules:\n");
    while (currentBranch != NULL) {
        currentNode = currentBranch;
        i = 0;
        while (currentNode != NULL) {

            // Allocate memory for itemCombination[i]
            itemCombination[i] = (char*) malloc(strlen(currentNode->namaItem) + 1);
            if (itemCombination[i] == NULL) {
                printf("Memory allocation failed\n");
                // Exit or handle the allocation failure
                exit(1);
            }

            // Copy currentNode->namaItem to itemCombination[i]
            strcpy(itemCombination[i], currentNode->namaItem);
            i++;
            currentNode = currentNode->fc;

            itemCombination[i] = NULL;
        }

        // Check if the combination passes the confidence threshold
        isPassedConfidenceThreshold = compareConfidence(transactions, confidence, itemCombination);

        if (isPassedConfidenceThreshold) {
            // Print the combination as an association rule
            for (int j = 0; j < i; j++) {
                printf("%s ", itemCombination[j]);
            }
            printf("\n");
        }

        // Free memory allocated for itemCombination
        for (int j = 0; j < i; j++) {
            free(itemCombination[j]);
            itemCombination[j] = NULL; // Reset pointer to NULL
        }

        currentBranch = currentBranch->nb;
    }
    printf("\n");
}

// Function to trim leading and trailing spaces from a string
void trim(char *str) {
    // Trim leading spaces
    char *start = str;
    while (*start && isspace(*start)) {
        start++;
    }

    // Trim trailing spaces
    char *end = str + strlen(str) - 1;
    while (end > start && isspace(*end)) {
        end--;
    }
    *(end + 1) = '\0'; // Terminate the string at the last non-space character
}

// Existing function to search for a single item in the Trie
Trie *searchItem(Trie *root, const char *namaItem) {
    Trie *pT = root->fc;

    // Traverse Trie to search for the item name
    while (pT != NULL) {
        if (strcmp(pT->namaItem, namaItem) == 0) {
            return pT; // If found, return the current node
        }
        pT = pT->nb; // Move to the next sibling
    }

    return NULL; // If not found, return NULL
}

// Function to search multiple items in the Trie and print the results
void searchItemsInTrie(Trie *root, char *items[], int itemCount) {
    for (int i = 0; i < itemCount; i++) {
        trim(items[i]); // Trim leading and trailing spaces from each item
        Trie *foundItem = searchItem(root, items[i]);
        if (foundItem != NULL) {
            printf("Found it: %s\n", items[i]);
        } else {
            printf("Sorry, we can't find it: %s\n", items[i]);
        }
    }
}

// Function to check if a directory exists
bool directoryExists(const char *path) {
    struct stat info;
    if (stat(path, &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}

// Function to create the "result" directory if it doesn't exist
void createResultDirectory() {
    const char *path = "result";
    if (!directoryExists(path)) {
        #ifdef _WIN32
            mkdir(path);
        #else
            mkdir(path, 0755); // UNIX/Linux
        #endif
    }
}

// Function to generate a unique filename based on the current date
char *generateFilename() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char *filename = (char *)malloc(20 * sizeof(char));
    if (filename == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strftime(filename, 20, "%d-%m-%Y", t);
    return filename;
}

// Function to write association rules to a file
void writeAssociationRulesToFile(const float *confidenceThresholds, int numThresholds, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to create file: %s\n", filename);
        return;
    }

    // Write header
    fprintf(file, "====================\n");
    fprintf(file, "Generate Association Rules\n");
    fprintf(file, "Result\n");
    fprintf(file, "====================\n");

    // Write association rules for each confidence threshold
    for (int i = 0; i < numThresholds; i++) {
        fprintf(file, "\nConfidence: %.1f\n", confidenceThresholds[i]);
        // Write association rules for this confidence threshold
        // (You need to implement this part based on your logic)
    }

    fprintf(file, "\nNotes:\n");
    fprintf(file, "- ...\n");

    fclose(file);
}

// Function to generate and save association rules to a file
void generateAndSaveAssociationRules(Trie *root, transactionsNode *transactions, const float *confidenceThresholds, int numThresholds) {
    createResultDirectory();
    char *filename = generateFilename();

    char filepath[50];
    snprintf(filepath, sizeof(filepath), "result/%s.txt", filename);

    writeAssociationRulesToFile(confidenceThresholds, numThresholds, filepath);

    printf("Association rules saved to: %s\n", filepath);

    free(filename);
}