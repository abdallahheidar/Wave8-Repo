#include "payment1.h"

int x=0;
char transctiondateUser[100];                           //string for transaction date that user enter it
int y = 0;
//Implement the Card-side APIs

void fillCardData(ST_transaction *transaction){         //Get the card data from the user
printf("Please, Enter Card holder Name..\n");
gets(transaction->cardHolderData.cardHolderName);
printf("Please, Enter the Primary Account Number:\n");
gets(transaction->cardHolderData.primaryAccountNumber);
printf("Please, Enter the Card Expiry Date:\n");
gets(transaction->cardHolderData.cardExpirationDate);
}



void checkAmount(ST_transaction *transaction){
char result = strcmp(transaction->transData.transAmount,transaction->transData.maxTransAmount);

if(result>0){
printf("The transaction is DECLINED:\n");     //we wan to save the response here
}

}

//Implement the Terminal-Side APIs.

void fillTerminalData(ST_transaction *transaction){
//It fills the transaction amount, maximum
//transaction amount and expiry date in the ST_transaction structure.
printf("Please Enter the transaction Amount:\n");
gets(transaction->transData.transAmount);
//check if the amount > maximum transaction Amount the maximum transaction amount is (5000.00)
strcpy(transaction->transData.maxTransAmount,"5000");
checkAmount(transaction);
}




void checkExpiryDate(ST_transaction *transaction){
    printf("Please Enter transaction Date\n");
    gets(transaction->transData.transactionDate);      //scan the transaction date that user enter

char result = strcmp(transaction->transData.transactionDate,transaction->cardHolderData.cardExpirationDate);

if(result>0){
    printf("Transaction is DECLINED!\n");
    }else{//saveTransactionIntoServer(ST_transaction *transaction);

        }
}



//Implement the Server-Side APIs

void saveTransactionIntoServer(ST_transaction *transaction){   //checks the expiry  date

checkExpiryDate(transaction);
checkBalance(transaction);
}


void checkBalance(ST_transaction *transaction){
for(int i=0;i<10;i++){
char result = strcmp(PrimaryNumberBalance[i].primaryAccountNumber,transaction->cardHolderData.primaryAccountNumber);
    if(result>0){
           if(strcmp(PrimaryNumberBalance[i].balance,transaction->transData.transAmount)){
            transaction->transResponse.transactionStatus = APPROVED;
            y++;
            transaction->transResponse.receiptReferenceNumber = y;
            printf("The transaction is DECLINED");
                    }else{  //balance is not equivalent
                         transaction->transResponse.transactionStatus = DECLINED;
                         y++;
                         transaction->transResponse.receiptReferenceNumber = y ;
                         printf("The transaction is DECLINED");
                        }
                        }else{      //Else if the primary account number is not found, store the transaction in the server array in a unique position with the DECLINED response and the transaction reference number.
                        transaction->transResponse.transactionStatus= DECLINED ;
                        printf("The transaction is DECLINED");
                        }
}

}
