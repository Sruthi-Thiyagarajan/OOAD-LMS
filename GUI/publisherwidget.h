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
    QMessageBox* errorBox;
    QMessageBox* sucessBox;

    QWidget* ProfileWidget;
    QGridLayout* ProfileLayout;
    QLineEdit* nameEdit ,*passEdit , * emailEdit ,* cashEdit ;
    QPushButton *EditBtn , *OkBtn;
    Publisher currentPublisher;
    QPushButton* showInfo;


    // *****************Add some more widgets ************************
    QPushButton* removeBookBtn;
    QWidget* browseWidget;
    QWidget* sendNotificationWidget;
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
    //***************************

signals:
    void addBookData(string,string,string,int);
    void removeBookData(Book);
    void setCurrentWidget(int);
    void updatePublisher(string,string,string,string,int);

public slots:
    void bookDataCheck();
    void removeDataCheck();
    void error(string);
    void buttonBack();
    void editButtonClicked();
    void okButtonClicked();
    void publisherLoggedIn(Publisher);
    void showInfoBtnClicked();

    void handleToolBar(QAction*);

};

#endif // PUBLISHERWIDGET_H
