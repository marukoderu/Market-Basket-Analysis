#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mba.h"

// Membuat Node Trie Baru
Trie *createTrieNode(const char *namaItem) {
    // Alokasi memori
    Trie *newNode = (Trie *) malloc(sizeof(Trie));
    // Cek alokasi
    if (newNode == NULL) {
      printf("Maaf! Alokasi memori penuh :(");
      exit(1);
    }

    // Alokasi berhasil
    strcpy(newNode->namaItem, namaItem);
    newNode->fc = NULL;
    newNode->nb = NULL;
    newNode->pr = NULL;
    return newNode;
}

Trie *searchItem(Trie *root, const char *namaItem) {
    // Traversal Pointer
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

// Menambahkan transaksi ke Trie
void addTransaction(Trie *root, const char *namaItem) {
    // Buat node trie
    Trie *newNode = createTrieNode(namaItem);

    // Traversal Pointer
    Trie *pT = root;

    // Cek jika root kosong / NULL
    if (root->fc == NULL) {
        // Jika root belum memiliki anak, tambahkan node baru sebagai anak pertama
        root->fc = newNode;
        newNode->pr = root;
    } else {
        Trie *parent = NULL;
        Trie *prevSibling = NULL;
        Trie *child = pT->fc;

        // Cari parent node untuk node baru
        while (child != NULL && strcmp(namaItem, child->namaItem) > 0) {
            parent = child;
            prevSibling = child;
            child = child->nb;
        }

        // Jika parent tidak ditemukan, node baru akan menjadi anak pertama root
        if (parent == NULL) {
            newNode->nb = root->fc;
            root->fc = newNode;
            newNode->pr = root;
        } else {
            // Jika parent ditemukan, cek apakah node baru harus menjadi anak pertama parent
            if (prevSibling == NULL) {
                newNode->nb = parent->fc;
                parent->fc = newNode;
            } else {
                // Jika tidak, sisipkan node baru setelah sibling sebelumnya
                newNode->nb = prevSibling->nb;
                prevSibling->nb = newNode;
            }
            newNode->pr = parent;
        }
    }
}

// Fungsi rekursif untuk mencetak isi Trie
void printTrieRecursively(Trie *node, int level) {
    if (node == NULL) {
        return;
    }

    // Cetak indentasi sesuai tingkat level
    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    // Cetak nama item pada node saat ini
    printf("%s\n", node->namaItem);

    // Rekursif untuk mencetak anak-anak dari node saat ini
    printTrieRecursively(node->fc, level + 1);

    // Rekursif untuk mencetak saudara dari node saat ini
    printTrieRecursively(node->nb, level);
}

// Fungsi untuk mencetak isi Trie
void printTrie(Trie *root) {
    printf("Isi Trie:\n");
    // Memanggil fungsi rekursif untuk mencetak isi Trie dimulai dari root
    printTrieRecursively(root, 0);
}
