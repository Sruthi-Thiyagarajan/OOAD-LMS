#include "bookstudent.h"


string bookstudent::getbookname(){return bookname;}
string bookstudent::getstudentname(){return studentname;}
int bookstudent::getlikealready(){return likealready;}
string bookstudent::getreview(){return review;}

void bookstudent::setbookname(string bn) {bookname = bn;}
void bookstudent::setstudentname(string sn) {studentname = sn;}
void bookstudent::setlikealready(int la) {likealready = la;}
void bookstudent::setreview(string rv){review = rv;}
