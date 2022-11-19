#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "book.h"
#include <bits/stdc++.h>
#include "publisher.h"
#include "student.h"
#include "user.h"
#include "database.h"
#include "bookstudent.h"
#include "librarian.h"
#include <QObject>
#include "GUI/indexs.h"
#include <vector>
#include <string>
#include "Transaction.h"
using namespace std;

class Controller : public QObject
{
    Q_OBJECT
private:
    DataBase db;
    vector<string> split_string(string,string);

public :
    Controller();
    void start();

    void studentLoggedIn(string);
    void publisherLoggedIn(string);
    string join_string(vector<string>,string);

public slots:

    void log_in(string name , string password , int choice);
    void sign_up(string ,string ,string,int,Transaction);
    // Admin
    void Upload_book(string ,string,string,int);
    void removeBookData(Book);
    void updatePublisher(string ,string,string,string,int);
    void updateStudent(string,string,string,string,Transaction);

    // books
    void searchBookByName(string,string);
    void searchBookByType(string,string);
    void searchBookByPrice(int,string);
    void searchBookByPub(string,string);
    void borrowBook(string,string,string);
    int checkLikeAlready(bookstudent);
    void saveBookLikeDB(bookstudent, int);
    vector<string> loadReview(string);
    void saveReview(string,bookstudent);
    void returnBook(string,string);
    void addAmount(double,string);
    void aa(string);
    // for member
    void getBookInfo(string);
    // for admin
    void getbookInfo(string);
    void getSearchHistory(string);
    map<string,string> getAllBooks();
    QSqlQuery* getbooktablehandle();

signals:

    void error(string);
    void error_login(string);
    void studentLoggedin(Student,Transaction);
    void transactionupdate(Transaction);
    void publisherLoggedin(Publisher);
    void setCurrentWidget(int index);

    // books
    void error_noBook(string);
    // for member
    void bookInfo(Book);
    //for admin
    void bookInfoAdmin(Book);
    void error_return(string);
    void update_wallet(string);
    void bookReturned(double,int);
    void borrowedBooks(vector<Book>);
    void booksFound(vector<Book>);
    void searchedBooks(vector<string>);


};

#endif // CONTROLLER_H
