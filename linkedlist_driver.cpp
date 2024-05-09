#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

#define debug printf

int main(){
    transactionsNode *firstTransaction = NULL, *lastTransaction = NULL;
    itemsetNode *itemlist = NULL;
    int choice;
    int inputID;
    
    while (1)
    {
        system("cls");
        printf("\n Menu \n");
        printf("1. Buat transaksi baru. \n");
        printf("2. Lihat daftar transaksi. \n");
        printf("0. Exit \n");
        scanf("%d", &choice);
        switch(choice){
            case 1:{
                char beliItem[20];
                while (1)
                {
                    printf("Input barang yang ingin anda beli: ");
                    scanf("%s", beliItem);
                    addItem(&itemlist, beliItem);
                    // debug("Item = %s \n", itemlist->item);
                    // debug("Item = %s \n", itemlist->next->item);

                    scanf("%d", &choice);
                    if(choice == 0){
                        newTransaction(&firstTransaction, &lastTransaction, itemlist);
                        // debug("%d", firstTransaction->ID);
                        // debug("%s", firstTransaction->transactionItem->item);
                        // debug("%s", firstTransaction->transactionItem->next->item);
                        break;
                    }
                }
            }
            case 2:{
                printf("Cetak item dalam transaksi dengan ID: ");
                scanf("%d", &inputID);
                if (searchTransaction(inputID, firstTransaction) == NULL){
                    printf("Transaksi dengan ID %d tidak ditemukan!", inputID);
                } else {
                    printItems(searchTransaction(inputID, firstTransaction));
                }
                break;
            }
            case 0:{
                return 0;
            }
            break;
        }
    }
    
    return 0;
}
