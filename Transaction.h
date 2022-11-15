#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "database.h"
using namespace std;

class Transaction
{
    string Name;
    string CardName;
    long int CardNumber;
    unsigned int CVV;
    string expiry_date;
public:
    Transaction();
    void setName(string);
    void setCardName(string);
    void setCardNumber(long int);
    void setCVV(unsigned int);
    void setexpiry_date(string);

    string getName();
    string getCardName();
    long int getCardNumber();
    unsigned int getCVV();
    string getexpiry_date();

    //add money from card to wallet
    void add_wallet_amt(double amt);

};

#endif // TRANSACTION_H
