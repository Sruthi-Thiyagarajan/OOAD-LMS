#ifndef TRANSACTION
#define TRANSACTION

#include "Transaction.h"

Transaction::Transaction()
{
}

//setters
void Transaction::setName(string name)
{
    Name = name ;
}

void Transaction::setCardName(string name)
{
    CardName = name ;
}
void Transaction::setCardNumber(string num)
{
    CardNumber = num ;
}
void Transaction::setCVV(string cvv)
{
    CVV = cvv ;
}
void Transaction::setexpiry_date(string d)
{
    expiry_date = d;
}
void Transaction::setwalletcash(double d)
{
    walletcash = d;
}


//getters
string Transaction::getName()
{
    return this->Name;
}
string Transaction::getCardName()
{
    return this->CardName;
}
string Transaction::getCardNumber()
{
    return this->CardNumber;
}
string Transaction::getCVV()
{
    return this->CVV;
}
string Transaction::getexpiry_date()
{
    return this->expiry_date;
}
double Transaction::getwalletcash()
{
    return this->walletcash;
}

void Transaction::add_wallet_amt(double d)
{
    this->walletcash+=d;
}
#endif TRANSACTION
