#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mba.h"

void menuHeader() {
    printf("| ===========================================\n");
    printf("| MARKET BASKET ANALYSIS PROGRAM\n");
    printf("| with Apriori Algorithm & Association Rules\n");
    printf("| ~ created by Raihan & Tresna\n");
}

int main() {
    // Trie Root Initialization
    Trie *root = createTrieNode("*");

    int option, numItem, transaction = 1;
    char namaItem[20];

    do {
        // Menu Option
        menuHeader();
        printf("| -------------------------------------------\n");
        printf("| Menu Option :\n");
        printf("| -------------------------------------------\n");
        printf("| 1 | Input Data Transaksi\n");
        printf("| 2 | Lihat Data Transaksi\n");
        printf("| 3 | Cari Data Transaksi\n");
        printf("| 0 | Exit Program\n");
        printf(">   Silahkan pilih option menu (masukkan angka nya) : ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                system("CLS");
                menuHeader();
                printf("| -------------------------------------------\n");

                // Proses input barang transaksi
                printf("Ada berapa barang dalam transaksi ke-%d :", transaction);
                scanf("%d", &numItem);

                for (int i = 1; i <= numItem; i++) {
                    printf("Masukkan nama barang ke-%d : ", i);
                    scanf(" %s", namaItem);

                    // Mencari parent yang sesuai untuk menempatkan barang baru
                    Trie *parent = searchItem(root, namaItem);
                    if (parent == NULL) {
                        // Jika parent tidak ditemukan, barang baru menjadi anak pertama dari root
                        addTransaction(root, namaItem);
                    } else {
                        // Jika parent ditemukan, cek apakah barang baru sudah ada sebagai anak
                        Trie *child = parent->fc;
                        bool found = false;
                        while (child != NULL) {
                            if (strcmp(child->namaItem, namaItem) == 0) {
                                found = true;
                                break;
                            }
                            child = child->nb;
                        }
                        // Jika barang belum ada, tambahkan sebagai anak terakhir dari parent
                        if (!found) {
                            addTransaction(parent, namaItem);
                        }
                    }
                }
                transaction++;
                break;
            case 2:
                printTrie(root);
                break;
            case 3:
                printf("In Progress");
                break;
            default:
                printf("Tolong masukkan opsi menu yang valid! >.<\n");
                break;
        }

    } while (option != 0);

    free(root);

    return 0;
}
