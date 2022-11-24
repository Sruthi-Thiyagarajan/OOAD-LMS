#include "bookwidget.h"

QDate currdate= QDate::currentDate();
BookWidget::BookWidget(Book b)
{
    currentBook =b;
}

BookWidget::BookWidget(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background: white;color: #808080; font-size: 18px; font-weight: 400;");
    this->Path = QCoreApplication::applicationDirPath();
    this->grid = new QGridLayout();
    this->grid->setColumnStretch(1,12);
    this->bookName = new QLabel(); bookName->setStyleSheet("color:#808080;font-weight: bold;font-size: 15px;");
    this->bookType = new QLabel(); bookType->setStyleSheet("color:#808080;font-weight: bold;font-size: 15px;");
    this->bookPrice = new QLabel(); bookPrice->setStyleSheet("color:#808080;font-weight: bold;font-size: 15px;");
    //this->bookPublisher = new QLabel(); bookPublisher->setStyleSheet("color:#808080;font-weight: bold;font-size: 15px;");
    this->bookAvailability = new QLabel(); bookAvailability->setStyleSheet("color:#808080;font-weight: bold;font-size: 15px;");

    this->name = new QLabel("Name :"); name->setStyleSheet("color:black;font-weight: bold;font-size: 16px;");
    this->type = new QLabel("Type :"); type->setStyleSheet("color:black;font-weight: bold;font-size: 16px;");
    this->price = new QLabel("Price :"); price->setStyleSheet("color:black;font-weight: bold;font-size: 16px;");
    //this->publisher = new QLabel("Publisher :"); publisher->setStyleSheet("color:black;font-weight: bold;font-size: 16px;");
    this->availability = new QLabel("Status :"); availability->setStyleSheet("color:black;font-weight: bold;font-size: 16px;");
    //************************
    this->bookLike = new QLabel(); bookLike->setStyleSheet("color:#808080;font-weight: bold;font-size: 15px;");
    this->like = new QLabel("LIKE :"); like->setStyleSheet("color:black;font-weight: bold;font-size: 16px;");
    //*******************************************

    this->bookImage = new QLabel();
    this->likeBtn = new QPushButton("like");
    this->likeBtn->setCursor(Qt::PointingHandCursor);
    this->likeBtn->setStyleSheet("background: gray; border-radius: 10px; padding: 10px 0px; color: white; width: 200px;");
    this->borrowBtn = new QPushButton("Borrow book");
    this->borrowBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; width: 200px;");
    this->borrowBtn->setCursor(Qt::PointingHandCursor);
    this->borrowed = new QMessageBox();
    this->errorBox = new QMessageBox();
    this->errorBox->setWindowIcon(QIcon(":images/error.png"));
    this->successBox = new QMessageBox();
    this->successBox->setWindowIcon(QIcon(":images/sucess.png"));
    //****************************
    this->reviewBtn = new QPushButton("Review"); this->reviewBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; width: 200px;");
    this->reviewBtn->setCursor(Qt::PointingHandCursor);
    this->showReviewLabel = new QLabel("Existing reviews");
    //this->showReview = new QLineEdit();
    this->showReview = new QTextEdit();
    this->showReview->setReadOnly(true);
    this->writeReview = new QLabel("Your Review: ");
    this->editReview = new QLineEdit();
    this->reviewWidget = new QWidget();
    this->saveReviewBtn = new QPushButton("Save");
    this->saveReviewBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; width: 200px;");
    this->saveReviewBtn->setCursor(Qt::PointingHandCursor);

    this->reviewWidget->setStyleSheet("background: white;color: #808080; font-size: 18px; font-weight: 400;");
    this->reviewLayout = new QGridLayout();

    this->ReturnWidget = new QWidget();
    this->ReturnWidget->setStyleSheet("background: white;color: #808080; font-size: 18px; font-weight: 400;");
    this->ReturnLayout = new QGridLayout();
    this->enterBook = new QLabel("Enter expected return date :"); enterBook->setStyleSheet("color:#808080;");

    QDate maxborrowperiod = currdate.addMonths(3);
    cout<<maxborrowperiod.toString().toStdString()<<endl;
    this->ReturnDate = new QDateEdit();
    this->ReturnDate->setMinimumDate(currdate.addDays(1));
    this->ReturnDate->setMaximumDate(maxborrowperiod);
    this->ReturnDate->setCalendarPopup(true);
    this->OkkBtn = new QPushButton("Ok");
    this->OkkBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->OkkBtn->setCursor(Qt::PointingHandCursor);

    this->Design();
    this->Signals_Slots();

}
void BookWidget::Design()
{

    this->grid->addWidget(this->name,0,0);
    this->grid->addWidget(this->type,1,0);
    this->grid->addWidget(this->price,2,0);
    //this->grid->addWidget(this->publisher,3,0);
    this->grid->addWidget(this->availability,3,0);
    this->grid->addWidget(this->like,4,0);
    this->grid->addWidget(this->reviewBtn, 5,2,1,4);

    this->grid->addWidget(this->bookName,0,1,1,-1);
    this->grid->addWidget(this->bookType,1,1,1,-1);
    this->grid->addWidget(this->bookPrice,2,1,1,-1);
    //this->grid->addWidget(this->bookPublisher,3,1,1,-1);
    this->grid->addWidget(this->bookAvailability,3,1,1,-1);
    this->grid->addWidget(this->borrowBtn,5,0,1,2);

    this->grid->addWidget(this->bookImage,0,2,5,-1);
    this->grid->addWidget(this->bookLike,4,1,1,2);
    this->grid->addWidget(this->likeBtn,4,2,1,4);

    //*************************
    this->reviewLayout->addWidget(this->showReviewLabel,0,0);
    this->reviewLayout->addWidget(this->showReview,1,0);
    this->reviewLayout->addWidget(this->writeReview,2,0);
    this->reviewLayout->addWidget(this->editReview,3,0);
    this->reviewLayout->addWidget(this->saveReviewBtn,4,0);
    this->reviewWidget->setLayout(reviewLayout);
    //*************************

    this->ReturnLayout->addWidget(enterBook,0,0,Qt::AlignLeft);
    this->ReturnLayout->addWidget(ReturnDate,0,1);
    QHBoxLayout* verticlaLayout = new QHBoxLayout;
    verticlaLayout->addWidget(OkkBtn);
    this->ReturnLayout->addLayout(verticlaLayout,2,0,1,-1);
    this-> ReturnWidget->setLayout(ReturnLayout);

    this->setMinimumWidth(600);
    this->setMinimumHeight(400);
    this->setLayout(this->grid);
}


void BookWidget::Signals_Slots()
{
//    connect(this->backBtn,SIGNAL(clicked()),this,SLOT(backIsClicked()));
    connect(this->borrowBtn,SIGNAL(clicked()),this,SLOT(borrowIsClicked()));
    connect(this->OkkBtn,SIGNAL(clicked()),this,SLOT(okkkButtonClicked()));
    //***************************
    connect(this->likeBtn, SIGNAL(clicked()), this, SLOT(likeIsClicked()));
    connect(this->reviewBtn, SIGNAL(clicked()), this, SLOT(reviewBtnIsClicked()));
    connect(this->saveReviewBtn, SIGNAL(clicked()), this, SLOT(saveReviewBtnIsClicked()));
    //***************************

}


void BookWidget::backIsClicked()
{
    // mlhas lazma
//    this->hide();
}

void BookWidget::borrowIsClicked()
{
    if(!this->currentBook.getAvailability())
    {
        this->errorBox->setText("Book is Not Available");
        this->errorBox->show();
        return;
    }
    ReturnWidget->show();

}
//***********************
void BookWidget::likeIsClicked()
{
    //first load db of the currentBook
    int liked = 10;
    bookstudent bs;
    bs.setbookname(currentBook.getName());
    bs.setstudentname(userName);
    liked = emit checkLikeAlready(bs);
    if (liked==0)
    {
       this->currentBook.incLike();
       this->bookLike->setText(QString::fromStdString(to_string(currentBook.getLike())));
       //save to db
        emit saveBookLikeDB(bs, 1);

    }
    else
    {
        this->currentBook.decLike();
        this->bookLike->setText(QString::fromStdString(to_string(currentBook.getLike())));

        emit saveBookLikeDB(bs,0);
    }

}

void BookWidget::reviewBtnIsClicked(){
    vector<string> vecReview = emit loadReview(currentBook.getName());
    string review = "";
    for (auto i = vecReview.begin(); i!=vecReview.end(); i++)
    {
        review += *i;
        review += "\n";

    }
    showReview->setText(QString::fromStdString(review));
    this->reviewWidget->show();
}

void BookWidget::saveReviewBtnIsClicked()
{

    bookstudent bs;
    bs.setbookname(currentBook.getName());
    bs.setstudentname(userName);
    string curReview = this->editReview->text().toStdString();
    emit saveReview(curReview, bs);
    this->reviewWidget->close();
}

//************************
void BookWidget::bookInfo(Book b)
{
    currentBook = b;
    this->bookName->setText(QString::fromStdString(currentBook.getName()));
    this->bookType->setText(QString::fromStdString(currentBook.getType()));
    this->bookPrice->setText(QString::fromStdString(to_string(currentBook.getPrice())));
    //this->bookPublisher->setText(QString::fromStdString(currentBook.getPublisherName()));
    this->bookLike->setText(QString::fromStdString(to_string(currentBook.getLike())));
    if(currentBook.getAvailability()) this->bookAvailability->setText("Available");
    else this->bookAvailability->setText("Not Available");
    QIcon icon(this->Path + QString::fromStdString(currentBook.getImagePath()));
    QPixmap image = icon.pixmap(100,100);

    bookImage->setPixmap(image);
    bookNameStr=currentBook.getName();
    this->show();
}

void BookWidget::bookInfoAdmin(Book b)
{

    currentBook = b;
    this->bookName->setText(QString::fromStdString(currentBook.getName()));
    this->bookType->setText(QString::fromStdString(currentBook.getType()));
    this->bookPrice->setText(QString::fromStdString(to_string(currentBook.getPrice())));
    this->bookLike->setText(QString::fromStdString(to_string(currentBook.getLike())));

    if(currentBook.getAvailability()) this->bookAvailability->setText("Available");
    else this->bookAvailability->setText("Not Available");
    QIcon icon(this->Path + QString::fromStdString(currentBook.getImagePath()));
    QPixmap image = icon.pixmap(100,100);
    bookImage->setPixmap(image);
    this->borrowBtn->hide();
    this->likeBtn->hide();
    this->reviewBtn->hide();
    this->show();

}

void BookWidget::error(string text)
{
    this->errorBox->setText(QString::fromStdString(text));
    this->errorBox->show();
}

void BookWidget::okkkButtonClicked()
{
    // check empty search
    if(this->ReturnDate->text().isEmpty())
    {
        this->errorBox->setText("Enter Return Date");
        this->errorBox->show();
        return;
    }
    // return Date must be > todayDate
    int flag = currdate.daysTo(this->ReturnDate->date());
    cout<<"no of days gap: "<<flag<<endl;
    if(!flag)
    {
        this->errorBox->setText("Invalid Return Date");
        this->errorBox->show();
        return;
    }

    QString rd = this->ReturnDate->date().toString();
    this->expectedReturnDate = rd.toStdString();
    emit borrowBook(this->bookNameStr,this->userName ,this->expectedReturnDate);
    this->ReturnWidget->hide();
    this->successBox->setText("Borrowed the Book Successfully !");
    this->successBox->show();

}

void BookWidget::setCurrentBook(Book b)
{
    currentBook =b;
    this->bookName->setText(QString::fromStdString(currentBook.getName()));
    this->bookType->setText(QString::fromStdString(currentBook.getType()));
    this->bookPrice->setText(QString::fromStdString(to_string(currentBook.getPrice())));
    //this->bookPublisher->setText(QString::fromStdString(currentBook.getPublisherName()));
    this->bookLike->setText(QString::fromStdString(to_string(currentBook.getLike())));

    if(currentBook.getAvailability()) this->bookAvailability->setText("Available");
    else this->bookAvailability->setText("Not Available");
    QIcon icon(this->Path + QString::fromStdString(currentBook.getImagePath()));
    QPixmap image = icon.pixmap(100,100);
    bookImage->setPixmap(image);
    bookNameStr=currentBook.getName();

}

void BookWidget::setLoggedInUserName(string name)
{
    this->userName = name;
}
