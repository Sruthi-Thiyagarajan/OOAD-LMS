#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
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
#include <vector>
#include <QDebug>

#include <QVBoxLayout>
#include <QTabBar>
#include <QTabWidget>
#include <QToolBar>
#include <QSize>
#include <QColor>
#include <QString>
#include <QImage>
#include <QPixmap>
#include "book.h"
#include "bookstudent.h"
#include <sstream>
#include <string>
#define START_WIDGET 0
#define SIGNUP_WIDGET 1
#define LOGIN_WIDGET 2
#define PUBLISHER_WIDGET 3
#define STUDENT_WIDGET 4
#define BOOK_WIDGET 5

class BookWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout* grid;
    QLabel* bookName; QLabel* name;
    QLabel* bookType; QLabel* type;
    QLabel* bookPrice;QLabel* price;
    QLabel* bookPublisher;QLabel* publisher;
    QLabel* bookAvailability;QLabel* availability;
    //*******************
    QLabel* bookLike; QLabel* like;
    QPushButton* reviewBtn;
    QLabel* showReviewLabel;
    //QLineEdit* showReview;
    QTextEdit* showReview;
    QLabel* writeReview;
    QLineEdit* editReview;
    QPushButton* saveReviewBtn;
    QPushButton*likeBtn;
    QWidget* reviewWidget;

    QGridLayout* reviewLayout;
    //***************************

    QLabel* bookImage;
 //   QPushButton* backBtn;
    QPushButton*borrowBtn;

    QMessageBox* borrowed,*errorBox,*successBox;
    QString Path;
    string bookNameStr;
    int expectedReturnDate;

    QWidget* ReturnWidget;
    QGridLayout* ReturnLayout;
    QLineEdit* ReturnDate;
    QPushButton *OkkBtn;

    string userName ;
    Book currentBook;

    QLabel* enterBook ;

public:
    BookWidget(QWidget *parent = nullptr);
    BookWidget(Book b);
    void Design();
    void Signals_Slots();

signals:
    void setCurrentWidget(int);
    void getBookInfo(string);
    void getBookInfo(Book);
    //void borrowBook(string,string,int);
    //*******************
    void borrowBook(string, string);
    int checkLikeAlready(bookstudent);
    void saveBookLikeDB(bookstudent, int);
    vector<string> loadReview(string);
    void saveReview(string,bookstudent);
    //************************

public slots:
    void backIsClicked();
    void borrowIsClicked();
    void bookInfo(Book);
    void error(string);
    void okkkButtonClicked();
    void setCurrentBook(Book b);
    void setLoggedInUserName(string name);
    //****************
    void likeIsClicked();
    void reviewBtnIsClicked();
    void saveReviewBtnIsClicked();

};


#endif // BOOKWIDGET_H
