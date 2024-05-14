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
        printf("| 6 | Kombinasi Item dari Trie \n");
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
                    scanf(" %[^\n]s", namaItem);
                    // Jika nama item = 0, maka sambungkan list item ke list transaksi.
                    // Jika bukan, maka sambungkan item baru ke list item.
                    if(strcmp(namaItem, "0") != 0){
                        addItem(&itemlist, namaItem);
                        numItem++;
                    } else {
                        newTransaction(&firstTransaction, &lastTransaction, itemlist);
                        addItemtoTrie(&root, itemlist);
                        itemlist = NULL; // Kosongkan list item.
                        break;
                    }
                }
                transaction++;
                system("pause");
                break;
            }
            case 2:{
                system("CLS");
                menuHeader();
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
                system("CLS");
                menuHeader();
                printAllTransactions(firstTransaction);
                system("pause");
                break;
            }
            case 5:{
                system("CLS");
                menuHeader();
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
                printf("------ \n");
                printf("Confidence: %.2f \n", calculateConfidence(firstTransaction, itemCombination));
                system("pause");
                break;
                for (int j = 0; j < i; j++) {
                    free(itemCombination[j]);
                }
                break;
            }
            case 6:{
                system("CLS");
                menuHeader();
                getItemCombination(root);
                system("pause");
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
