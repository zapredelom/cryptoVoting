#include"Candidate.h"
#include<iostream>
#include<QSize>
namespace E_voting
{
Candidate::Candidate(const QString & text,c_value_type num,QWidget* parrent) : 
                                            QLabel(parrent),m_number(num)
{
    m_layout = new QHBoxLayout;
    m_candidate = new QLabel(QString( QString::number(m_number))+ "." + text);
    m_chois = new QCheckBox;
    m_chois->setIconSize(QSize(90,90));
    m_layout->addWidget(m_candidate);
    m_layout->addWidget(m_chois);
    setLayout(m_layout);
    connect(m_chois,SIGNAL(toggled(bool)),this,SLOT(isChanged(bool)));
}

void Candidate::setNumber(c_value_type n)
{
    m_number = n;
}
void Candidate::isChanged(bool status)
{
    if(status)
    {
        emit isChaked(m_candidate->text(),m_number);
    }
    else
    {
        emit isUnChaked(m_candidate->text(),m_number);
    }
}

void Candidate::setText(const QString & txt)
{
    m_candidate->setText(txt);
}

const QString Candidate::getText() const
{
    return m_candidate->text();
}
void Candidate::setChecked(bool op)
{
    m_chois->setChecked(op);
}
c_value_type Candidate::getNumber() const
{
    return m_number;
}

}
