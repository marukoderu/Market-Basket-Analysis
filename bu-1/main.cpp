#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "marketbasket.h"

int main() {
    TrieNode* root = createNode("ROOT");

    int numTransactions;
    printf("Masukkan jumlah transaksi: ");
    scanf("%d", &numTransactions);

    // Memproses setiap transaksi
    for (int i = 0; i < numTransactions; i++) {
        int numItems;
        printf("Masukkan jumlah barang dalam transaksi %d: ", i + 1);
        scanf("%d", &numItems);

        char** transaction = (char**)malloc(numItems * sizeof(char*));

        // Memasukkan setiap barang dalam transaksi
        printf("Masukkan nama barang dalam transaksi %d (tanpa spasi, dipisahkan dengan enter):\n", i + 1);
        for (int j = 0; j < numItems; j++) {
            transaction[j] = (char*)malloc(50 * sizeof(char));
            scanf("%s", transaction[j]);
        }

        // Menambahkan transaksi ke Trie
        addTransaction(root, (const char**)transaction, numItems);

        // Membersihkan memory setelah transaksi selesai diproses
        for (int j = 0; j < numItems; j++) {
            free(transaction[j]);
        }
        free(transaction);
    }

    // Menampilkan aturan asosiasi
    printf("\nAturan Asosiasi:\n");
    printAssociationRules(root, 0.2, 0.5, numTransactions);

    return 0;
}
