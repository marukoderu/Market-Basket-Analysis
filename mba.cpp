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

// Menambahkan transaksi ke Trie
void addTransaction(Trie *root, const char *namaItem) {
    // Cari node Trie untuk namaItem
    Trie *node = searchItem(root, namaItem);

    // Jika node belum ada, buat node baru
    if (node == NULL) {
        node = createTrieNode(namaItem);
        node->terminal = true; // Tandai sebagai node terminal
        node->pr = root; // Tetapkan parent
    }
}

// Fungsi untuk mendapatkan transaksi dari linked list dan membuat Trie
void getTransaction(Trie *root, transactionsNode *firstTransaction) {
    transactionsNode *currentTransaction = firstTransaction;

    // Iterasi melalui setiap transaksi
    while (currentTransaction != NULL) {
        // Iterasi melalui setiap item dalam transaksi
        itemsetNode *currentItem = currentTransaction->transactionItem;
        while (currentItem != NULL) {
            // Tambahkan item ke dalam Trie
            addTransaction(root, currentItem->item);
            currentItem = currentItem->next;
        }
        currentTransaction = currentTransaction->nextTransaction;
    }
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

void addItemtoTrie(char namaItem[], Trie **root) {
    // Buat array of pointers untuk menyimpan pointer ke node Trie dari setiap level
    Trie *levelPointers[20]; // Misalnya, batasi maksimum level Trie menjadi 20
    int level = 0;

    // Inisialisasi levelPointers dengan NULL
    for (int i = 0; i < 20; i++) {
        levelPointers[i] = NULL;
    }

    // Cek apakah root Trie kosong
    if (*root == NULL) {
        // Jika kosong, buat node baru untuk item pertama dalam array
        Trie *newNode = createTrieNode(namaItem);
        *root = newNode;
        levelPointers[0] = newNode; // Simpan pointer ke node root
        level++;
    } else {
        // Jika tidak kosong, cek apakah item pertama dalam array sama dengan fc dari root
        if (strcmp((*root)->namaItem, namaItem) != 0) {
            // Jika tidak sama, tambahkan item pertama sebagai fc dari root
            Trie *newNode = createTrieNode(namaItem);
            newNode->nb = (*root)->fc;
            (*root)->fc = newNode;
            newNode->pr = *root;
            levelPointers[0] = newNode; // Simpan pointer ke node fc dari root
            level++;
        } else {
            // Jika sama, langsung lanjut ke fc dari root
            levelPointers[0] = (*root)->fc;
        }
    }

    // Iterasi melalui item-item dalam array kecuali item pertama
    for (int i = 1; namaItem[i] != '\0'; i++) {
        // Jika pointer di level sebelumnya NULL, berarti Trie belum memiliki branch untuk item sebelumnya
        // Ini menunjukkan kesalahan dalam data transaksi
        if (levelPointers[i - 1] == NULL) {
            printf("Error: Invalid transaction data.\n");
            return;
        }

        // Cari node dalam Trie yang sesuai dengan item saat ini
        Trie *currentNode = levelPointers[i - 1]->fc;
        Trie *previousNode = NULL;
        while (currentNode != NULL && strcmp(currentNode->namaItem, &namaItem[i]) != 0) {
            previousNode = currentNode;
            currentNode = currentNode->nb;
        }

        // Jika node tidak ditemukan, tambahkan node baru sebagai nb dari node sebelumnya
        if (currentNode == NULL) {
            Trie *newNode = createTrieNode(&namaItem[i]);
            previousNode->nb = newNode;
            newNode->pr = levelPointers[i - 1];
            levelPointers[i] = newNode; // Simpan pointer ke node saat ini
            level++;
        } else {
            // Jika node ditemukan, langsung lanjut ke node tersebut
            levelPointers[i] = currentNode;
        }
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