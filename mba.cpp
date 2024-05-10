#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mba.h"
#include "linkedlist.h"

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
    newNode->terminal = false;
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

void addItemtoTrie(Trie **root, itemsetNode* items) {
    Trie *currentRoot = *root;
    while (items != NULL) {
        Trie *currentNode = currentRoot->fc;
        Trie *previousNode = NULL;
        while (currentNode != NULL && strcmp(currentNode->namaItem, items->item) != 0) {
            previousNode = currentNode;
            currentNode = currentNode->nb;
        }
        if (currentNode == NULL) {
            Trie *newNode = createTrieNode(items->item);
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
    printf("%s", node->namaItem);

    // Jika node terminal, cetak tanda * sebagai penanda
    if (node->terminal) {
        printf(" *");
    }
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