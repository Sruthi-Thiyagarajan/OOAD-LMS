#ifndef DataBase_H
#define DataBase_H

#include <bits/stdc++.h>
#include <iostream>
#include "user.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QCoreApplication>
#include <QString>
#include <QSqlRecord>
#include <cstddef>
#include "Transaction.h"
#include <QSqlError>
using namespace std;

class Student;
class Publisher;
class Book;
class bookstudent;

class DataBase
{
private:
    QSqlDatabase db;
    vector<string> split_string(string s,string splitter);
public:

    DataBase();
    void init(QString);
    // savers
    bool saveBook(Book);
    bool removeBook(Book);
    bool saveStudent(Student);
    bool savePublisher(Publisher);
    bool savetransactiondetails(Transaction);
    //***************************
    bool saveBookLikeDB(bookstudent,int);
    bool saveReview(string, bookstudent);
    //***************************
    // update1
    void updateBook(Book,string);
    void updateBookByRowId(Book,string);
    void updateStudent(Student,string);
    void updatePublisher(Publisher,string);
    void addPublisherBooks(Book,string);
    void addPublisherCash(int,string);
    void addCurrentBooks(Book,string);
    void addSearchHistory(Book,string);
    void addBorrowedBooks(Book,string);
    void addFavoriteBooks(Book,string);
    // system search
    Book loadBookByRowId(string);
    Book loadBook(string);
    Book loadBookForce(string);
    Student loadStudent(string);
    Publisher loadPublisher(string);

    //*************
    vector<string> loadReview(string);

    //*************
    //checkers
    int checkStudent(string,string);
    int checkPublisher(string,string);
    //*********************
    int checkLikeStatus(bookstudent);

    //*********************
    // user search
    vector<Book> searchBookByType(string);
    vector<Book> searchBookByPrice(int);
    vector<Book> searchBookByPubName(string);

    map<string,string> getAllBooks();

    //    void saveLibrarian(Librarian);
    //    Book loadLibirian();
};
#endif // DataBase_H
