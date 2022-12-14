#ifndef SIGNUP_H
#define SIGNUP_H

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
#include <QRegularExpressionValidator>
#include <QDateEdit>
#include "Transaction.h"
//#include "indexs.h"

using namespace std;

class SignUp : public QWidget
{
    Q_OBJECT
private:
    QGridLayout* main_grid;

    QWidget* widget;

    QLabel* image;
    QPixmap* pixMap;

    QGridLayout* grid;
    QPushButton* SignUpBtn;
    QPushButton* BackBtn;

    QLineEdit* Name;            QLabel* nameLabel;
    QLineEdit* Email;           QLabel* emailLabel;
    QLineEdit* Password;        QLabel* passLabel;
    QLineEdit* ConfirmPassword; QLabel* confirmLabel;
    QLineEdit* CardName;        QLabel* cardnameLabel;
    QLineEdit* CardNumber;      QLabel* cardnumLabel;
    QLineEdit* CVV;             QLabel* cvvLabel;
    QDateEdit* expiry_date;     QLabel* expLabel;

    QRadioButton* publisherBtn;
    QRadioButton* studentBtn;

    QMessageBox* errorBox;

public:
    SignUp(QWidget* parent = nullptr);
    void Design();
    void outDesign();
    void Signals_Slots();
    void clear_entries();

signals:
    void signUpData(string,string,string,int,Transaction);
    //void signupTransactionData(Transaction);
    void setCurrentWidget(int);

public slots:
    void signUpCheck();
    void error(string);
    void buttonBack();

};

#endif // SIGNUP_H
