#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <bits/stdc++.h>
using namespace std;

class Transaction
{
    string Name;
    string CardName;
    string CardNumber;
    string CVV;
    string expiry_date;
    double walletcash=0.0;
public:
    Transaction();
    void setName(string);
    void setCardName(string);
    void setCardNumber(string);
    void setCVV(string);
    void setexpiry_date(string);
    void setwalletcash(double);

    string getName();
    string getCardName();
    string getCardNumber();
    string getCVV();
    string getexpiry_date();
    double getwalletcash();
    //add money from card to wallet
    void add_wallet_amt(double amt);

};

#endif // TRANSACTION_H
