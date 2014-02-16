#include"SetUpWindow.h"
#include<QSpinBox>
#include<iostream>
#include<QMessageBox>
namespace E_voting
{
SetUpWindow::SetUpWindow(QWidget* parrent) :
    QWidget(parrent)
{
    m_candidateLine = new QLineEdit;
    m_generator = new QLineEdit;
    m_basePrime = new QLineEdit;
    m_numbersCount = new QSpinBox;
    m_addCandidate = new QPushButton(tr("add candidat"));
    m_setGenerator = new QPushButton(tr("set generator"));
    m_randomGenerator = new QPushButton(tr("genretare random"));
    m_setNumbersCount = new QPushButton(tr("set numbers count"));
    m_setBasePrime = new QPushButton(tr("set Base Prime"));
    m_randomBasePrime = new QPushButton(tr("genretare random"));
    m_ok  = new QPushButton(tr("ok"));
    m_layout = new QVBoxLayout;

    m_candidateLayout = new QHBoxLayout;
    m_generatorLayout  = new QHBoxLayout;
    m_numbersLayout   = new QHBoxLayout;
    m_basePrimeLayout = new QHBoxLayout;

    m_candidateLayout->addWidget(m_candidateLine);
    m_candidateLayout->addWidget(m_addCandidate);
    m_layout->addLayout(m_candidateLayout);

    m_generatorLayout->addWidget(m_generator);
    m_generatorLayout->addWidget(m_setGenerator);
    m_generatorLayout->addWidget(m_randomGenerator);
    m_layout->addLayout(m_generatorLayout);

    m_numbersLayout->addWidget(m_numbersCount);
    m_numbersLayout->addWidget(m_setNumbersCount);
    m_layout->addLayout(m_numbersLayout);
    
    m_basePrimeLayout->addWidget(m_basePrime);
    m_basePrimeLayout->addWidget(m_setBasePrime);
    m_basePrimeLayout->addWidget(m_randomBasePrime);
    m_layout->addLayout(m_basePrimeLayout);

    m_layout->addWidget(m_ok);
    setLayout(m_layout);

    connect(m_addCandidate,SIGNAL(clicked()),
            this,SLOT(addCandidate()));

    connect(m_setGenerator,SIGNAL(clicked()),
            this,SLOT(setGenerator()));

    connect(m_setNumbersCount,SIGNAL(clicked()),
            this,SLOT(setNumbersCount()));
    connect(m_ok,SIGNAL(clicked()),this,SIGNAL(ok()));
    connect(m_randomGenerator,SIGNAL(clicked()),
                 this,SLOT(getRandomGenerator()));
    connect(m_randomBasePrime,SIGNAL(clicked()),
                 this,SLOT(getRandomBasePrime()));
    connect(m_setBasePrime,SIGNAL(clicked()),this,SLOT(setBasePrime()));
}
void SetUpWindow::getRandomGenerator()
{
    m_generator->setText(QString::fromStdString(Primality::instance().get_random_integer().toString()));
}
void SetUpWindow::getRandomBasePrime()
{
    m_basePrime->setText(QString::fromStdString(Primality::instance().get_random_prime().toString()));
}
void SetUpWindow::addCandidate()
{
    if(!m_candidateLine->text().isEmpty())
    {
        emit addCandidate(m_candidateLine->text());
        m_candidateLine->clear();
    }
}
      
void SetUpWindow::setGenerator()
{
    if(!m_generator->text().isEmpty())
    {
        emit setGenerator(m_generator->text());
        m_generator->setEnabled(false);
        m_randomGenerator->setEnabled(false);
        m_setGenerator->setEnabled(false);
    }
}
void SetUpWindow::setBasePrime()
{
    if(! m_basePrime->text().isEmpty())
    {
        emit setBasePrime(m_basePrime->text());
        m_setBasePrime->setEnabled(false);
        m_basePrime->setEnabled(false);
        m_randomBasePrime->setEnabled(false);
    }
}

void SetUpWindow::setNumbersCount()
{
    if(m_numbersCount->value() != 0)
    {
        emit setNumbersCount(m_numbersCount->value());
        m_numbersCount->setEnabled(false);

    }
}
}
