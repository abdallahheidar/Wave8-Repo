

typedef struct ST_cardData
{
	unsigned char cardHolderName[25];
	unsigned char primaryAccountNumber[19];
	unsigned char cardExpirationDate[6];
}ST_cardData;


typedef struct ST_trminalData
{
	unsigned char transAmount[8];
    unsigned char maxTransAmount[8];
    unsigned char transactionDate[11];
}ST_trminalData;



typedef enum EN_transStat
{
	DECLINED,
	APPROVED
}EN_transStat;

typedef struct ST_serverData
{
	EN_transStat transactionStatus;
    unsigned int receiptReferenceNumber;
}ST_serverData;

typedef struct ST_transaction
{
	ST_cardData cardHolderData;
	ST_trminalData transData;
	ST_serverData transResponse;
}ST_transaction;

typedef struct ST_accountBalance
{
	unsigned char balance[8];
	unsigned char primaryAccountNumber[19];
}ST_accountBalance;

ST_accountBalance PrimaryNumberBalance[10]={{"0100.00","123456789"},{"6000.00","234567891"},{"3250.25","567891234"},{"1500.12","456789123"},{"0500.00","258649173"},
                                            {"2100.00","654823719"},{"0000.00","971362485"},{"0001.00","793148625"},{"0010.12","123123456"},{"0000.55","456789321"}};

void fillCardData(ST_transaction *transaction);    //fills the card data structure into the ST_transaction structure.
void checkAmount(ST_transaction *transaction);      //reads the amount - checks if the amount> maximum transaction Amount (5000.00) - saves the response as DECLINE and prints "the transaction is declined"
void fillTerminalData(ST_transaction *transaction); //fills the transaction amount, maximum transaction amount and expiry date in the ST_transaction structure
void checkExpiryDate(ST_transaction *transaction);
void saveTransactionIntoServer(ST_transaction *transaction);
void checkBalance(ST_transaction *transaction);


