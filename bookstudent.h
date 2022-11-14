#ifndef BOOKTUDENT_H
#define BOOKTUDENT_H
#include<bits/stdc++.h>
#include<string>
using namespace std;
class bookstudent{
    string bookname;
    string studentname;
    int likealready;
    string review;
public:
    bookstudent()=default;
    string getbookname();
    string getstudentname();
    int getlikealready();
    string getreview();
    void setbookname(string bn);
    void setstudentname(string sn);
    void setlikealready(int lr);
    void setreview(string rv);

};
#endif // BOOKTUDENT_H
