#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mba.h"
#include "linkedlist.h"
#include "apriori.h"

void menuHeader() {
    printf("| ===========================================\n");
    printf("| MARKET BASKET ANALYSIS PROGRAM\n");
    printf("| with Apriori Algorithm & Association Rules\n");
    printf("| ~ created by Raihan & Tresna\n");
}

int main() {
    // Trie Root Initialization
    Trie *root = createTrieNode("*");
    itemsetNode* itemlist = NULL;
    transactionsNode *firstTransaction = NULL, *lastTransaction = NULL;

    int option, numItem, transaction = 1;
    char namaItem[20];

    do {
        // Menu Option
        menuHeader();
        printf("| -------------------------------------------\n");
        printf("| Menu Option :\n");
        printf("| -------------------------------------------\n");
        printf("| 1 | Input Data Transaksi\n");
        printf("| 2 | Lihat Data Transaksi (Trie)\n");
        printf("| 3 | Cari Data Transaksi\n");
        printf("| 4 | Lihat Data Transaksi \n");
        printf("| 5 | Hitung support untuk suatu item \n");
        printf("| 0 | Exit Program\n");
        printf(">   Silahkan pilih option menu (masukkan angka nya) : ");
        scanf("%d", &option);

        switch (option) {
            case 1:{
                numItem = 1;
                system("CLS");
                menuHeader();
                printf("| -------------------------------------------\n");

                // Proses input barang transaksi
                printf("Silahkan masukkan nama barang satu-persatu untuk transaksi ke-%d. \n", transaction);
                printf("Masukkan 0 jika anda telah selesai. \n");
                while (1){
                    printf("Masukkan nama barang ke-%d: ", numItem);
                    scanf(" %s", namaItem);
                    // Jika nama item = 0, maka sambungkan list item ke list transaksi.
                    // Jika bukan, maka sambungkan item baru ke list item.
                    if(strcmp(namaItem, "0") != 0){
                        addItem(&itemlist, namaItem);
                        addItemtoTrie(namaItem, &root);
                        numItem++;
                    } else {
                        newTransaction(&firstTransaction, &lastTransaction, itemlist);
                        itemlist = NULL; // Kosongkan list item.
                        break;
                    }
                }
                transaction++;
                break;
            }
            case 2:{
                printf("Data Transaksi (Trie):\n");
                printf("----------------------------------------------\n");
                printTrieFormatted(root);
                printf("----------------------------------------------\n");
                system("pause");
                break;
            }
            case 3:{
                printf("In Progress");
                break;
            }
            case 4:{
                printAllTransactions(firstTransaction);
                system("pause");
                break;
            }
            case 5:{
                char *itemCombination[20];
                int i = 0;
                while (1){
                    printf("Input nama item yang ingin dihitung: ");
                    scanf(" %s", namaItem);
                    if (strcmp(namaItem, "0") != 0 && i < 20) {
                        itemCombination[i] = (char*) malloc(strlen(namaItem) + 1);
                        strcpy(itemCombination[i], namaItem);
                        i++;
                    } else {
                    itemCombination[i] = NULL;
                    break;
                    }
                }
                printf("Support: %.2f \n", calculateSupport(firstTransaction, itemCombination));
                printf("Confidence: %.2f \n", calculateConfidence(firstTransaction, itemCombination));
                system("pause");
                break;
                for (int j = 0; j < i; j++) {
                    free(itemCombination[j]);
                }
                break;
            }
            default:{
                printf("Tolong masukkan opsi menu yang valid! >.<\n");
                break;
            }
        }

    } while (option != 0);

    free(root);

    return 0;
}
