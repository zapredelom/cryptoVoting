#ifndef AUTHENTICATION_WINDOW_H
#define AUTHENTICATION_WINDOW_H
#include<QWidget>
class QLineEdit;
class QPushButton;
class AuthenticationWindow : QWidget
{
public:
    QLineEdit * m_IDNum;
    QPushButton* m_confirm;


