// new changes test
#include "book.h"
#include "publisher.h"

Book::Book(string name, string Type, string author,
           int price, bool State , bool Availability, int Like, int rowid)
{
    Name = name;
    type = Type;
    publisher_name = author ;
    Price = price ;
    state = State;
    availability = Availability;
    this->rowid=rowid;
    like = Like;
}

Book::Book()
{

}

void Book::setISBN(string isbn)
{
    this->ISBN = isbn;
}

string Book::getISBN(){
    return this->ISBN;
}
void Book::setLike(int curLike){
    this->like = curLike;

}

void Book::incLike(){
    this->like += 1;
}
void Book::decLike(){
    this->like -= 1;
}
void Book::setName(string name)
{
    this->Name =  name;
}

void Book::setPrice(int price)
{
    this->Price = price;
}

void Book::setType(string Type)
{
    this->type = Type;
}

void Book::setPublisher(Publisher* myPublisher)
{
    this->publisher = myPublisher;
}

void Book::setPublisherName(string name)
{
    this->publisher_name = name;
}

void Book::setImagePath(string path)
{
    this->imagePath = path;
}

void Book::setState(bool State)
{
    this->state = State;
}

void Book::setAvailability(bool Availability)
{
    this->availability = Availability;
}

void Book::setBorrowedDate(string date)
{
    this->borrowedDate = date;
}

void Book::setExpectedReturnDate(string date)
{
    this->expectedReturnDate = date;
}

void Book::setActualReturnDate(string date)
{
    this->actualReturnDate = date ;
}

void Book::setRowId(int Rowid)
{
    this->rowid = Rowid;
}

void Book::setborrowed_by(string b)
{
    this->borrowed_by=b;
}

//
int Book::getLike()
{
    return this->like;
}

int Book::getRowId()
{
    return this->rowid;
}

string Book::getName()
{
    return this->Name;
}

int Book::getPrice()
{
    return this->Price;
}

string Book::getType()
{
    return this->type;
}

Publisher* Book::getPublisher()
{
    return publisher;
}

string Book::getPublisherName()
{
    return this->publisher_name;
}

string Book::getImagePath()
{
    return this->imagePath;
}

bool Book::getState()
{
    return this->state;
}

bool Book::getAvailability()
{
    return this->availability;
}

string Book::getBorrowedDate()
{
    return this->borrowedDate;
}

string Book::getExpectedReturnDate()
{
    return this->expectedReturnDate;
}

string Book::getActualReturnDate()
{
    return this->actualReturnDate;
}

string Book::getborrowed_by()
{
    return this->borrowed_by;
}

void Book::showInfo()
{
    cout << "Name:" << this->Name ;
    cout << endl;
    cout << "Price:" << this->Price;
    cout << endl;
    cout << "State:" << this->state;
    cout << endl;
    cout << "Type:" << this->type ;
    cout << endl;
    cout << "Like" << this->like;
    cout << endl;
    cout << "Publisher_name: " << this->publisher_name << endl;
}

bool Book::operator ==(Book &)
{

}
