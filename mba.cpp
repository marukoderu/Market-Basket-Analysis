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
    printf("%s", node->namaItem);
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

// Fungsi untuk mencetak semua kombinasi dari transaksi tertentu
void printTransactionCombination(char *items[], int start, int length) {
    for (int i = start; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            printf("%s, %s\n", items[i], items[j]);
        }
    }
}

// Fungsi rekursif untuk mengambil semua kombinasi item dari Trie
void getItemCombinationRecursive(Trie *root, char **currentCombination, int index, int length) {
    if (root == NULL) return;

    // Panggil rekursi dengan mengabaikan item saat ini
    getItemCombinationRecursive(root->nb, currentCombination, index, length);

    // Tambahkan item saat ini ke dalam kombinasi
    currentCombination[index] = root->namaItem;
    index++;

    // Jika kita mencapai node yang merupakan bagian terakhir dari transaksi,
    // cetak semua kombinasi yang mungkin
    if (root->fc == NULL) {
        printTransactionCombination(currentCombination, 0, index);
    } else {
        // Panggil rekursi untuk anak-anak node saat ini
        Trie *child = root->fc;
        while (child != NULL) {
            getItemCombinationRecursive(child, currentCombination, index, length);
            child = child->nb;
        }
    }

    // Kembalikan nilai indeks ke posisi semula setelah selesai memproses anak-anak
    index--;
    currentCombination[index] = NULL;
}

// Fungsi untuk mengambil kombinasi item dari Trie
void getItemCombination(Trie *root) {
    if (root == NULL) return;

    // Hitung panjang transaksi dan alokasikan array kombinasi
    int length = 0;
    Trie *node = root->fc;
    while (node != NULL) {
        length++;
        node = node->nb;
    }
    char **currentCombination = (char **)malloc(length * sizeof(char *));
    if (currentCombination == NULL) {
        printf("Maaf! Alokasi memori gagal :(");
        exit(1);
    }

    // Panggil fungsi rekursif untuk mendapatkan kombinasi
    getItemCombinationRecursive(root, currentCombination, 0, length);

    // Bebaskan memori setelah selesai
    free(currentCombination);
}