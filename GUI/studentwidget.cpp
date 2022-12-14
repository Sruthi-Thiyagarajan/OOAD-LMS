#include "studentwidget.h"

Book b;

StudentWidget::StudentWidget(QWidget *parent) : QWidget(parent)
{
    this->Path = QCoreApplication::applicationDirPath();
    this->grid = new QGridLayout();
    this->toolBar = new QToolBar();
    this->searchLineEdit = new QLineEdit();
    this->searchLineEdit->setStyleSheet("background: white;");

    this->viewBooksScroll = new QScrollArea();
    this->viewBooksWidget = new QWidget();
    this->viewBooksWidget->setStyleSheet("background: black;");
    this->viewBooksLayout = new QGridLayout();
    this->lastSize.setWidth(0);
    this->lastSize.setHeight(0);

    this->today = new QLabel();
    this->today->setText(" Today: "+ QDate::currentDate().toString());
    this->today->setStyleSheet("color:black;font-weight: bold;font-size: 14px; background-color:white;");

    this->errorBox = new QMessageBox();
    this->successBox = new QMessageBox();
    this->successBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../OOAD-LMS/icons/sucess.png"));
    this->tabWidget = new QTabWidget();
    this->tabWidget->setMinimumHeight(500);
    this->tabWidget->setMinimumWidth(800);

    this->initProfileWidget();
    this->initReturnWidget();
    this->initBorrowedWidget();
    this->initSearchWidget();
    this->initPayWidget();
    this->initHistoryWidget();
    this->initMymessageWidget();
    this->initLibrarianWidget();
    this->initToolBar();
    this->Design();
    this->Signals_Slots();
}
void StudentWidget::initToolBar()
{
    this->toolBar->setMovable(false);
    this->toolBar->setIconSize(QSize(40,40));
    this->toolBar->setOrientation(Qt::Vertical);
    this->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QIcon Profile(this->Path +"/../../OOAD-LMS/icons/profile.jpg"); QString ProfileText = "Profile";
    QIcon Search(this->Path + "/../../OOAD-LMS/icons/search.png"); QString SearchText = "Search";
    QIcon favorite(this->Path + "/../../OOAD-LMS/icons/book.png"); QString favoriteText = "My Books";
    QIcon History( this->Path + "/../../OOAD-LMS/icons/history.png"); QString HistoryText = "History";
    QIcon Return(this->Path + "/../../OOAD-LMS/icons/return1.png"); QString ReturnText = "Return";
    QIcon LogOut(this->Path + "/../../OOAD-LMS/icons/logout1.png"); QString LogOutText = "Log Out";
    QIcon Pay(this->Path + "/../../OOAD-LMS/icons/pay.jpg"); QString PayText = "My Wallet";
    QIcon Mymessage(this->Path + "/../../OOAD-LMS/icons/mymessage.png"); QString MymessageText = "My Message";

    this->toolBar->addAction(Profile,ProfileText);
    this->toolBar->addAction(Search,SearchText);
    this->toolBar->addAction(favorite,favoriteText);
    this->toolBar->addAction(History,HistoryText);
    this->toolBar -> addAction(Pay, PayText);
    this->toolBar->addAction(Mymessage, MymessageText);
    this->toolBar->addAction(Return,ReturnText);
    this->toolBar->addAction(LogOut,LogOutText);
    this->toolBar->setStyleSheet("QToolButton:hover{padding: 5px;background-color: white; color: black;}"
                                 "QToolButton:select{padding: 5px;background-color: white; color: black;}"
                                 "QToolButton{padding: 10px; border-radius: 10px;}"
                                 "QToolBar{background-color:white;}");

}
void StudentWidget::initProfileWidget()
{
    this->ProfileWidget = new QWidget();
    this->ProfileWidget->setStyleSheet("background: white;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->ProfileLayout = new QGridLayout();

    QLabel* name = new QLabel("Name:");             this->nameEdit = new QLineEdit(); nameEdit->setReadOnly(true);  this->nameEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");
    QLabel* password = new QLabel("Password:");     this->passEdit = new QLineEdit(); passEdit->setReadOnly(true);  this->passEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");
    QLabel* email = new QLabel("Email:");           this->emailEdit = new QLineEdit();emailEdit->setReadOnly(true); this->emailEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");
    QLabel* cardnamelabel = new QLabel("Card Name:");    this->cardname = new QLineEdit(); cardname->setReadOnly(true); this->cardname->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");
    QLabel* cardnumlabel = new QLabel("Card Number:");    this->cardnum = new QLineEdit(); cardnum->setReadOnly(true); this->cardnum->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");
    QLabel* cvvlabel = new QLabel("CVV:");    this->cvv = new QLineEdit(); cvv->setEchoMode(QLineEdit::Password);cvv->setReadOnly(true); this->cvv->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");
    QLabel* explabel = new QLabel("Expiry:");    this->expiry = new QLineEdit(); expiry->setReadOnly(true); this->expiry->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");

    QLabel *image; QPixmap* pixMap;
    image = new QLabel;
    pixMap =new QPixmap(QCoreApplication::applicationDirPath()+"/../../OOAD-LMS/icons/person.png");
    image->setPixmap(pixMap->scaled(image->width()/4,image->height()/4,Qt::KeepAspectRatio) );
    image->setScaledContents(true);

    this->EditBtn = new QPushButton("Edit");
    this->EditBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->EditBtn->setCursor(Qt::PointingHandCursor);

    this->OkBtn = new QPushButton("Ok");
    this->OkBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->OkBtn->setCursor(Qt::PointingHandCursor);

    QLabel* setting =new QLabel("Profile Settings");
    QFrame* line = new QFrame; line->setFrameShape(QFrame::HLine);

    this->ProfileLayout->addWidget(setting,0,0,1,1);
    this->ProfileLayout->addWidget(image,1,0,1,1);
    this->ProfileLayout->addWidget(line,2,0,1,-1);

    this->ProfileLayout->addWidget(name,3,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(nameEdit,3,1);

    this->ProfileLayout->addWidget(password,4,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(passEdit,4,1);

    this->ProfileLayout->addWidget(email,5,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(emailEdit,5,1);

    this->ProfileLayout->addWidget(cardnamelabel,6,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(cardname,6,1);

    this->ProfileLayout->addWidget(cardnumlabel,7,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(cardnum,7,1);

    this->ProfileLayout->addWidget(cvvlabel,8,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(cvv,8,1);

    this->ProfileLayout->addWidget(explabel,9,0,Qt::AlignLeft);
    this->ProfileLayout->addWidget(expiry,9,1);

    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(this->EditBtn);
    horizontalLayout->addWidget(this->OkBtn);
    this->ProfileLayout->addLayout(horizontalLayout,10,0,1,-1);

    this->ProfileWidget->setLayout(this->ProfileLayout);
    this->ProfileWidget->setMinimumWidth(500);
    this->ProfileWidget->setMinimumHeight(400);
}
void StudentWidget::initReturnWidget()
{
    cout<<"Return Widget"<<endl;
    this->ReturnWidget = new QWidget();
    this->ReturnWidget->setStyleSheet("background: white;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->ReturnLayout = new QGridLayout();

    QLabel* enterBook = new QLabel("Enter return book :"); enterBook->setStyleSheet("color:#808080");
    this->ReturnBook = new QLineEdit();
    this->ReturnBook->setStyleSheet("background: white;");

    this->BackBtn = new QPushButton("Back");
    this->BackBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->BackBtn->setCursor(Qt::PointingHandCursor);

    this->OkkBtn = new QPushButton("Ok");
    this->OkkBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->OkkBtn->setCursor(Qt::PointingHandCursor);

    this->ReturnLayout->addWidget(enterBook,0,0,Qt::AlignLeft);
    this->ReturnLayout->addWidget(ReturnBook,0,1);

    QHBoxLayout* verticlaLayout = new QHBoxLayout;
    verticlaLayout->addWidget(this->BackBtn);
    verticlaLayout->addWidget(this->OkkBtn);
    this->ReturnLayout->addLayout(verticlaLayout,2,0,1,-1);

    this->ReturnWidget->setLayout(this->ReturnLayout);
}
void StudentWidget::initBorrowedWidget()
{
    this->BorrowedWidget = new QWidget();
    this->BorrowedWidget->setStyleSheet("color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->borrowedList = new QTreeWidget();
    this->borrowedList->setStyleSheet("background: white");
    this->Ok1Btn = new QPushButton("Ok");
    this->Ok1Btn->setStyleSheet("background: gray; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->Ok1Btn->setCursor(Qt::PointingHandCursor);
    this->BorrowedWidget->setMinimumSize(600,150);

    QStringList headerLabels;
    headerLabels.push_back(tr("Borrowed Book"));
    headerLabels.push_back(tr("Borrowed Date"));
    headerLabels.push_back(tr("Expected Return Date"));
    headerLabels.push_back(tr("Expected Bill"));
    this->borrowedList->setColumnCount(headerLabels.count());
    this->borrowedList->setHeaderLabels(headerLabels);

    this->borrowedList->setColumnWidth(0,250);
    this->borrowedList->setColumnWidth(1,50);
    this->borrowedList->setColumnWidth(2,50);
    this->borrowedList->setColumnWidth(3,30);

    QVBoxLayout* verticlaLayout = new QVBoxLayout;
    verticlaLayout->addWidget(this->borrowedList);
    verticlaLayout->addWidget(this->Ok1Btn);
    this->BorrowedWidget->setLayout(verticlaLayout);
}

void StudentWidget::initMymessageWidget()
{
    this->MymessageWidget = new QWidget();
    this->MymessageWidget->setStyleSheet("background: white;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    QLabel* MymessageLabel = new QLabel("Dear");
    MymessageLabel->setStyleSheet("background: white; border-radius: 10px; padding: 10px 0px; color: black; width: 200px;");
    MymessageLabel->setCursor(Qt::PointingHandCursor);
    this->nameShow = new QLineEdit();
    this->nameShow->setReadOnly(true);
    this->MymessageShow = new QTextEdit();
    this->MymessageShow->setReadOnly(true);

    this->MymessageWidgetLayout = new QGridLayout;
    this->MymessageWidgetLayout ->addWidget(MymessageLabel,0,0);
    this->MymessageWidgetLayout->addWidget(nameShow, 0, 1);
    this->MymessageWidgetLayout ->addWidget(MymessageShow,1,0,-1,-1);
    this->MymessageWidget->setLayout(MymessageWidgetLayout);

    this->MymessageWidget->setMinimumWidth(1000);
    this->MymessageWidget->setMinimumHeight(400);
}
void StudentWidget::initPayWidget()
{
    cout<<"Inside Pay widget"<<endl;
    this->PayWidget = new QWidget();
    this->PayWidget->setStyleSheet("background: white;color: #2E2E2E; font-size: 15px; font-weight: 400;");

    QLabel* CashShowLabel = new QLabel("Your Existing Balance is (in $)");
    CashShowLabel->setStyleSheet("background: white; border-radius: 10px; padding: 10px 0px; color: black; width: 200px;");
    CashShowLabel->setCursor(Qt::PointingHandCursor);
    this->CashShow = new QLineEdit();
    this->CashShow->setReadOnly(true);

    QLabel* CashEditLabel = new QLabel("Add Money (in $)");
    CashEditLabel->setStyleSheet("background: white; border-radius: 10px; padding: 10px 0px; color: black; width: 200px;");
    CashEditLabel->setCursor(Qt::PointingHandCursor);
    this->CashEdit = new QLineEdit();

    PayButton = new QPushButton("Add Money");
    this->PayButton->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; width: 200px;");
    this->PayButton->setCursor(Qt::PointingHandCursor);

    this->payBackbtn = new QPushButton("Back");
    this->payBackbtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->payBackbtn->setCursor(Qt::PointingHandCursor);

    this->payWidgetLayout = new QGridLayout;
    this->payWidgetLayout ->addWidget(CashShowLabel,0,0);
    this->payWidgetLayout ->addWidget(CashShow,0,1);

    this->payWidgetLayout ->addWidget(CashEditLabel,1,0);
    this->payWidgetLayout ->addWidget(CashEdit,1,1);

    QHBoxLayout* verticlaLayout = new QHBoxLayout;
    verticlaLayout->addWidget(this->payBackbtn);
    verticlaLayout->addWidget(this->PayButton);
    this->payWidgetLayout->addLayout(verticlaLayout,2,0,1,-1);
    this->PayWidget->setLayout(payWidgetLayout);

    this->PayWidget->setMinimumWidth(500);
    this->PayWidget->setMinimumHeight(400);

}

void StudentWidget::initSearchWidget()
{
    this->SearchWidget = new QWidget();
    this->SearchWidget->setStyleSheet("background: white;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->SearchLayout = new QVBoxLayout();
    this->SearchBook = new QLineEdit();
    this->SearchBook->setStyleSheet("background: white;");

    QLabel *lbl = new QLabel("You want to search by :"); lbl->setStyleSheet("color:#808080");

    this->NameBtn = new QPushButton("Name");
    this->NameBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->NameBtn->setCursor(Qt::PointingHandCursor);

    this->TypeBtn = new QPushButton("Type");
    this->TypeBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->TypeBtn->setCursor(Qt::PointingHandCursor);

    this->PriceBtn = new QPushButton("Price");
    this->PriceBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->PriceBtn->setCursor(Qt::PointingHandCursor);

    this->ISBNBtn = new QPushButton("ISBN");
    this->ISBNBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->ISBNBtn->setCursor(Qt::PointingHandCursor);

    this->DoneBtn = new QPushButton("Done");
    this->DoneBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->DoneBtn->setCursor(Qt::PointingHandCursor);

    this->SearchLayout->addWidget(lbl);
    this->SearchLayout->addWidget(NameBtn);
    this->SearchLayout->addWidget(TypeBtn);
    this->SearchLayout->addWidget(PriceBtn);
    this->SearchLayout->addWidget(ISBNBtn);
    //this->SearchLayout->addWidget(PubBtn);
    this->SearchLayout->addWidget(SearchBook);
    this->SearchLayout->addWidget(DoneBtn);
    this->SearchWidget->setLayout(this->SearchLayout);
    this->SearchWidget->setMinimumWidth(500);
}
void StudentWidget::initHistoryWidget()
{
    this->HistoryWidget = new QWidget();
    this->HistoryWidget->setStyleSheet("background: white;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->HistoryList = new QTreeWidget();
    this->HistoryList->setStyleSheet("background: white");
    this->OkBtnh = new QPushButton("Ok");
    this->OkBtnh->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->OkBtnh->setCursor(Qt::PointingHandCursor);
    this->HistoryWidget->setMinimumSize(600,150);

    QStringList headerLabels;
    headerLabels.push_back(tr("Searched Book"));
    this->HistoryList->setColumnCount(headerLabels.count());
    this->HistoryList->setHeaderLabels(headerLabels);

    QVBoxLayout* verticlaLayout = new QVBoxLayout;
    verticlaLayout->addWidget(this->HistoryList);
    verticlaLayout->addWidget(this->OkBtnh);
    this->HistoryWidget->setLayout(verticlaLayout);
}
void StudentWidget::initLibrarianWidget()
{
    this->librarianWidget = new QWidget();
    this->librarianWidget->setStyleSheet("background: #F6F5E4;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->librarianWidget->setWindowTitle("Librarian");
    this->librarianWidget->move(600,0);
    this->librarianLayout = new QVBoxLayout();
    this->libLabel = new QLabel("Enter Book State :");
    this->bookState = new QLineEdit();
    this->bookState->setStyleSheet("background: white;");

    this->Ok2Btn = new QPushButton("Ok");
    this->Ok2Btn->setStyleSheet("background: #2e2e2e; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->Ok2Btn->setCursor(Qt::PointingHandCursor);

    this->librarianLayout->addWidget(libLabel);
    this->librarianLayout->addWidget(bookState);
    this->librarianLayout->addWidget(Ok2Btn);

    this->librarianWidget->setLayout(librarianLayout);
}

void StudentWidget::Design()
{
    this->viewBooksScroll->setWidget(this->viewBooksWidget);
    this->viewBooksScroll->setWidgetResizable(true);
    this->viewBooksScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    this->viewBooksWidget->setStyleSheet("background-color:white");
    this->viewBooksWidget->setLayout(this->viewBooksLayout);

    this->grid->addWidget(this->toolBar,0,1,-1,1);
    this->grid->addWidget(this->viewBooksScroll,0,0);
    this->grid->addWidget(this->today,1,1,Qt::AlignLeft);

    this->setMinimumSize(MIN_SIZE);
    this->setLayout(this->grid);
    this->setStyleSheet("background-color:white;");
}

void StudentWidget::Signals_Slots()
{
    connect(this->toolBar,SIGNAL(actionTriggered(QAction*)),this,SLOT(ButtonClicked(QAction*)));
    connect(this->EditBtn,SIGNAL(clicked()),this,SLOT(editButtonClicked()));
    connect(this->OkBtn,SIGNAL(clicked()),this,SLOT(okButtonClicked()));
    connect(this->BackBtn,SIGNAL(clicked()),this,SLOT(backButtonClicked()));
    connect(this->OkkBtn,SIGNAL(clicked()),this,SLOT(okkButtonClicked()));
    connect(this->Ok1Btn,SIGNAL(clicked()),this,SLOT(ok1ButtonClicked()));
    connect(this->OkBtnh,SIGNAL(clicked()),this,SLOT(okButtonhClicked()));
    connect(this->NameBtn,SIGNAL(clicked()),this,SLOT(nameButtonClicked()));
    connect(this->TypeBtn,SIGNAL(clicked()),this,SLOT(typeButtonClicked()));
    connect(this->PriceBtn,SIGNAL(clicked()),this,SLOT(priceButtonClicked()));
    connect(this->DoneBtn,SIGNAL(clicked()),this,SLOT(doneButtonClicked()));
    connect(this->PayButton,SIGNAL(clicked()),this,SLOT(PayButtonClicked()));
    connect(this->payBackbtn,SIGNAL(clicked()),this,SLOT(payBackbtnClicked()));
    connect(this->ISBNBtn, SIGNAL(clicked()), this, SLOT(ISBNBtnClicked()));
}


void StudentWidget::UpdateBooks()
{
    // get allBooks from dataBase -> no duplicates
    map<string, string> name_imagePath = emit getAllBooks();
    // convert them into imageWidget (book interface)
    for (auto i = name_imagePath.begin(); i != name_imagePath.end() ;i++)
    {
        imageWidget* book_interface = new imageWidget(i->first,i->second);
        connect(book_interface,SIGNAL(bookClicked(string)),this,SLOT(bookClicked(string)));
        books.push_back(book_interface);
        //cout << i->first << ",";
    }
    cout << "  =========== books" << endl;
    // display it in the gridlayout
    uint COLOMN_SIZE = 3;
    uint ROW_SIZE = books.size()/COLOMN_SIZE +1;

    cout << ROW_SIZE << "," << COLOMN_SIZE << endl;
    for (uint i =0 ; i< ROW_SIZE ; i++)
    {
        for(uint j =0 ; j< COLOMN_SIZE; j++)
        {
            uint index =  i * COLOMN_SIZE + j ;
            if(index >= books.size())
                break;
            cout << "i=" << i << ",j=" << j << ",index=" << index << endl;
            // for sizing apperance
            books[index]->setMaximumWidth(this->viewBooksWidget->width()/3);
            books[index]->setMaximumHeight(this->viewBooksWidget->height()/3);

            this->viewBooksLayout->addWidget(books[index],i,j);
        }
    }

}

void StudentWidget::studentLoggedIn(Student student,Transaction t)
{
    this->currentStudent = student;
    this->currenttrans = t;
    std::cout << "studentloggedIn cash amount:" << currenttrans.getwalletcash()<< std::endl;
    emit setLoggedInUserName(this->currentStudent.getName());
    this->nameEdit->setText(QString::fromStdString(this->currentStudent.getName()));
    this->passEdit->setText(QString::fromStdString(this->currentStudent.getPassword()));
    this->emailEdit->setText(QString::fromStdString(this->currentStudent.getEmail()));
    this->CashShow->setText(QString::fromStdString(to_string(this->currenttrans.getwalletcash())));
    this->cardname->setText(QString::fromStdString(this->currenttrans.getCardName()));
    this->cardnum->setText(QString::fromStdString(this->currenttrans.getCardNumber()));
    this->cvv->setText(QString::fromStdString(this->currenttrans.getCVV()));
    this->expiry->setText(QString::fromStdString(this->currenttrans.getexpiry_date()));
    this->MymessageShow->setText(QString::fromStdString(this->currentStudent.getMessage()));
    this->nameShow->setText(QString::fromStdString(this->currentStudent.getName()));
    this->UpdateBooks();
}

void StudentWidget::transactionupdate(Transaction t)
{
    this->currenttrans = t;
    this->cardname->setText(QString::fromStdString(this->currenttrans.getCardName()));
    this->cardnum->setText(QString::fromStdString(this->currenttrans.getCardNumber()));
    this->cvv->setText(QString::fromStdString(this->currenttrans.getCVV()));
    this->expiry->setText(QString::fromStdString(this->currenttrans.getexpiry_date()));
    this->CashShow->setText(QString::fromStdString(to_string(this->currenttrans.getwalletcash())));
}

void StudentWidget::PayButtonClicked()
{
    if(this->CashEdit->text().isEmpty() )
    {
        this->errorBox->setText("Please Enter a Valid Amount");
        this->errorBox->show();
        return;
    }
    double amt = this->CashEdit->text().toDouble();
    emit addAmount(amt,currentStudent.getName());
}

void StudentWidget::payBackbtnClicked()
{
    this->PayWidget->hide();
}

void StudentWidget::ButtonClicked(QAction *action)
{
    if (action->text() == "Profile")
        this->ProfileWidget->show();
    else if (action->text() == "Return")
        this->ReturnWidget->show();
    else if (action->text() == "My Books")
        emit aa(currentStudent.getName());
    else if (action->text() == "Search")
        this->SearchWidget->show();
    else if (action->text() == "My Wallet")
        this->PayWidget ->show();
    else if (action->text() == "History")
        emit getSearchHistory(currentStudent.getName());
    else if (action->text() == "My Message")
        emit MymessageWidget->show();
    else if (action->text() == "Log Out")
    {
        emit setCurrentWidget(LOGIN_WIDGET);
        for (int i =0 ; i< this->books.size();i++)
            delete this->books[i];
        this->books.clear();
    }

}

void StudentWidget::editButtonClicked()
{
    this->nameEdit->setReadOnly(false);
    this->passEdit->setReadOnly(false);
    this->emailEdit->setReadOnly(false);
    this->cardname->setReadOnly(false);
    this->cardnum->setReadOnly(false);
    this->cvv->setReadOnly(false);
    this->expiry->setReadOnly(false);
    //this->cashEdit->setReadOnly(false);
}

void StudentWidget::okButtonClicked()
{
    // update Student DataBase
    string name = this->nameEdit->text().toStdString();
    string pass = this->passEdit->text().toStdString();
    string email = this->emailEdit->text().toStdString();
   // int cash = this->cashEdit->text().toInt();

    Transaction t;
    t.setName(name);
    t.setCardName(this->cardname->text().toStdString());
    t.setCardNumber(this->cardnum->text().toStdString());
    t.setCVV(this->cvv->text().toStdString());
    t.setexpiry_date(this->expiry->text().toStdString());
    emit updateStudent(this->currentStudent.getName(),name,pass,email, t);

    this->currentStudent.setName(name);
    this->currentStudent.setPassword(pass);
    this->currentStudent.setEmail(email);

    this->nameEdit->setReadOnly(true);
    this->passEdit->setReadOnly(true);
    this->emailEdit->setReadOnly(true);
    this->ProfileWidget->hide();
    emit setLoggedInUserName(this->currentStudent.getName());

    this->successBox->setText("Edit Successful !");
    this->successBox->show();
}

void StudentWidget::backButtonClicked()
{
    this->ReturnWidget->hide();
}

void StudentWidget::okkButtonClicked()
{
    if(this->ReturnBook->text().isEmpty() )
    {
        this->errorBox->setText("Please Enter a Valid Book Name");
        this->errorBox->show();
        return;
    }
    string returnBookName = this->ReturnBook->text().toStdString();
    emit returnBook(returnBookName,currentStudent.getName());
}

void StudentWidget::error_return(string text)
{
    this->errorBox->setText(QString::fromStdString(text));//setIcon if you want
    this->errorBox->show();
}
void StudentWidget::update_wallet(string text)
{
    this->errorBox->setText(QString::fromStdString(text));
    this->errorBox->show();
}
void StudentWidget::bookReturned(double bill , int mode)
{
    string str = "Your Bill : " + to_string(bill) + " deducted from wallet.";
    if(mode==0){
        this->errorBox->setText("Thanks for returning the book sound and in time\n"+QString::fromStdString(str));
        this->errorBox->show();
    }
    else if(mode==1){
        this->errorBox->setText("You're late, a fee is added to the bill. ($5/week for the days between your said and actual return date)\n"+QString::fromStdString(str));
        this->errorBox->show();
    }
    this->ReturnWidget->hide();
}

void StudentWidget::borrowedBooks(vector<Book> v)
{
    for(int i=0;i<v.size();i++)
    {
        string name = v[i].getName();
        string b_date = v[i].getBorrowedDate();
        string e_date = v[i].getExpectedReturnDate();
        double b = calculate_expected_bill(b_date,e_date,v[i].getPrice());
        this->addRoot(name,b_date,e_date,to_string(b));
    }
    this->BorrowedWidget->show();
}

double StudentWidget::calculate_expected_bill(string b_date, string e_date, int p)
{
    QString bstring = QString::fromStdString(b_date);
    QString estring = QString::fromStdString(e_date);
    QDate borrow = QDate::fromString(bstring,"ddd MMM dd yyyy");
    QDate expected = QDate::fromString(estring,"ddd MMM dd yyyy");

    int ex_borrow_period = borrow.daysTo(expected);
    double bill = ceil(ex_borrow_period/7.0)*p;
    return bill;
}

void StudentWidget::searchedBooks(vector<string> v)
{

    for(int i=0;i<v.size();i++)
       this->addRoot(v[i]);

    this->HistoryWidget->show();
}

void StudentWidget::bookClicked(string name)
{
    emit getBookInfo(name);
}

void StudentWidget::ok1ButtonClicked()
{
    this->BorrowedWidget->hide();
    this->borrowedList->clear();
}

void StudentWidget::okButtonhClicked()
{
    this->HistoryWidget->hide();
    this->HistoryList->clear();
}

void StudentWidget::nameButtonClicked()
{
    if(SearchBook->text().isEmpty())
    {
        this->errorBox->setText("Empty Search");
        this->errorBox->show();
        return;
    }
    this->tabWidget->clear();
    emit searchBookByName(this->SearchBook->text().toStdString(),currentStudent.getName());
}

void StudentWidget::ISBNBtnClicked()
{
    if(SearchBook->text().isEmpty())
    {
        this->errorBox->setText("Empty Search");
        this->errorBox->show();
        return;
    }
    this->tabWidget->clear();
    emit searchBookByISBN(this->SearchBook->text().toStdString(),currentStudent.getName());

}

void StudentWidget::typeButtonClicked()
{
    if(SearchBook->text().isEmpty())
    {
        this->errorBox->setText("Empty Search");
        this->errorBox->show();
        return;
    }

    this->tabWidget->clear();
    emit searchBookByType(this->SearchBook->text().toStdString(),currentStudent.getName());
}

void StudentWidget::priceButtonClicked()
{
    if(SearchBook->text().isEmpty())
    {
        this->errorBox->setText("Empty Search");
        this->errorBox->show();
        return;
    }

    this->tabWidget->clear();
    emit searchBookByPrice(this->SearchBook->text().toInt(),currentStudent.getName());
}

void StudentWidget::pubButtonClicked()
{
    if(SearchBook->text().isEmpty())
    {
        this->errorBox->setText("Empty Search");
        this->errorBox->show();
        return;
    }

    this->tabWidget->clear();
    emit searchBookByPub(this->SearchBook->text().toStdString(),currentStudent.getName());
}

void StudentWidget::doneButtonClicked()
{
    this->SearchWidget->hide();
}

void StudentWidget::booksFound(vector<Book> v)
{
    if(v.size()==0)
    {
        this->errorBox->setText("Not Found");
        this->errorBox->show();
        return;
    }

    for(uint i=0;i<v.size();i++)
    {
        BookWidget* foundBookWidget  = new BookWidget;
        Controller* controller1 = new Controller;
        connect(foundBookWidget,SIGNAL(checkLikeAlready(bookstudent)), controller1, SLOT(checkLikeAlready(bookstudent)));
        connect(foundBookWidget, SIGNAL(saveBookLikeDB(bookstudent,int)),controller1,SLOT(saveBookLikeDB(bookstudent,int)));
        connect(foundBookWidget,SIGNAL(loadReview(string)),controller1,SLOT(loadReview(string)));
        connect(foundBookWidget,SIGNAL(saveReview(string,bookstudent)),controller1,SLOT(saveReview(string,bookstudent)));
        connect(foundBookWidget,SIGNAL(borrowBook(string,string,string)),controller1,SLOT(borrowBook(string,string,string)));
        foundBookWidget->setCurrentBook(v[i]);
        foundBookWidget->setLoggedInUserName(currentStudent.getName());
        this->tabWidget->addTab(foundBookWidget,QString::fromStdString(v[i].getName()));
    }
    this->tabWidget->show();
}


void StudentWidget::addRoot(string s0, string s1,string s2, string s3)
{
    QTreeWidgetItem *i1 = new QTreeWidgetItem(this->borrowedList);
    i1->setText(0,QString::fromStdString(s0));
    i1->setText(1,QString::fromStdString(s1));
    i1->setText(2,QString::fromStdString(s2));
    i1->setText(3,QString::fromStdString(s3));
    borrowedList->addTopLevelItem(i1);

}

void StudentWidget::addRoot(string s)
{
    QTreeWidgetItem *i1 = new QTreeWidgetItem(this->HistoryList);
    i1->setText(0,QString::fromStdString(s));
     HistoryList->addTopLevelItem(i1);
}


