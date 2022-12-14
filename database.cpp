#include "database.h"
#include "book.h"
#include "publisher.h"
#include "student.h"
#include "bookstudent.h"

DataBase::DataBase()
{

}

void DataBase::init(QString path)
{
    this->db = QSqlDatabase ::addDatabase("QSQLITE");
    QString Path = path + "/../../OOAD-LMS/ray2.db";

    Path.toStdString();

    this->db.setDatabaseName(Path);

    this->db.open();

    if (!this->db.isOpen())
        cout << "db doesn't open" << endl;
    else
        cout << "db is open" << endl;

}

QSqlQuery* DataBase::getBookTableHandle()
{
    QSqlQuery* qry = new QSqlQuery(this->db);
    qry->prepare("select Name as BookName, Type, Price, Author, Availability, borrowedBy as Member,ISBN from books");
    qry->exec();
    return qry;
}

QSqlQuery* DataBase::getBorrowedTableHandle()
{
    QSqlQuery* qry = new QSqlQuery(this->db);
    qry->prepare("select borrowedBy as MEMBER, Name as BOOKNAME, borrowedDate as BORROWEDDATE, expectedReturnDate as EXPECTEDRETURNDATE from books where borrowedBy!=?");
    qry->bindValue(0,QString::fromStdString(""));
    qry->exec();
    return qry;
}

bool DataBase::updateMymessage(Book b)
{
    Student s;
    QDate d=QDate::currentDate();
    string ds = d.toString().toStdString();
    string rd = b.getExpectedReturnDate();
    string str = ds + ":   Your Book:  "+b.getName()+"  is due on  " + rd + ".  If returned, please ignore this message. For more details, check your 'MY BOOKS' tab.\n";
    s = loadStudent(b.getborrowed_by());
    string old = s.getMessage();
    old+=str;
    QSqlQuery query(this->db);
    query.prepare("UPDATE Students SET Mymessage=? WHERE Name = ? ;");
    query.bindValue(0,QString::fromStdString(old));
    query.bindValue(1,QString::fromStdString(b.getborrowed_by()));
    return query.exec();
}

bool DataBase::saveBook(Book book)
{
    QSqlQuery check(this->db);
    check.prepare("SELECT * FROM Books WHERE Name=?;");
    check.bindValue(0,QString::fromStdString(book.getName()));
    check.exec();
    QSqlQuery query(this->db);
    query.prepare("INSERT INTO Books(Name,Type,Price,Author,borrowedDate,expectedReturnDate,actualReturnDate,State,Availability,imagePath,ISBN) VALUES(?,?,?,?,?,?,?,?,?,?,?);");
    query.bindValue(0,QString::fromStdString(book.getName()));
    query.bindValue(1,QString::fromStdString(book.getType()));
    query.bindValue(2,book.getPrice());
    query.bindValue(3,QString::fromStdString(book.getPublisherName()));
    query.bindValue(4,QString::fromStdString(book.getBorrowedDate()));
    query.bindValue(5,QString::fromStdString(book.getExpectedReturnDate()));
    query.bindValue(6,QString::fromStdString(book.getActualReturnDate()));
    query.bindValue(7,book.getState());
    query.bindValue(8,book.getAvailability());
    query.bindValue(9,QString::fromStdString(book.getImagePath()));
    query.bindValue(10, QString::fromStdString(book.getISBN()));
    //query.bindValue(10,book.getLike());
    query.exec();
    return true;
}

bool DataBase::removeBook(Book book)
{
    QString book_key = QString::fromStdString(book.getName());
    QSqlQuery query(this->db);
    query.prepare("DELETE FROM Books WHERE Name = ?");
    query.bindValue(0,book_key);
    query.exec();
    cout<<"Book remove db called"<<endl;
    // Delete the entry of the book from the book DB(like-review)
    QSqlQuery q(this->db);
    QString str= "DELETE FROM "+ book_key;
    cout<<str.toStdString()<<endl;
    q.exec(str);
    return true;
}

bool DataBase::saveStudent(Student student)
{
    QSqlQuery check(this->db);
    check.prepare("SELECT * FROM Students WHERE Name=?;");
    check.bindValue(0,QString::fromStdString(student.getName()));
    check.exec();
    if(check.next())
        return false;
    QSqlQuery query(this->db);
    query.prepare("INSERT INTO Students(Name,Email,Password) VALUES(?,?,?);");
    query.bindValue(0,QString::fromStdString(student.getName()));
    query.bindValue(1,QString::fromStdString(student.getEmail()));
    query.bindValue(2,QString::fromStdString(student.getPassword()));
    //query.bindValue(3,student.getCash());
    query.exec();
    return true;
}

bool DataBase::savetransactiondetails(Transaction t)
{
    QSqlQuery query(this->db);
    query.prepare("INSERT INTO CardData(Name,CardName,CardNumber,CVV,Expiry,walletcash) VALUES(?,?,?,?,?,?);");
    query.bindValue(0,QString::fromStdString(t.getName()));
    query.bindValue(1,QString::fromStdString(t.getCardName()));
    query.bindValue(2,QString::fromStdString(t.getCardNumber()));
    query.bindValue(3,QString::fromStdString(t.getCVV()));
    query.bindValue(4,QString::fromStdString(t.getexpiry_date()));
    query.bindValue(5,t.getwalletcash());
    return query.exec();
}
bool DataBase::savePublisher(Publisher publisher)
{
    QSqlQuery check(this->db);
    check.prepare("SELECT * FROM Publishers WHERE Name=?;");
    check.bindValue(0,QString::fromStdString(publisher.getName()));
    check.exec();
    if(check.next())
        return false;
    QSqlQuery query(this->db);
    query.prepare("INSERT INTO Publishers(Name,Email,Password,cashAmount) VALUES(?,?,?,?);");
    query.bindValue(0,QString::fromStdString(publisher.getName()));
    query.bindValue(1,QString::fromStdString(publisher.getEmail()));
    query.bindValue(2,QString::fromStdString(publisher.getPassword()));
    query.bindValue(3,publisher.getCash());
    query.exec();
    return true;
}
void DataBase::updateStudent(Student student , string oldStuName)
{

    QSqlQuery query(this->db);
    query.prepare("UPDATE Students SET Name=?,Email=?,Password=?,cashAmount=?,currentBook=?,requestedBook=?,borrowedBooks=? WHERE Name = ? ;");
    query.bindValue(0,QString::fromStdString(student.getName()));
    query.bindValue(1,QString::fromStdString(student.getEmail()));
    query.bindValue(2,QString::fromStdString(student.getPassword()));
    //query.bindValue(3,student.getCash());
    query.bindValue(4,QString::fromStdString(student.getCurrentBookName()));
    query.bindValue(5,QString::fromStdString(student.getRequestedBookName()));
    query.bindValue(6,QString::fromStdString(student.getborrowed_books()));
    query.bindValue(7,QString::fromStdString(oldStuName));
    query.exec();

}

void DataBase::updateStudent(Student student , string oldStuName, Transaction t)
{
    QSqlQuery query(this->db);
    query.prepare("UPDATE Students SET Name=?,Email=?,Password=?,currentBook=?,requestedBook=?,borrowedBooks=? WHERE Name = ? ;");
    query.bindValue(0,QString::fromStdString(student.getName()));
    query.bindValue(1,QString::fromStdString(student.getEmail()));
    query.bindValue(2,QString::fromStdString(student.getPassword()));
    //query.bindValue(3,student.getCash());
    query.bindValue(3,QString::fromStdString(student.getCurrentBookName()));
    query.bindValue(4,QString::fromStdString(student.getRequestedBookName()));
    query.bindValue(5,QString::fromStdString(student.getborrowed_books()));
    query.bindValue(6,QString::fromStdString(oldStuName));
    query.exec();
    updateTransaction(t,oldStuName);
}

void DataBase::updateTransaction(Transaction t, string name)
{
    QSqlQuery q(this->db);
    q.prepare("UPDATE CardData SET Name=?,CardName=?,CardNumber=?,CVV=?,Expiry=?,walletcash=? WHERE Name = ? ;");
    q.bindValue(0,QString::fromStdString(t.getName()));
    q.bindValue(1,QString::fromStdString(t.getCardName()));
    q.bindValue(2,QString::fromStdString(t.getCardNumber()));
    q.bindValue(3,QString::fromStdString(t.getCVV()));
    q.bindValue(4,QString::fromStdString(t.getexpiry_date()));
    q.bindValue(5,t.getwalletcash());
    q.bindValue(6,QString::fromStdString(name));
    q.exec();
}
void DataBase::updatePublisher(Publisher publisher, string old_name)
{
    QSqlQuery query(this->db);
    query.prepare("UPDATE Publishers SET Name=?,Email=?,Password=?,cashAmount=? WHERE Name = ? ;");
    query.bindValue(0,QString::fromStdString(publisher.getName()));
    query.bindValue(1,QString::fromStdString(publisher.getEmail()));
    query.bindValue(2,QString::fromStdString(publisher.getPassword()));
    query.bindValue(3,publisher.getCash());
    query.bindValue(4,QString::fromStdString(old_name));
    query.exec();
}
void DataBase::updateBook(Book book , string oldBookName)
{
    QSqlQuery query(this->db);
    query.prepare("UPDATE Books SET Name=?,Type=?,Price=?,Author=?,borrowedDate=?,expectedReturnDate=?,actualReturnDate=?,State=?,Availability=?,imagePath=?,borrowedBy=? WHERE Name = ? ;");
    query.bindValue(0,QString::fromStdString(book.getName()));
    query.bindValue(1,QString::fromStdString(book.getType()));
    query.bindValue(2,book.getPrice());
    query.bindValue(3,QString::fromStdString(book.getPublisherName()));
    query.bindValue(4,QString::fromStdString(book.getBorrowedDate()));
    query.bindValue(5,QString::fromStdString(book.getExpectedReturnDate()));
    query.bindValue(6,QString::fromStdString(book.getActualReturnDate()));
    query.bindValue(7,book.getState());
    query.bindValue(8,book.getAvailability());
    query.bindValue(9,QString::fromStdString(book.getImagePath()));
    query.bindValue(10,QString::fromStdString(book.getborrowed_by()));
    query.bindValue(11,QString::fromStdString(oldBookName));
    query.exec();
}

void DataBase::updateBookByRowId(Book book, string rowid)
{
    QSqlQuery query(this->db);
    query.prepare("UPDATE Books SET Name=?,Type=?,Price=?,Author=?,borrowedDate=?,expectedReturnDate=?,actualReturnDate=?,State=?,Availability=?,imagePath=?,borrowedBy=? WHERE rowid = ? ;");
    query.bindValue(0,QString::fromStdString(book.getName()));
    query.bindValue(1,QString::fromStdString(book.getType()));
    query.bindValue(2,book.getPrice());
    query.bindValue(3,QString::fromStdString(book.getPublisherName()));
    query.bindValue(4,QString::fromStdString(book.getBorrowedDate()));
    query.bindValue(5,QString::fromStdString(book.getExpectedReturnDate()));
    query.bindValue(6,QString::fromStdString(book.getActualReturnDate()));
    query.bindValue(7,book.getState());
    query.bindValue(8,book.getAvailability());
    query.bindValue(9,QString::fromStdString(book.getImagePath()));
    query.bindValue(10,QString::fromStdString(book.getborrowed_by()));
    query.bindValue(11,QString::fromStdString(rowid));
    query.exec();
}

Book DataBase::loadBook(string name)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Type,Price,Author,borrowedDate,expectedReturnDate,actualReturnDate,State,Availability,imagePath,Like,rowid FROM "
                  "Books WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    Book book;
    while(query.next())
    {
        int available = query.value(8).toInt();
        if (!available)
            continue;
        book.setAvailability(available);
        book.setName(query.value(0).toString().toStdString());
        book.setType(query.value(1).toString().toStdString());
        book.setPrice(stoi(query.value(2).toString().toStdString()));
        book.setPublisherName(query.value(3).toString().toStdString());

        book.setBorrowedDate(query.value(4).toString().toStdString());
        book.setExpectedReturnDate(query.value(5).toString().toStdString());
        book.setActualReturnDate(query.value(6).toString().toStdString());
        book.setState(query.value(7).toInt());
        book.setImagePath(query.value(9).toString().toStdString());
        book.setLike(query.value(10).toInt());
        cout<<"My Row ID: "<<to_string(query.value(11).toInt())<<endl;
        book.setRowId(query.value(11).toInt());
        break;
    }
    return book;
}
Book DataBase::loadBookByRowId(string rowid)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Type,Price,Author,borrowedDate,expectedReturnDate,actualReturnDate,State,Availability,imagePath,Like,borrowedBy,rowid FROM "
                  "Books WHERE rowid=?;");
    query.bindValue(0,QString::fromStdString(rowid));
    query.exec();
    Book book;
    while(query.next())
    {
        book.setName(query.value(0).toString().toStdString());
        book.setType(query.value(1).toString().toStdString());
        book.setPrice(stoi(query.value(2).toString().toStdString()));
        book.setPublisherName(query.value(3).toString().toStdString());
        book.setBorrowedDate(query.value(4).toString().toStdString());
        book.setExpectedReturnDate(query.value(5).toString().toStdString());
        book.setActualReturnDate(query.value(6).toString().toStdString());
        book.setState(query.value(7).toInt());
        book.setAvailability(query.value(8).toInt());
        book.setImagePath(query.value(9).toString().toStdString());
        book.setLike(query.value(10).toInt());
        book.setborrowed_by(query.value(11).toString().toStdString());
        book.setRowId(query.value(12).toInt());
    }
    return book;
}
Book DataBase::loadBookForce(string name)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Type,Price,Author,borrowedDate,expectedReturnDate,actualReturnDate,State,Availability,imagePath,Like,rowid FROM "
                  "Books WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    Book book;
    while(query.next())
    {
        book.setName(query.value(0).toString().toStdString());
        book.setType(query.value(1).toString().toStdString());
        book.setPrice(stoi(query.value(2).toString().toStdString()));
        book.setPublisherName(query.value(3).toString().toStdString());
        book.setBorrowedDate(query.value(4).toString().toStdString());
        book.setExpectedReturnDate(query.value(5).toString().toStdString());
        book.setActualReturnDate(query.value(6).toString().toStdString());
        book.setState(query.value(7).toInt());
        book.setAvailability(query.value(8).toInt());
        book.setImagePath(query.value(9).toString().toStdString());
        book.setLike(query.value(10).toInt());
        book.setRowId(query.value(11).toInt());
        break;
    }
    return book;
}

//********************
//********************* check book table and row**************
// ****************** Create talbe and/or insert a new row ****************

bool DataBase::insertNewRowInBookStudent(bookstudent bs)
//  ************To Do: insert a row if the studentName is not existent *************
{


    string bookName = bs.getbookname();
    std::string::iterator end_pos = std::remove(bookName.begin(), bookName.end(), ' ');
    bookName.erase(end_pos, bookName.end());
    string studentName = bs.getstudentname();

    // check the table "bookName" exists or not
    QSqlQuery queryCreate(this->db);
    string query_string_create = "CREATE TABLE IF NOT EXISTS " + bookName + "(studentName text, likeAlready int, review text);";
    queryCreate.prepare(QString::fromStdString(query_string_create));
    queryCreate.exec();

    // check the row "studentName" exists or not
    QSqlQuery queryCheck(this->db);
    string query_string_check = "SELECT studentName from " + bookName;
    queryCheck.prepare(QString::fromStdString(query_string_check));
    queryCheck.exec();
    int found = false;
    while (queryCheck.next()){
        string targetStudent = queryCheck.value(0).toString().toStdString();
        if (targetStudent == studentName)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {   // if not found the studentName, add a new row
        string query_insert = "INSERT INTO " + bookName + " (studentName, likeAlready, review) VALUES (?,?,?);";
        QSqlQuery queryInsert(this->db);
        queryInsert.prepare(QString::fromStdString(query_insert));
        queryInsert.bindValue(0,QString::fromStdString(studentName));
        queryInsert.bindValue(1,QString::fromStdString(to_string(0)));
        queryInsert.bindValue(2,QString::fromStdString(""));
        queryInsert.exec();
    }
    return true;
}



//********************
//int DataBase::checkLikeStatus(string bookName, string studentName)
int DataBase::checkLikeStatus(bookstudent bs)
{   string bookName = bs.getbookname();
    std::string::iterator end_pos = std::remove(bookName.begin(), bookName.end(), ' ');
    bookName.erase(end_pos, bookName.end());
    string studentName = bs.getstudentname();
    int likeAlready;
    int test = 11;

    insertNewRowInBookStudent(bs);
    QSqlQuery query(this->db);
    string query_string = "SELECT likeAlready from " + bookName + " where studentName = ?;";
    query.prepare(QString::fromStdString(query_string));

    query.bindValue(0, QString::fromStdString(studentName));
    if(query.exec())
        test= 222;
    //if (query.next())
    //    test = 234;
    while (query.next())
        likeAlready = query.value(0).toInt();
    return likeAlready;
}


bool DataBase::saveReview(string review, bookstudent bs)
{
    int test = 111;
    string bookName = bs.getbookname();
    std::string::iterator end_pos = std::remove(bookName.begin(), bookName.end(), ' ');
    bookName.erase(end_pos, bookName.end());
    string studentName = bs.getstudentname();;
    insertNewRowInBookStudent(bs);
    QSqlQuery query(this->db);
    string query_string = "UPDATE " + bookName + " SET review = ? WHERE studentName =?;";
    query.prepare(QString::fromStdString(query_string));
    query.bindValue(0, QString::fromStdString(review));
    query.bindValue(1, QString::fromStdString(studentName));
    if(query.exec())
        test = 222;
    return true;
}
vector<string> DataBase::loadReview(string bookName)
{
    QSqlQuery query(this->db);
    std::string::iterator end_pos = std::remove(bookName.begin(), bookName.end(), ' ');
    bookName.erase(end_pos, bookName.end());
    vector<string> review;
    string query_string = "SELECT review from " + bookName + ";";
    query.exec(QString::fromStdString(query_string));

    while (query.next())
        review.push_back(query.value(0).toString().toStdString());
    return review;

}
bool DataBase::saveBookLikeDB(bookstudent bs, int liked)
{
    int test = 111;
    string bookName = bs.getbookname();
    std::string::iterator end_pos = std::remove(bookName.begin(), bookName.end(), ' ');
    bookName.erase(end_pos, bookName.end());
    string studentName = bs.getstudentname();
    QSqlQuery query(this->db);
    string query_string = "UPDATE " + bookName + " SET likeAlready = ? WHERE studentName = ?;";
    query.prepare(QString::fromStdString(query_string));
    query.bindValue(0,QString::fromStdString(to_string(liked)));
    query.bindValue(1,QString::fromStdString(studentName));
    if(query.exec())
        test = 222;
    //update all the info in Books
    int curLike;
    int nextLike;
    QSqlQuery query1(this->db);
    QSqlQuery query2(this->db);
    query1.prepare("SELECT Like from BOOKS where Name = ?");
    query1.bindValue(0, QString::fromStdString(bs.getbookname()));
    query1.exec();
    while (query1.next())
    {
        curLike = query1.value(0).toInt();
        if (liked == 1)
            nextLike = curLike + 1;
        else
            nextLike = curLike - 1;
        query2.prepare("UPDATE Books SET Like = ? WHERE Name = ?");
        query2.bindValue(0, QString::fromStdString(to_string(nextLike)));
        query2.bindValue(1, QString::fromStdString(bs.getbookname()));
        if(query2.exec())
            test = 333;
    }

    return true;

}

Student DataBase::loadStudent(string name)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Email,Password,cashAmount,currentBook,requestedBook,borrowedBooks,searchHistory,favoriteBooks, Mymessage FROM Students WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    Student student;
    while(query.next())
    {
        student.setName(query.value(0).toString().toStdString());
        student.setEmail(query.value(1).toString().toStdString());
        student.setPassword(query.value(2).toString().toStdString());

        //student.setCash(stoi(query.value(3).toString().toStdString()));
        student.setCurrentBook(query.value(4).toString().toStdString());
        student.setRequestedBook(query.value(5).toString().toStdString());
        student.setborrowed_books(query.value(6).toString().toStdString());

        student.addBorrowedBooks(split_string(query.value(6).toString().toStdString(),","));
        student.addSearchHistory(split_string(query.value(7).toString().toStdString(),","));
        student.addFavoriteBooks(split_string(query.value(8).toString().toStdString(),","));
        student.setMessage(query.value(9).toString().toStdString());
    }
    return student;
}
Transaction DataBase::loadtransaction(string name)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,CardName,CardNumber,CVV,Expiry,walletcash FROM CardData WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    Transaction n;
    while(query.next())
    {
        n.setName(query.value(0).toString().toStdString());
        n.setCardName(query.value(1).toString().toStdString());
        n.setCardNumber(query.value(2).toString().toStdString());
        n.setCVV(query.value(3).toString().toStdString());
        n.setexpiry_date(query.value(4).toString().toStdString());
        n.setwalletcash(query.value(5).toDouble());
    }
    return n;
}

Publisher DataBase::loadPublisher(string name)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Email,Password,cashAmount,my_books FROM Publishers WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    Publisher publisher;
    while(query.next())
    {
        publisher.setName(query.value(0).toString().toStdString());
        publisher.setEmail(query.value(1).toString().toStdString());
        publisher.setPassword(query.value(2).toString().toStdString());
        publisher.setCash(stoi(query.value(3).toString().toStdString()));
        // my_books
        vector<string> BooksNames = split_string(query.value(4).toString().toStdString(),",");
        for (int i =0 ; i< BooksNames.size(); i++)
            publisher.addBook(BooksNames[i]);
    }
    return publisher;
}

int DataBase::checkStudent(string name, string password)// 0:name,password are correct | 1:name wrong | 2:name correct & password wrong
{
    int mode=0;
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Password FROM Students where Name = ? ;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    string namee,pass;
    while(query.next())
    {
        namee = query.value(0).toString().toStdString();
        pass = query.value(1).toString().toStdString();
    }
    if(namee.empty())mode=1;
    else {if(pass!=password)mode=2;}
    return mode;
}
int DataBase::checkPublisher(string name, string password)
{
    int mode=0;
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,Password FROM Publishers where Name = ? ;");
    query.bindValue(0,QString::fromStdString(name));
    query.exec();
    string namee,pass;
    while(query.next())
    {
        namee = query.value(0).toString().toStdString();
        pass = query.value(1).toString().toStdString();
    }
    if(namee.empty())mode=1;
    else {if(pass!=password)mode=2;}
    return mode;
}

void DataBase::addPublisherBooks(Book book,string pubName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT my_books FROM Publishers WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(pubName));
    query.exec();
    string pubBooks;
    while(query.next())
       pubBooks = query.value(0).toString().toStdString();
    pubBooks += "," + book.getName();
    query.prepare("UPDATE Publishers SET my_books=? WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(pubBooks));
    query.bindValue(1,QString::fromStdString(pubName));
    query.exec();
}
void DataBase::addPublisherCash(int price , string pubName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT cashAmount FROM Publishers WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(pubName));
    query.exec();
    int cashAmount=0;
    while(query.next())
       cashAmount = query.value(0).toInt();
    cashAmount += price;
    query.prepare("UPDATE Publishers SET cashAmount=? WHERE Name=?;");
    query.bindValue(0,cashAmount);
    query.bindValue(1,QString::fromStdString(pubName));
    query.exec();
}
void DataBase::addCurrentBooks(Book book, string stuName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT currentBook FROM Students WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(stuName));
    query.exec();
    string currentBooks,currentBooksUnique="";
    while(query.next())
       currentBooks = query.value(0).toString().toStdString();
    if(currentBooks!="")currentBooks += "," + to_string(book.getRowId());
    else currentBooks += to_string(book.getRowId());
    vector<string> vec = split_string(currentBooks,",");
    sort( vec.begin(), vec.end() );
    vec.erase( unique( vec.begin(),vec.end() ), vec.end() );
    for(int i=0;i<vec.size();i++)
        currentBooksUnique+=vec[i]+",";
    currentBooksUnique = currentBooksUnique.substr(0, currentBooksUnique.size()-1);
    if(currentBooksUnique[0]==',')currentBooksUnique = currentBooksUnique.substr(1, currentBooksUnique.size());
    query.prepare("UPDATE Students SET currentBook=? WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(currentBooksUnique));
    query.bindValue(1,QString::fromStdString(stuName));
    query.exec();
}

void DataBase::addSearchHistory(Book book , string stuName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT searchHistory FROM Students WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(stuName));
    query.exec();
    string searchBooks,searchBooksUnique="";
    while(query.next())
       searchBooks = query.value(0).toString().toStdString();
    if(searchBooks!="")searchBooks += "," + book.getName();
    else searchBooks += book.getName();
    vector<string> vec = split_string(searchBooks,",");
    sort( vec.begin(), vec.end() );
    vec.erase( unique( vec.begin(),vec.end() ), vec.end() );
    for(int i=0;i<vec.size();i++)
        searchBooksUnique+=vec[i]+",";
    searchBooksUnique = searchBooksUnique.substr(0, searchBooksUnique.size()-1);
    if(searchBooksUnique[0]==',')searchBooksUnique = searchBooksUnique.substr(1, searchBooksUnique.size());
    query.prepare("UPDATE Students SET searchHistory=? WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(searchBooksUnique));
    query.bindValue(1,QString::fromStdString(stuName));
    query.exec();
}
void DataBase::addBorrowedBooks(Book book, string stuName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT borrowedBooks FROM Students WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(stuName));
    query.exec();
    string borrowedBooks,borrowedBooksUnique="";
    while(query.next())
       borrowedBooks = query.value(0).toString().toStdString();
    if(borrowedBooks!="")borrowedBooks += "," + book.getName();
    else borrowedBooks += book.getName();
    vector<string> vec = split_string(borrowedBooks,",");
    sort( vec.begin(), vec.end() );
    vec.erase( unique( vec.begin(),vec.end() ), vec.end() );
    for(int i=0;i<vec.size();i++)
        borrowedBooksUnique+=vec[i]+",";
    borrowedBooksUnique = borrowedBooksUnique.substr(0, borrowedBooksUnique.size()-1);
    if(borrowedBooksUnique[0]==',')borrowedBooksUnique = borrowedBooksUnique.substr(1, borrowedBooksUnique.size());
    query.prepare("UPDATE Students SET borrowedBooks=? WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(borrowedBooksUnique));
    query.bindValue(1,QString::fromStdString(stuName));
    query.exec();
}
void DataBase::addFavoriteBooks(Book book, string stuName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT favoriteBooks FROM Students WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(stuName));
    query.exec();
    string favoriteBooks,favoriteBooksUnique="";
    while(query.next())
       favoriteBooks = query.value(0).toString().toStdString();
    favoriteBooks += "," + book.getName();
    vector<string> vec = split_string(favoriteBooks,",");
    sort( vec.begin(), vec.end() );
    vec.erase( unique( vec.begin(),vec.end() ), vec.end() );
    for(int i=0;i<vec.size();i++)
        favoriteBooksUnique+=vec[i]+",";
    favoriteBooksUnique = favoriteBooksUnique.substr(0, favoriteBooksUnique.size()-1);
    if(favoriteBooksUnique[0]==',')favoriteBooksUnique = favoriteBooksUnique.substr(1, favoriteBooksUnique.size());
    query.prepare("UPDATE Students SET favoriteBooks=? WHERE Name=?;");
    query.bindValue(0,QString::fromStdString(favoriteBooksUnique));
    query.bindValue(1,QString::fromStdString(stuName));
    query.exec();
}


vector<Book> DataBase::searchBookByType(string type)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name FROM Books where Type = ? ;");
    query.bindValue(0,QString::fromStdString(type));
    query.exec();
    vector<Book> v;
    vector<string> ss;
    while(query.next())
        ss.push_back(query.value(0).toString().toStdString());
    for(int i=0 ; i<ss.size();i++)
        v.push_back(this->loadBookForce(ss[i]));
    return v;
}

vector<Book> DataBase::searchBookByISBN(string bookISBN)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name FROM Books where ISBN = ? ;");
    query.bindValue(0,QString::fromStdString(bookISBN));
    query.exec();
    vector<Book> v;
    vector<string> ss;
    while(query.next())
        ss.push_back(query.value(0).toString().toStdString());
    for(int i=0 ; i<ss.size();i++)
        v.push_back(this->loadBookForce(ss[i]));
    return v;
}
vector<Book> DataBase::searchBookByPrice(int price)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name FROM Books where Price <= ? ;");
    query.bindValue(0,price);
    query.exec();
    vector<Book> v;
    vector<string> ss;
    while(query.next())
        ss.push_back(query.value(0).toString().toStdString());
    for(int i=0 ; i<ss.size();i++)
        v.push_back(this->loadBookForce(ss[i]));
    return v;
}
vector<Book> DataBase::searchBookByPubName(string pubName)
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name FROM Books where Publisher = ? ;");
    query.bindValue(0,QString::fromStdString(pubName));
    query.exec();
    vector<Book> v;
    vector<string> ss;
    while(query.next())
        ss.push_back(query.value(0).toString().toStdString());
    for(int i=0 ; i<ss.size();i++)
        v.push_back(this->loadBookForce(ss[i]));
    return v;
}

map<string,string> DataBase::getAllBooks()
{
    QSqlQuery query(this->db);
    query.prepare("SELECT Name,imagePath FROM Books;");
    query.exec();
    map<string,string> name_imagePath ;
    while(query.next())
    {
        string name  = query.value(0).toString().toStdString() ;
        string imagePath = query.value(1).toString().toStdString();
        name_imagePath[name] = imagePath;
    }
    return name_imagePath;

}


vector<string> DataBase :: split_string(string s,string splitter)
{
    vector<string> splitted;
    uint n = s.length();
    int pos = 0;
    int start = pos;
    while (pos != string::npos)
    {
        pos = s.find_first_of(splitter,pos+1);
        string splitted_string = s.substr(start,pos-start);
        splitted.push_back(splitted_string);
        start = pos+1;
    }

    return splitted;
}
