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
        printf("2. Lihat barang dalam sebuah transaksi. \n");
        printf("3. Cetak semua transaksi. \n");
        printf("0. Exit \n");
        scanf("%d", &choice);
        switch(choice){
            case 1:{
                char beliItem[20];
                while (1)
                {
                    printf("Input barang yang ingin anda beli (input 0 jika selesai.): ");
                    scanf("%s", beliItem);
                    if(beliItem != "0"){
                        addItem(&itemlist, beliItem);
                    }
                    newTransaction(&firstTransaction, &lastTransaction, itemlist);
                    itemlist = NULL; // agar list kosong lagi karena yang sebelumnya sudah selesai.
                    }
                break;
            }
            case 2:{
                printf("Cetak item dalam transaksi dengan ID: ");
                scanf("%d", &inputID);
                if (searchTransaction(inputID, firstTransaction) == NULL){
                    printf("Transaksi dengan ID %d tidak ditemukan!", inputID);
                } else {
                    printItems(searchTransaction(inputID, firstTransaction));
                    system("pause");
                }
                break;
            }
            case 3:{
                printAllTransactions(firstTransaction);
                system("pause");
                break;
            }
            case 4:{
                saveTransactions(firstTransaction);
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
