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
    itemsetNode* listofItem = NULL;

    int option, numItem, transaction = 1;
    char namaItem[20];
    float support = 0.5;

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
        printf("| 5 | Update Nilai Support \n");
        printf("| 6 | Kombinasi Item dari Trie \n");
        printf("| 7 | Generate Association Rules \n");
        printf("| 0 | Exit Program\n");
        printf(">   Silahkan pilih option menu (masukkan angka nya) : ");
        scanf("%d", &option);

        switch (option) {
            case 1:{

                numItem = 1;~
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
                        generateItemList(&listofItem, itemlist);
                        // printItemList(listofItem);
                        // addItemtoTrie(&root, itemlist);
                        itemlist = NULL; // Kosongkan list item.
                        break;
                    }
                }
                updateTrie(&root, listofItem, firstTransaction, support);
                transaction++;
                system("pause");
                break;
            }
            case 2:{
                system("CLS");
                menuHeader();
                printf("Data Transaksi (Trie):\n");
                printf("Support = %.1f \n", support);
                printf("----------------------------------------------\n");
                printTrieFormatted(root);
                printf("----------------------------------------------\n");
                system("pause");
                break;
            }
            case 3:{
                system("CLS");
                menuHeader();
                printf("| -------------------------------------------\n");
                printf("Cari Data Transaksi:\n");
                printf("----------------------------------------------\n");
                char input[256];
                char *items[20];
                int itemCount = 0;

                printf("Enter items to search (comma separated): ");
                scanf(" %[^\n]", input);

                char *token = strtok(input, ", ");
                while (token != NULL) {
                    items[itemCount] = (char *)malloc(strlen(token) + 1);
                    strcpy(items[itemCount], token);
                    itemCount++;
                    token = strtok(NULL, ", ");
                }
                items[itemCount] = NULL;

                searchItemsInTrie(root, items, itemCount);

                for (int i = 0; i < itemCount; i++) {
                    free(items[i]);
                }
                system("pause");
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
                printf("| -------------------------------------------\n");
                printf("Update Nilai Support.\n");
                printf("Nilai support default: 0.5 \n");
                printf("Nilai support saat ini: %.1f \n", support);
                printf("----------------------------------------------\n");
                printf("Nilai support baru (ex. 0.5): ");
                scanf("%f", &support);
                if (support > 1){
                    support = support/10;
                }
                updateTrie(&root, listofItem, firstTransaction, support);
                break;
            }
            case 6:{
                system("CLS");
                menuHeader();
                printAllItemCombination(root);
                system("pause");
                break;
            }
            // case 7:{ //redundant
            //     system("CLS");
            //     float support;
            //     printf("Input support threshold: \n");
            //     scanf("%f", &support);  // Use %f to read a float value
            //     support = support / 10; // Divide by 10 if needed
            //     printf("Support threshold after division: %f\n", support);  // Print the support threshold
            //     updateTrie(&root, listofItem, firstTransaction, support);
            //     break;
            // }
            case 7:{
                system("CLS");
                float confidence;
                printf("Input confidence threshold (ex. 0.5): ");
                scanf("%f", &confidence);
                if (confidence > 1){
                    confidence = confidence/10;
                }
                generateAssociationRules(root, firstTransaction, confidence);

                // Define confidence thresholds
                const float confidenceThresholds[] = {2.0, 5.0, 10.0};
                int numThresholds = sizeof(confidenceThresholds) / sizeof(float);

                // Generate and save association rules for each confidence threshold
                generateAndSaveAssociationRules(root, firstTransaction, confidenceThresholds, numThresholds);

                system("pause");
                break;
            }
            case 0:{
                printf("Terima kasih....");
                break;
            }
            default:{
                system("CLS");
                printf("Tolong masukkan opsi menu yang valid! >.<\n");
            }
        }

    } while (option != 0);

    free(root);

    return 0;
}
