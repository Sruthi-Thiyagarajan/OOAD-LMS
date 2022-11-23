#ifndef PUBLISHERWIDGET_H
#define PUBLISHERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QCoreApplication>
#include <QIcon>
#include <iostream>
#include <QDebug>
#include "publisher.h"
#include <QToolBar>
#include "indexs.h"
#include "book.h"
#include "GUI/imagewidget.h"
#include <QScrollArea>
#include <QTableView>>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QTreeWidget>

using namespace std;
class PublisherWidget : public QWidget
{
    Q_OBJECT
private :
    QGridLayout* main_grid;

    // ******** Header *************
    QWidget* headerWidget;
    QHBoxLayout* headerLayout;

    QPixmap* pixMapHeader;
    QLabel* iconHeader;
    QLabel* Name;
    QToolBar* toolBar;
    // ******** White Widget ********
    QGridLayout* grid;
    QWidget* widget;
    QLabel* image;
    QPixmap* pixMap;
    QGridLayout* rightLayout;

    QPushButton* addBookBtn;
    QPushButton* BackBtn;
    QLabel* pubNameLabel;
    QLabel* pubBooksNumLabel;

    QLineEdit* bookName;        QLabel* bookNameLabel;
    QLineEdit* bookPrice;       QLabel* bookPriceLabel;
    QLineEdit* bookType;        QLabel* bookTypeLabel;
    QLineEdit* bookAuthor;      QLabel* bookAuthorLabel;
    QLineEdit* bookISBN;        QLabel* bookISBNLabel;

    QMessageBox* errorBox;
    QMessageBox* sucessBox;

    QWidget* ProfileWidget;
    QGridLayout* ProfileLayout;
    QLineEdit* nameEdit ,*passEdit , * emailEdit;
    QPushButton *EditBtn , *OkBtn;
    Publisher currentPublisher;
    QPushButton* showInfo;


    // *****************Add some more widgets ************************
    QPushButton* removeBookBtn;
    QWidget* browseWidget;
    QWidget* sendNotificationWidget;

    // **************** Browse all the books *****************
    QTableView* bookTableView;
    QSqlQueryModel* model;
    QSqlQuery* bookTableHandle;
    QGridLayout* tableviewLayout;

    // *********** View borrowed books and borrowed by List ans send notification **********
    QTableView* BorrowedTableView;
    QSqlQueryModel* Borrowedmodel;
    QSqlQuery* BorrowedTableHandle;
//    QTreeWidget* borrowedList;
//    QGridLayout* BorrowedtableviewLayout;
    QPushButton* sendnotifbtn;
    QPushButton* backbtn;
    QHBoxLayout* bhorizontalLayout;
    QVBoxLayout* verticalLayout;

public:
    PublisherWidget(QWidget *parent = nullptr);
    void initHeader();
    void Design();
    void outDesign();
    void Signals_Slots();
    void initProfileWidget();

    //***************************
    void initBrowseWidget();
    void initSendNotificationWidget();
    void updateBooks();

    //***************************

signals:
    void addBookData(string,string,string,int,string);
    void removeBookData(Book);
    void setCurrentWidget(int);
    void updatePublisher(string,string,string,string,int);
    map<string,string> getAllBooksP();
    void getbookInfo(string);
    QSqlQuery* getbooktablehandle();
    QSqlQuery* getborrowedtablehandle();
    void sendnotif(Book);

public slots:
    void bookDataCheck();
    void removeDataCheck();
    void error(string);
    void buttonBack();
    void editButtonClicked();
    void okButtonClicked();
    void publisherLoggedIn(Publisher);
    void showInfoBtnClicked();
    void browseBtnClicked();
    void notification_btn_clicked();
    void handleToolBar(QAction*);
    void bookClicked(string);
    void notifbackbtnClicked();
    void notifsendbtnClicked();
    void display_msg(string);
};

#endif // PUBLISHERWIDGET_H
