#ifndef BOOK_H
#define BOOK_H

#include <bits/stdc++.h>
#include <iostream>
class Publisher;

using namespace std;

class Book
{
private:
    int rowid=-1;
    string Name;
    int Price;
    bool state;
    string type;
    string imagePath;
    Publisher* publisher;
    bool availability;
    string publisher_name;
    string borrowed_by="";
    int like=0;
    string borrowedDate="", expectedReturnDate="", actualReturnDate="" ;
    string ISBN;
public:
    Book();
    Book(string name , string type , string author, int price = 0 , bool State = true, bool Availability = true, int Like=0, int rowid=-1);

    // ========= Setters ===========
    void setName(string);
    void setPrice(int);
    void setType(string);
    void setPublisher(Publisher*);
    void setPublisherName(string);
    void setImagePath(string);
    void setState(bool);
    void setAvailability(bool);
    void setBorrowedDate(string);
    void setExpectedReturnDate(string);
    void setActualReturnDate(string);
    void setRowId(int);
    void setLike(int);
    void incLike();
    void decLike();
    void setborrowed_by(string);
    void setISBN(string isbn);

    // ========== Getters ===========
    int getLike();
    int getRowId();
    string getName();
    int getPrice();
    string getType();
    Publisher* getPublisher();
    string getPublisherName();
    string getImagePath();
    bool getState();
    bool getAvailability();
    string getBorrowedDate();
    string getExpectedReturnDate();
    string getActualReturnDate();
    string getborrowed_by();
    void showInfo();
    bool operator == (Book&);
    string getISBN();
};

#endif // BOOK_H
