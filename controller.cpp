#include "controller.h"
#include "qdatetime.h"

Controller::Controller() : QObject()
{
    QString path = QCoreApplication::applicationDirPath();
    this->db.init(path);
}
void Controller::start()
{
}

QSqlQuery* Controller::getbooktablehandle()
{
    return db.getBookTableHandle();
}

QSqlQuery* Controller::getborrowedtablehandle()
{
    return db.getBorrowedTableHandle();
}

void Controller::sendnotif(Book b)
{
    bool d = db.updateMymessage(b);
    string str="";
    if(d)str+="Message sent successfully.";
    else str+="Message unsuccessful.";
    emit display_msg(str);
}

void Controller::sign_up(string name ,string email , string password , int choice, Transaction t)
{
    Student student1;
    Publisher publisher1;
    if (choice == 1) // user is student
    {
        student1.setName(name);
        student1.setPassword(password);
        student1.setEmail(email);
        if(!db.saveStudent(student1))
        {
            emit error("Member Name already Exist ! Enter another name");
            cout << "Member Name already Exist ! Enter another name" << endl;
            return;
        }
        if(!db.savetransactiondetails(t))
        {
            emit error("Error in transaction details. Please create a new Account");
            cout<<"Transaction details error"<<endl;
            return;
        }
        cout<<"You signed up successfully"<<endl;
        this->log_in(name,password,choice);
    }
    else if(choice ==2)
    {
        publisher1.setName(name);
        publisher1.setPassword(password);
        publisher1.setEmail(email);
        if(!db.savePublisher(publisher1))
        {
            emit error("Admin already Exist ! Enter another name");
            cout << "Admin Name already Exist ! Enter another name" << endl;
            return;
        }
        if(!db.savetransactiondetails(t))
        {
            emit error("Error in transaction details. Please create a new Account");
            cout<<"Transaction details error"<<endl;
            return;
        }
        cout<<"You signed up successfully"<<endl;
        this->log_in(name,password,choice);
    }
}
void Controller::log_in(string name , string password , int choice)
{
    if(choice==1)
    {
        Student s; Transaction t;
        int mode = db.checkStudent(name,password);
        if (mode==1)
        {
            emit error_login("No name matches the name you entered");
        }
        else if(mode==2)
        {
            emit error_login("Wrong Password");
        }
        else if(mode==0)
        {
            s = db.loadStudent(name);
            t = db.loadtransaction(name);
            cout<<"You've logged in successfully"<<endl;
            emit studentLoggedin(s,t);
            emit setCurrentWidget(STUDENT_WIDGET);
        }
    }
    else if(choice==2)
    {
        Publisher p;
        int mode = db.checkPublisher(name,password);
        if (mode==1)
        {
            emit error_login("No name matches the name you entered");
        }
        else if(mode==2)
        {
            emit error_login("Wrong Password");
        }
        else if(mode==0)
        {
            p = db.loadPublisher(name);
            cout<<"You've logged in successfully"<<endl;
            emit publisherLoggedin(p);
            emit setCurrentWidget(PUBLISHER_WIDGET);
        }
    }

}
void Controller::publisherLoggedIn(string pubName)
{
    while(1)
    {
        cout <<"what do yo want to do ? \n";
        cout << "1-Upload book" << endl;
        cout << "2-Update book"<<endl;
        cout << "3-view books" << endl;
        cout << "4-view cash" << endl;
        cout << "5-view profile" << endl;
        cout << "6-edit profile"<<endl;
        cout << "7-Log Out"<<endl;
        int choice;
        cin>>choice;
        if(choice==1)
        {
            string name,type;
            int price;
            string isbn;
            cout<<"Enter Book Name : ";
            cin>>name;
            cout<<"Enter Book Type : ";
            cin>>type;
            cout<<"Enter Book Price : ";
            cin>>price;
            this->Upload_book(pubName,name,type,price,isbn);
        }
        else if(choice==2)
        {
            Book book1;
            string nameInitial,type,name;
            int price,x;
            cout<<"Which book you want to update? :";
            cin>>nameInitial;
            book1=db.loadBook(nameInitial);
            cout<<"What do you want to edit in this book ?"<<endl;
            cout<<"1-Name"<<endl;
            cout<<"2-Type"<<endl;
            cout<<"3-Price"<<endl;
            cin>>x;
            if(x==1){cout<<"Enter Book Name : ";cin>>name;book1.setName(name);}
            if(x==2){cout<<"Enter Book Type : ";cin>>type;book1.setType(type);}
            if(x==3){cout<<"Enter Book Price : ";cin>>price;book1.setPrice(price);}
            db.updateBook(book1,nameInitial);
        }
        else if(choice==3)
        {
            vector<string> s = db.loadPublisher(pubName).viewMyBooks();
            cout<<"Your books are : ";
            for (int i =0 ; i < s.size() ; i++)
                cout << s[i] << " ";
            cout << endl;
        }
        else if(choice==4) cout<<"You Have : "<< db.loadPublisher(pubName).getCash() << " L.E.\n" ;
        else if(choice==5) db.loadPublisher(pubName).showInfo();
        else if(choice==6)
        {
            Publisher pub;
            string email,name,pass;
            int cashAmount,x;
            pub=db.loadPublisher(pubName);
            cout<<"What do you want to edit in the profile ?"<<endl;
            cout<<"1-Name"<<endl;
            cout<<"2-Password"<<endl;
            cout<<"3-Email"<<endl;
            cout<<"4-Cash amount"<<endl;
            cin>>x;
            if(x==1){cout<<"Enter new Name : ";cin>>name;pub.setName(name);}
            if(x==2){cout<<"Enter new Password : ";cin>>pass;pub.setPassword(pass);}
            if(x==3){cout<<"Enter new Email : ";cin>>pass;pub.setPassword(pass);}
            if(x==4){cout<<"Enter new Cash amount : ";cin>>cashAmount;pub.setCash(cashAmount);}
            db.updatePublisher(pub,pubName);
            break;
        }
        else if(choice==7) return;
        else cout<<"Wrong Choice. "<<endl;
    }
}

void Controller::Upload_book(string pubName ,string name ,string type,int price, string isbn)
{
    Book book1;
    book1.setName(name);
    book1.setPrice(price);
    book1.setType(type);
    book1.setPublisherName(pubName);
    book1.setState(1);
    book1.setAvailability(1);
    book1.setISBN(isbn);
    db.saveBook(book1);
    cout<<"Book saved succesfully"<<endl;
}

void Controller::removeBookData(Book b)
{
    db.removeBook(b);
    cout<<"Book removed successfully"<<endl;
}
void Controller::searchBookByName(string BookNameOrID,string stuName)
{
    Book b;
    // check for available books
    b= db.loadBook(BookNameOrID);
    // if not found -> get any un available book to just show it to user and know that there is no available books
    if(b.getName().empty())
        b= db.loadBookForce(BookNameOrID);
    if(b.getName().empty())
    {
        emit error_noBook("Not Found Book");
        return;
    }
    emit bookInfo(b);
    Student s =db.loadStudent(stuName);
    db.addSearchHistory(b,stuName);
    db.updateStudent(s,stuName);
}

void Controller::searchBookByISBN(string bookISBN,string stuName)
{
    vector<Book> v = db.searchBookByISBN(bookISBN);
    Student s =db.loadStudent(stuName);
    for(int i=0;i<v.size();i++)
    {
        db.addSearchHistory(v[i],stuName);
        db.updateStudent(s,stuName);
    }

    emit booksFound(v);
}

void Controller::searchBookByType(string type , string stuName)
{
    vector<Book> v = db.searchBookByType(type);
    Student s =db.loadStudent(stuName);
    for(int i=0;i<v.size();i++)
    {
        db.addSearchHistory(v[i],stuName);
        db.updateStudent(s,stuName);
    }

    emit booksFound(v);
}

void Controller::searchBookByPrice(int price, string stuName)
{
    vector<Book> v = db.searchBookByPrice(price);
    emit booksFound(v);
    Student s =db.loadStudent(stuName);
    for(int i=0;i<v.size();i++)
    {
        db.addSearchHistory(v[i],stuName);
        db.updateStudent(s,stuName);
    }
}

void Controller::searchBookByPub(string pub, string stuName)
{
    vector<Book> v = db.searchBookByPubName(pub);
    emit booksFound(v);
    Student s =db.loadStudent(stuName);
    for(int i=0;i<v.size();i++)
    {
        db.addSearchHistory(v[i],stuName);
        db.updateStudent(s,stuName);
    }
}

int Controller::checkLikeAlready(bookstudent bs)
{   int likeAlready;
    likeAlready = db.checkLikeStatus(bs);

    return likeAlready;
}

vector<string> Controller::loadReview(string bookName)
{
    return db.loadReview(bookName);
}
void Controller::saveBookLikeDB(bookstudent bs, int isliked)
{
    db.saveBookLikeDB(bs, isliked);
}

void Controller::saveReview(string review, bookstudent bs){
    db.saveReview(review, bs);
}

void Controller::borrowBook(string bookName,string stuName,string expectedReturnDate)
{
    if(db.loadBook(bookName).getName().empty())
    {
        emit error_noBook("This book is not available");
        return;
    }
    else {
        QDate borrowDate= QDate::currentDate();
        Student s = db.loadStudent(stuName);
        Book b = db.loadBook(bookName);
        s.setCurrentBook(to_string(b.getRowId()));
        b.setBorrowedDate(borrowDate.toString().toStdString());
        b.setExpectedReturnDate(expectedReturnDate);
        b.setAvailability(0);
        b.setborrowed_by(stuName);
        db.addCurrentBooks(b,stuName);
        db.addBorrowedBooks(b,stuName);
        db.updateBookByRowId(b,to_string(db.loadBook(bookName).getRowId()));
        cout<<"You borrowed the book successfully, your book's ID is : "<<b.getRowId()<<endl;
        //cout<<"You will pay : "<<ceil((expectedReturnDate-borrowDate)/7.0)*b.getPrice()<<endl;
        cout<<"Warning 1 : if you return the book late, you'll pay a fee of 5$ for each week late"<<endl;
        cout<<"Warning 2 : if you return the book damaged, you'll pay a fee of half the book's price"<<endl;
    }
}

void Controller::addAmount(double amt, string stuName)
{
    Transaction t=db.loadtransaction(stuName);
    t.add_wallet_amt(amt);
    db.updateTransaction(t,stuName);
    emit transactionupdate(t);
    return;
}

void Controller::returnBook(string bookName, string stuName)
{
    int actualBorrowedPeriod,expectedBorrowedPeriod,rowid;
    QDate actualReturnDate;
    int borrowed_book_found=0,mode=0,zero_bal=0;
    vector<string> v, vborrowed;
    Book b; Transaction t;
    double bill=0.0;
    Student s=db.loadStudent(stuName);
    v= split_string(s.getCurrentBookName(),",");
    vborrowed = s.getborrow_books_vector();
    for(int i=0;i<v.size();i++)
    {
        cout<<"v[i] start:"<<v[i]<<endl;
        b = db.loadBookByRowId(v[i]);
        if(b.getName()==bookName)
        {
            borrowed_book_found=1;
            v.erase(v.begin()+i);
            break;
        }
        cout<<"v[i] end:"<<v[i]<<endl;
    }
    if(!borrowed_book_found)
        emit error_return("You didn't borrow this book");
    else
    {
          actualReturnDate=QDate::currentDate();
          cout<<"b date string : "<<b.getBorrowedDate()<<endl;
          QString bstring = QString::fromStdString(b.getBorrowedDate());
          QDate borrow_date = QDate::fromString(bstring,"ddd MMM dd yyyy");
          cout<<"B Date: "<<borrow_date.toString().toStdString()<<endl;
          QString expecstring = QString::fromStdString(b.getExpectedReturnDate());
          QDate expdate = QDate::fromString(expecstring,"ddd MMM dd yyyy");

          actualBorrowedPeriod = borrow_date.daysTo(actualReturnDate);
          expectedBorrowedPeriod= borrow_date.daysTo(expdate);

          cout <<"Actual B Period : "<<actualBorrowedPeriod<<endl;
          cout <<"Exp B Period : "<<expectedBorrowedPeriod<<endl;

          bill = ceil(actualBorrowedPeriod/7.0)*b.getPrice();
          if(actualBorrowedPeriod>expectedBorrowedPeriod)
          {
             double fee;
             fee=5*ceil((actualBorrowedPeriod-expectedBorrowedPeriod)/7.0);
             bill+=fee;
             mode=1;
          }
          cout<<"Bill is : "<<bill<<endl;
          if((t=db.loadtransaction(stuName)).getwalletcash()<bill)
          {
              cout << "In whileloop"<<endl;
              string str = "Your Bill is : $" + to_string(bill) + ". Please update your wallet with the required amount before returning. Click MY WALLET to update wallet.\n";
              cout<<str<<endl;
              zero_bal=1;
              emit update_wallet(str);

          }
          if(zero_bal)return;
          emit bookReturned(bill,mode);
          //Student DB update
          string current_books=join_string(v,",");
          cout<<"current books string:"<<current_books<<endl;
          s.setCurrentBook(current_books);
          for(int i=0;i<vborrowed.size();i++) {
              if(vborrowed[i]==bookName){
                  vborrowed.erase(vborrowed.begin()+i);
              }
          }
          string borrowed_books=join_string(vborrowed,",");
          cout<<"borrowed books string:"<<borrowed_books<<endl;
          s.setborrowed_books(borrowed_books);
          db.updateStudent(s,stuName);
          //Book DB update
          b.setExpectedReturnDate("");
          b.setBorrowedDate("");
          b.setActualReturnDate("");
          b.setborrowed_by("");
          b.setAvailability(1);
          b.setState(1);
          db.updateBookByRowId(b,to_string(b.getRowId()));
          //Transaction/CardData DB update
          t.add_wallet_amt(-1.0*bill);
          db.updateTransaction(t,stuName);
          emit transactionupdate(t);
          return;
    }
}

void Controller::aa(string stuName)
{
    vector<Book> v = db.loadStudent(stuName).getCurrentBookVector(&db);
    emit borrowedBooks(v);
}

void Controller::getBookInfo(string BookNameOrID)
{
    //Book b = db.loadBookByRowId(BookNameOrID);
    Book b;
    b= db.loadBook(BookNameOrID);
    if(b.getName().empty())
        b= db.loadBookForce(BookNameOrID);
    if(b.getName().empty())
    {
        emit error_noBook("Not Found Book");
        return;
    }
    emit bookInfo(b);
}

void Controller::getbookInfo(string bookName)
{
    Book b;
    b= db.loadBook(bookName);
    if(b.getName().empty())
        b= db.loadBookForce(bookName);
    if(b.getName().empty())
    {
        emit error_noBook("Not Found Book");
        return;
    }
    emit bookInfoAdmin(b);
}

void Controller::getSearchHistory(string stuName)
{
    Student s = db.loadStudent(stuName);
    vector<string> v = s.getSearchHistory();
    //could load books instead of bookNames
    emit searchedBooks(v);
}

map<string, string> Controller::getAllBooks()
{
    return this->db.getAllBooks();
}

void Controller::updatePublisher(string pubName, string name, string pass, string email, int cashAmount)
{
    Publisher p;
    p=db.loadPublisher(pubName);
    p.setName(name);
    p.setPassword(pass);
    p.setEmail(email);
    p.setCash(cashAmount);
    db.updatePublisher(p,pubName);
}

void Controller::updateStudent(string stuName, string name, string pass, string email, Transaction t)
{
    Student s;
    s=db.loadStudent(stuName);
    //n=db.loadtransaction(stuName);
    s.setName(name);
    s.setPassword(pass);
    s.setEmail(email);
    db.updateStudent(s,stuName);
}

void Controller::studentLoggedIn(string stuName)
{
    /*int choice;
    while(1)
    {
        cout<<"what do yo want to do ? "<<endl;
        cout << "1-Search" << endl;
        cout << "2-Borrow" << endl;
        cout << "3-Return" << endl;
        cout << "4-view search history" << endl;
        cout << "5-view favorite books" << endl;
        cout << "6-view your borrowed books"<<endl;
        cout << "7-check your cash"<<endl;
        cout << "8-view profile" << endl;
        cout << "9-edit profile" << endl;
        cout << "10-Log Out"<<endl;
        cin>>choice;
        if(choice==1)
        {
            int choice1;
            while(1){
                cout<<"Do you wanna search books by :"<<endl;
                cout<<"1-Name"<<endl;
                cout<<"2-Type"<<endl;
                //cout<<"3-Publisher"<<endl;
                cout<<"4-Price"<<endl;
                cout<<"5-Exit"<<endl;
                cin>>choice1;
                if(choice1==1)
                {
                    string name;
                    cout<<"Enter book's name : ";
                    cin>>name;
                    if(db.loadBook(name).getName().empty()) cout<<"Your book is not available :( "<<endl;
                    else {

                        Book ray2 = db.loadBook(name);
                        ray2.showInfo();
                    }
                    db.addSearchHistory(db.loadBook(name),stuName);
                }
                else if(choice1==2)
                {
                    string type;
                    cout<<"Enter type : ";
                    cin>>type;
                    vector<Book> v = db.searchBookByType(type);
                    cout<<"We've found "<<v.size()<<" books that matches your search :"<<endl;
                    for(int i=0; i<v.size();i++)
                    {  v[i].showInfo();
                        db.addSearchHistory(v[i],stuName);
                    }
                }
                else if(choice1==3)
                {
                    string publisherName;
                    cout<<"Enter name of publisher : ";
                    cin>>publisherName;
                    vector<Book> v = db.searchBookByPubName(publisherName);
                    cout<<"We've found "<<v.size()<<" books that matches your search :"<<endl;
                    for(int i=0; i<v.size();i++)
                    {
                        v[i].showInfo();
                        db.addSearchHistory(v[i],stuName);
                    }
                }
                else if(choice1==4)
                {
                    int price;
                    cout<<"Enter your price range : ";
                    cin>>price;
                    vector<Book> v = db.searchBookByPrice(price);
                    cout<<"We've found "<<v.size()<<" books that matches your search :"<<endl;
                    for(int i=0; i<v.size();i++)
                    {
                        v[i].showInfo();
                        db.addSearchHistory(v[i],stuName);
                    }
                }
                else if (choice1==5) break;
                else cout<<"Wrong choice , rakkez b2a mate2refnash"<<endl;
            }
        }
        else if(choice==2)
        {
            string name;Librarian l;
            int borrowDate,expectedReturnDate;
            cout<<"Enter book's name : ";
            cin>>name;
            if(db.loadBook(name).getName().empty())
            {
                Book b;int x;
                cout<<"This book is not available 😞 "<<endl;
                cout<<"Do you want to request this book ? 0 for no , 1 for yes"<<endl;
                cin>>x;
                if(x) b=l.supplyRequestedBook(stuName,&db);
            }
            else
            {
                cout<<"Enter today's date : ";//el 7etta dih el mafrod ne3melha men barra bas for now 5aliha keda
                cin>>borrowDate;
                cout<<"Enter return date : ";
                cin>>expectedReturnDate;
                Student s = db.loadStudent(stuName);
                Book b = db.loadBook(name);
//s               s.setCurrentBook(db.loadBook(name).getRowId());
//s                b.setBorrowedDate(borrowDate);
//s                b.setExpectedReturnDate(expectedReturnDate);
                db.addBorrowedBooks(b,stuName);
                b.setAvailability(0);
                db.updateStudent(s,stuName);
//s                db.updateBookByRowId(b,db.loadBook(name).getRowId());
                Publisher pub = db.loadPublisher(db.loadBook(b.getName()).getPublisherName());
                pub.addCash(db.loadBook(b.getName()).getPrice()/2);
                db.updatePublisher(pub,pub.getName());
                cout<<"You borrowed the book successfully, your book's ID is : "<<b.getRowId()<<endl;
                cout<<"You will pay : "<<ceil((expectedReturnDate-borrowDate)/7.0)*b.getPrice()<<endl;
                cout<<"Warning 1 : if you return the book late, you'll pay a fee of 5$ for each week late"<<endl;
                cout<<"Warning 2 : if you return the book damaged, you'll pay a fee of half the book's price"<<endl;
            }
        }
        else if(choice==3)
        {
            int bill=0,actualReturnDate,actualBorrowedPeriod,expectedBorrowedPeriod;bool flag=0;
            string rowid;Librarian l;
            cout<<"Enter your book's ID : ";
            cin>>rowid;
            Book b=db.loadBookByRowId(rowid);
            Student s=db.loadStudent(stuName);
//s         if(b.getRowId()!=s.getCurrentBookName())
//                cout<<"This is not the book you borrowed!"<<endl;
//            else
//            {
//                cout<<"Enter today's date : ";
//                cin>>actualReturnDate;
//                b.setActualReturnDate(actualReturnDate);
//                actualBorrowedPeriod = b.getActualReturnDate() - b.getBorrowedDate();
//                expectedBorrowedPeriod=b.getExpectedReturnDate()-b.getBorrowedDate();
//                bill=ceil(actualBorrowedPeriod/7.0)*b.getPrice();
//                if(actualBorrowedPeriod>expectedBorrowedPeriod)
//                {
//                    int fee;
//                    fee=5*ceil((actualBorrowedPeriod-expectedBorrowedPeriod)/7.0);
//                    bill+=fee;
//                    flag=1;
//                }
//                int state = l.checkState(&b);
//                if(state)
//                {
//                    int fee;
//                    fee=b.getPrice()/2;
//                    bill+=fee;
//                    flag=1;
//                }
//                if(!flag)
//                    cout<<"You're a good boy, you returned the book sound and in the right time, here's your bill : "<<bill<<endl;
//                else cout<<"Enta 3ayel 3el2 w hatedfa3 8arama, 5od b2a : "<<bill<<endl;
//                s.addCash(-1*bill);
//                b.setAvailability(1);
//                db.updateStudent(s,stuName);
//                db.updateBookByRowId(b,b.getRowId());
//            }
        }
        else if(choice==4)
        {
            Student s = db.loadStudent(stuName);
            //s.getSearchHistory
        }
        else if(choice==5)
        {
            Student s = db.loadStudent(stuName);
            //s.getBorrowedBooks
        }
        else if(choice==6)
        {
            Student s = db.loadStudent(stuName);
            //s.getFavoriteBooks
        }
        else if(choice==7)
            cout<<"You Have : "<< db.loadStudent(stuName).getCash() << " L.E.\n" ;
        else if(choice==8)
            db.loadStudent(stuName).showInfo();
        else if(choice==9)
        {
            Student s;
            string email,name,pass;
            int cashAmount,x;
            s=db.loadStudent(stuName);
            cout<<"What do you want to edit in the profile ?"<<endl;
            cout<<"1-Name"<<endl;
            cout<<"2-Password"<<endl;
            cout<<"3-Email"<<endl;
            cout<<"4-Cash amount"<<endl;
            cin>>x;
            if(x==1){cout<<"Enter new Name : ";cin>>name;s.setName(name);}
            if(x==2){cout<<"Enter new Password : ";cin>>pass;s.setPassword(pass);}
            if(x==3){cout<<"Enter new Email : ";cin>>pass;s.setPassword(pass);}
            if(x==4){cout<<"Enter new Cash amount : ";cin>>cashAmount;s.setCash(cashAmount);}
            db.updateStudent(s,stuName);
            break;
        }
        else if(choice==10)
            break;
        else
            cout<<"Enter correct choice"<<endl;
    }*/

}
vector<string> Controller :: split_string(string s,string splitter)
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

string Controller::join_string(vector<string> strings, string delim)
{
    std::stringstream ss;
    std::copy(strings.begin(), strings.end(),
        std::ostream_iterator<std::string>(ss, delim.c_str()));
    return ss.str();
}
