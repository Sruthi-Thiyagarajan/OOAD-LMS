#include "publisherwidget.h"

PublisherWidget::PublisherWidget(QWidget *parent) : QWidget(parent)
{
    this->main_grid = new QGridLayout;
    this->widget = new QWidget;
    // ********** header ***************
    this->headerWidget = new QWidget;
    this->headerLayout = new QHBoxLayout;

    this->pixMapHeader = new QPixmap(QCoreApplication::applicationDirPath()+"/../../OOAD-LMS/icons/person.png");
    this->iconHeader   = new QLabel;
    this->Name = new QLabel;
    this->toolBar = new QToolBar;

    this->initHeader();

    // book image
    this->image = new QLabel;
    this->image->setMaximumSize(QSize(200,200));
    this->pixMap =new QPixmap(QCoreApplication::applicationDirPath()+"/../../OOAD-LMS/icons/addBook.png");
    this->image->setPixmap(pixMap->scaled(this->image->width(),this->image->height(),Qt::KeepAspectRatio) );
    this->image->setScaledContents(true);

    this->setStyleSheet("font-size: 15px; font-weight: 400;");
    this->grid = new QGridLayout;
    this->addBookBtn = new QPushButton("Add Book");
    this->addBookBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; width: 200px;"
                                    "hover{background-color:white; color:#808080;}"); // hover is not working
    this->addBookBtn->setCursor(Qt::PointingHandCursor);
    //************** add remove button *************
    this->removeBookBtn = new QPushButton("Remove Book");
    this->removeBookBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; width: 200px;"
                                    "hover{background-color:white; color:#808080;}"); // hover is not working
    this->removeBookBtn->setCursor(Qt::PointingHandCursor);

    this->bookName = new QLineEdit;
    this->bookName->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");
    this->bookPrice = new QLineEdit;
    this->bookPrice->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");
    this->bookType = new QLineEdit;
    this->bookType->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");
    this->bookAuthor = new QLineEdit;
    this->bookAuthor->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");
    this->bookISBN = new QLineEdit;
    this->bookISBN->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");

    this->pubBooksNumLabel = new QLabel("Books Published");
    this->pubNameLabel = new QLabel("Publisher Name");
    this->bookNameLabel = new QLabel("Book Name");
    this->bookPriceLabel= new QLabel("Book Price");
    this->bookTypeLabel = new QLabel("Book Type");
    this->bookAuthorLabel = new QLabel("Book Author");
    this->bookISBNLabel = new QLabel("ISBN");

    this->errorBox = new QMessageBox();
    this->errorBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../OOAD-LMS/icons/error.png"));
    this->sucessBox = new QMessageBox();
    this->sucessBox->setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/../../OOAD-LMS/icons/sucess.png"));

    this->browseWidget = new QWidget();
    this->sendNotificationWidget = new QWidget();

    //***************************

    this->initProfileWidget();
    this->initBrowseWidget();
    this->initSendNotificationWidget();
    this->Design();
    this->outDesign();
    this->Signals_Slots();
}

void PublisherWidget::initHeader()
{
    // ********* tool Bar ************
    this->toolBar->setCursor(Qt::PointingHandCursor);
    QIcon logoutBtn= QIcon(QCoreApplication::applicationDirPath()+"/../../OOAD-LMS/icons/logout1.png");
    QIcon profileBtn = QIcon (QCoreApplication::applicationDirPath()+"/../../OOAD-LMS/icons/profile.jpg");
    // *************************************************
    //QIcon addBookBtn = QIcon(QCoreApplication::applicationDirPath()+"/../../OOAD-LMS/icons/book.png");

    QIcon getAllBooksInfo = QIcon(QCoreApplication::applicationDirPath()+"/../../OOAD-LMS/icons/book.png");
    QIcon sendNotification = QIcon(QCoreApplication::applicationDirPath()+"/../../OOAD-LMS/icons/mymessage.png");


    QString getAllBooksInfoString = "Browse";
    QString sendNotificationString = "Send Notification";
    //**************************************************
    QString logoutString  = "Logout";
    QString profileString = "Profile";

    this->toolBar->addAction(logoutBtn,logoutString);
    this->toolBar->addAction(profileBtn,profileString);

    //*************************************************
    this->toolBar->addAction(getAllBooksInfo, getAllBooksInfoString);
    this->toolBar->addAction(sendNotification,sendNotificationString);
    //*************************************************
    this->toolBar->setIconSize(QSize(50,50));
    this->toolBar->setOrientation(Qt::Horizontal);
    this->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->toolBar->setStyleSheet("QToolButton:hover{padding: 10px; background-color:white; color:#808080;}"
                                 "QToolButton:select{padding: 10px;}"
                                 "QToolButton{color:white; font-weight: bold;}");

    // ******** Icon *********
    this->iconHeader->setMaximumSize(QSize(50,50));
    this->iconHeader->setPixmap(pixMapHeader->scaled(this->iconHeader->width(),this->iconHeader->height(),Qt::KeepAspectRatio) );
    this->iconHeader->setScaledContents(true);

    // ******** Layout Design *****************
    this->headerLayout->addWidget(this->iconHeader,Qt::AlignLeft);
    this->headerLayout->addWidget(this->Name,Qt::AlignLeft);
    this->headerLayout->addItem(new QSpacerItem(200,20));
    this->headerLayout->addWidget(this->toolBar,Qt::AlignRight);

    this->headerWidget->setLayout(this->headerLayout);
    this->headerWidget->setStyleSheet("background-color:#808080");

    // name
    this->Name->setText("Name"); this->Name->setStyleSheet("font-weight:bold; font-size:18px; color:white;");
    this->headerWidget->setMinimumWidth(1000);
    this->headerWidget->show();

}
void PublisherWidget::outDesign()
{
    QWidget *w1 = new QWidget; QWidget *w2 = new QWidget;
    this->main_grid->addWidget(w1,0,0,1,3);
    this->main_grid->addWidget(w2,2,0,1,3);

    this->main_grid->addWidget(this->widget,1,1);
    this->setLayout(this->main_grid);
}
void PublisherWidget::Design()
{
    this->widget->setStyleSheet("background-color:white;");

    this->rightLayout= new QGridLayout;
    this->rightLayout->addWidget(this->bookNameLabel,0,0);
    this->rightLayout->addWidget(this->bookName,0,1,1,-1);
    this->rightLayout->addWidget(this->bookPriceLabel,1,0);
    this->rightLayout->addWidget(this->bookPrice,1,1,1,-1);
    this->rightLayout->addWidget(this->bookTypeLabel,2,0);
    this->rightLayout->addWidget(this->bookType,2,1,1,-1);

    this->rightLayout->addWidget(this->bookAuthorLabel,3,0);
    this->rightLayout->addWidget(this->bookAuthor,3,1,1,-1);
    this->rightLayout->addWidget(this->bookISBNLabel,4,0);
    this->rightLayout->addWidget(this->bookISBN,4,1,1,-1);


    this->rightLayout->addWidget(this->addBookBtn,5,1,1,1);
    //***************** removeBookBtn *************************
    this->rightLayout->addWidget(this->removeBookBtn, 5,3,1,-1);
    //******************************************************

    this->grid->addWidget(this->headerWidget,0,0,1,-1,Qt::AlignTop);
    this->grid->addWidget(this->image,1,0,-1,1);
    this->grid->addLayout(this->rightLayout,1,1,-1,2);

    this->grid->setVerticalSpacing(0);
    this->headerWidget->setMaximumHeight(100);

    this->widget->setMinimumWidth(700);
    this->widget->setMinimumHeight(400);
    this->widget->setLayout(this->grid);
}

void PublisherWidget::Signals_Slots()
{
    connect(this->toolBar,SIGNAL(actionTriggered(QAction*)),this,SLOT(handleToolBar(QAction*)));
    connect(this->addBookBtn,SIGNAL(clicked()),this,SLOT(bookDataCheck()));
    connect(this->removeBookBtn,SIGNAL(clicked()),this,SLOT(removeDataCheck()));
    connect(this->EditBtn,SIGNAL(clicked()),this,SLOT(editButtonClicked()));
    connect(this->OkBtn,SIGNAL(clicked()),this,SLOT(okButtonClicked()));

    connect(this->backbtn,SIGNAL(clicked()),this,SLOT(notifbackbtnClicked()));
    connect(this->sendnotifbtn,SIGNAL(clicked()),this,SLOT(notifsendbtnClicked()));
}

void PublisherWidget::notifbackbtnClicked()
{
    this->sendNotificationWidget->hide();
}

void PublisherWidget::notifsendbtnClicked()
{
    Book b;
    QItemSelectionModel *select = this->BorrowedTableView->selectionModel();
    QString n = select->selectedRows(0).value(0).data().toString();
    QString bname = select->selectedRows(1).value(0).data().toString();
    QString bdate = select->selectedRows(2).value(0).data().toString();
    QString rdate = select->selectedRows(3).value(0).data().toString();
    cout<<n.toStdString()<<" "<<bname.toStdString()<<" "<<bdate.toStdString()<<" "<<rdate.toStdString()<<endl;
    b.setName(bname.toStdString());
    b.setborrowed_by(n.toStdString());
    b.setBorrowedDate(bdate.toStdString());
    b.setExpectedReturnDate(rdate.toStdString());
    emit sendnotif(b);
}

void PublisherWidget::display_msg(string s)
{
    this->sucessBox->setText(QString::fromStdString(s));
    this->sucessBox->show();
}

void PublisherWidget::bookDataCheck()
{
    cout << "Add Book Check " << endl;
    if(this->bookName->text().isEmpty() || this->bookType->text().isEmpty() || this->bookPrice->text().isEmpty())
    {
        this->errorBox->setText("Please Fill all the Required Data");
        this->errorBox->show();
        return;
    }

    string Name;
    string Type;
    int Price;
    string Author;
    string ISBN;
    Name  =this->bookName->text().toStdString();
    Type  =this->bookType->text().toStdString();
    Price =this->bookPrice->text().toInt();
    Author =this->bookAuthor->text().toStdString();
    ISBN = this->bookISBN->text().toStdString();
    //emit addBookData(this->currentPublisher.getName(),Name,Type,Price);
    emit addBookData(Author, Name, Type, Price, ISBN);
    // check box
    this->sucessBox->setText("Book Added Successfully!");
    this->sucessBox->show();
}

void PublisherWidget::removeDataCheck()
{
    cout << "Remove Book Check " << endl;
    if(this->bookName->text().isEmpty() || this->bookType->text().isEmpty() || this->bookPrice->text().isEmpty())
    {
        this->errorBox->setText("Please Fill all the Required Data");
        this->errorBox->show();
        return;
    }

    Book b;
    b.setName(this->bookName->text().toStdString());
    b.setType(this->bookType->text().toStdString());
    b.setPrice(this->bookPrice->text().toInt());
    emit removeBookData(b);

    // check box
    this->sucessBox->setText("Book Remove Successfully!");
    this->sucessBox->show();
}


void PublisherWidget::initProfileWidget()
{
    this->ProfileWidget = new QWidget();
    this->ProfileWidget->setStyleSheet("background: #F6F5E4;color: #2E2E2E; font-size: 15px; font-weight: 400;");

    this->ProfileLayout = new QGridLayout();

    QLabel* name = new QLabel("Name:");             this->nameEdit = new QLineEdit(); nameEdit->setReadOnly(true); this->nameEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");
    QLabel* password = new QLabel("Password:");     this->passEdit = new QLineEdit(); passEdit->setReadOnly(true); this->passEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");
    QLabel* email = new QLabel("Email:");           this->emailEdit = new QLineEdit();emailEdit->setReadOnly(true);this->emailEdit->setStyleSheet("QLineEdit{ background-color:white;border: 2px solid #808080;border-radius: 5px;}");

    this->EditBtn = new QPushButton("Edit");
    this->EditBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->EditBtn->setCursor(Qt::PointingHandCursor);

    this->OkBtn = new QPushButton("Ok");
    this->OkBtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; ");
    this->OkBtn->setCursor(Qt::PointingHandCursor);

    QLabel *image; QPixmap* pixMap;
    image = new QLabel;
    pixMap =new QPixmap(QCoreApplication::applicationDirPath()+"/../../OOAD-LMS/icons/person.png");
    image->setPixmap(pixMap->scaled(image->width()/4,image->height()/4,Qt::KeepAspectRatio) );
    image->setScaledContents(true);

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

    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(this->EditBtn);
    horizontalLayout->addWidget(this->OkBtn);
    this->ProfileLayout->addLayout(horizontalLayout,6,0,1,-1);

    this->ProfileWidget->setLayout(this->ProfileLayout);
    this->ProfileWidget->setMinimumWidth(500);
    this->ProfileWidget->setMinimumHeight(400);

}

void PublisherWidget::initBrowseWidget(){
    this->browseWidget->setStyleSheet("background: #F6F5E4;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    this->model = new QSqlQueryModel();
    this->bookTableView = new QTableView();
    this->bookTableView->setAlternatingRowColors(true);
    this->tableviewLayout = new QGridLayout();
    tableviewLayout->addWidget(bookTableView,0,0,0,-1);

    this->browseWidget->setLayout(tableviewLayout);
    this->browseWidget->setMinimumWidth(1000);
    this->browseWidget->setMinimumHeight(600);
}

void PublisherWidget::initSendNotificationWidget(){
    this->sendNotificationWidget->setStyleSheet("background: #F6F5E4;color: #2E2E2E; font-size: 15px; font-weight: 400;");
    //this->borrowedList = new QTreeWidget();
    this->Borrowedmodel = new QSqlQueryModel();
    this->BorrowedTableView = new QTableView();
    this->BorrowedTableView->setAlternatingRowColors(true);
    this->BorrowedTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    this->BorrowedTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    this->BorrowedTableView->setColumnWidth(1,250);
    this->BorrowedTableView->setColumnWidth(2,250);
    this->BorrowedTableView->setColumnWidth(3,250);
    this->BorrowedTableView->setColumnWidth(4,250);
    /**** Buttons ***/
    this->sendnotifbtn = new QPushButton("Send Notification");
    this->sendnotifbtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; width: 200px;"
                                    "hover{background-color:white; color:#808080;}"); // hover is not working
    this->sendnotifbtn->setCursor(Qt::PointingHandCursor);
    this->backbtn = new QPushButton("Back");
    this->backbtn->setStyleSheet("background: #808080; border-radius: 10px; padding: 10px 0px; color: white; width: 200px;"
                                    "hover{background-color:white; color:#808080;}"); // hover is not working
    this->backbtn->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* bhorizontalLayout = new QHBoxLayout;
    bhorizontalLayout->addWidget(this->backbtn);
    bhorizontalLayout->addWidget(this->sendnotifbtn);

    /**** Headers ****/
//    QStringList headerLabels;
//    headerLabels.push_back(tr("MEMBER NAME"));
//    headerLabels.push_back(tr("BOOK"));
//    headerLabels.push_back(tr("BORROWED DATE"));
//    headerLabels.push_back(tr("RETURN DATE"));
//    headerLabels.push_back(tr("EXPECTED BILL"));
//    this->borrowedList->setColumnCount(headerLabels.count());
//    this->borrowedList->setHeaderLabels(headerLabels);

//    this->borrowedList->setColumnWidth(0,150);
//    this->borrowedList->setColumnWidth(1,200);
//    this->borrowedList->setColumnWidth(2,50);
//    this->borrowedList->setColumnWidth(3,50);
//    this->borrowedList->setColumnWidth(4,50);

    QVBoxLayout* verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(BorrowedTableView);
    verticalLayout->addLayout(bhorizontalLayout);

    this->sendNotificationWidget->setLayout(verticalLayout);
    this->sendNotificationWidget->setMinimumWidth(1000);
    this->sendNotificationWidget->setMinimumHeight(600);
}


void PublisherWidget::bookClicked(string name)
{
    emit getbookInfo(name);

}

void PublisherWidget::error(string text)
{
    this->errorBox->setText(QString::fromStdString(text));
    this->errorBox->show();
}

void PublisherWidget::buttonBack()
{
    emit setCurrentWidget(START_WIDGET);
}

void PublisherWidget::publisherLoggedIn(Publisher Publisher)
{
    this->currentPublisher = Publisher;
    this->nameEdit->setText(QString::fromStdString(this->currentPublisher.getName()));
    this->passEdit->setText(QString::fromStdString(this->currentPublisher.getPassword()));
    this->emailEdit->setText(QString::fromStdString(this->currentPublisher.getEmail()));
    this->Name->setText(QString::fromStdString(this->currentPublisher.getName()));
}


void PublisherWidget::browseBtnClicked()
{
    this->bookTableHandle = emit getbooktablehandle();
    this->model->setQuery(*bookTableHandle);
    this->bookTableView->setModel(model);
    this->browseWidget->show();
}

void PublisherWidget::notification_btn_clicked()
{
    this->BorrowedTableHandle = emit getborrowedtablehandle();
    this->Borrowedmodel->setQuery(*BorrowedTableHandle);
    this->BorrowedTableView->setModel(Borrowedmodel);
    this->sendNotificationWidget->show();
}

void PublisherWidget::showInfoBtnClicked()
{
    this->ProfileWidget->show();
}

void PublisherWidget::handleToolBar(QAction * action)
{
    QString action_name = action->text();
    if(action_name == "Logout")
        emit setCurrentWidget(START_WIDGET);
    if (action_name == "Profile")
        this->showInfoBtnClicked();
    if (action_name == "Browse")
        this->browseBtnClicked();
    if (action_name == "Send Notification")
        this->notification_btn_clicked();
}


void PublisherWidget::editButtonClicked()
{
    this->nameEdit->setReadOnly(false);
    this->passEdit->setReadOnly(false);
    this->emailEdit->setReadOnly(false);
}

void PublisherWidget::okButtonClicked()
{
    // update Publisher DataBase
    string name = this->nameEdit->text().toStdString();
    string pass = this->passEdit->text().toStdString();
    string email = this->emailEdit->text().toStdString();

    emit updatePublisher(this->currentPublisher.getName(),name,pass,email,0);

    this->currentPublisher.setName(name);
    this->currentPublisher.setPassword(pass);
    this->currentPublisher.setEmail(email);

    this->nameEdit->setReadOnly(true);
    this->passEdit->setReadOnly(true);
    this->emailEdit->setReadOnly(true);

    this->sucessBox->setText("Edit Successfully !");
    this->sucessBox->show();
    this->ProfileWidget->hide();
}
