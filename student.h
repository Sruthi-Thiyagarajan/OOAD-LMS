#ifndef STUDENT_H
#define STUDENT_H

#include <bits/stdc++.h>
#include "user.h"
#include "book.h"
#include "database.h"

using namespace std;

class Student : public User
{
private:
    vector<Book> currentBooks;
    string currentBook_name;
    string requestedBook_name;
    string borrowed_books;
    string Mymessage;
    vector<string> borrowedBooks_names;
    vector<string> searchHistory_names;
    vector<string> favoriteBooks_names;
    vector<string> split_string(string,string);

public:
    Student();
    Student(string name , string password,string email);
    // setters and adders
    //overloaded functions
    void setCurrentBook(string);
    void setRequestedBook(string);
    void setborrowed_books(string);
    void addBorrowedBooks(vector<string>);
    void addSearchHistory(vector<string>);
    void addFavoriteBooks(vector<string>);
    void showInfo();
    void setMessage(string message);
    // getters
    string getborrowed_books();
    vector<string> getborrow_books_vector();
    string getCurrentBookName();
    vector<Book> getCurrentBookVector(DataBase*);
    string getRequestedBookName();
    vector<string> getSearchHistory();
    string getMessage();

};

#endif // STUDENT_H
