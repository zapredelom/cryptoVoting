#include"PrivatKeyFixatator.h"
#include"Primality.h"
#include<QMessageBox>
#include<QString>
#include<QDebug>

namespace E_voting
{

CandidatePrivateKey::CandidatePrivateKey(const QString & name):
    is_seted(false)
{
    m_candidateName = new QLabel(name);
    m_candidatePrivatKey = new QLineEdit();
    m_setPivateKey= new QPushButton("set key") ;
    m_generateRandom = new QPushButton("generate random");
    connect(m_generateRandom,SIGNAL(clicked()),this,SLOT(generateRandomKey()));
    connect(m_setPivateKey,SIGNAL(clicked()),this,SLOT(setKey()));
//    key_type m_keyValur;
}

void CandidatePrivateKey::generateRandomKey()
{
    m_candidatePrivatKey->setText( QString::fromStdString(Primality::instance().get_random_integer().toString()) );

}

void CandidatePrivateKey::setKey()
{
    if(  m_candidatePrivatKey->text().isEmpty() )
    {
        QMessageBox* box = new QMessageBox();
        box->setText("please set enter privete key befor pressing \"set key\"");
        box->show();
        return;
    }
    m_keyValue = key_type((m_candidatePrivatKey->text()).toStdString());
    //m_candidateName->setEnabled(false);
    m_candidatePrivatKey->setEnabled(false);
    m_generateRandom->setEnabled(false);
    m_setPivateKey->setEnabled(false);
    m_candidatePrivatKey->clear();
    disconnect(m_setPivateKey,0, 0 ,0);
    disconnect(m_generateRandom,0,0,0);
    is_seted = true;

}

PrivateKeyFixator::PrivateKeyFixator()
{
    m_layout = new QVBoxLayout();
    m_buttonsLayout = new QVBoxLayout();
    m_ok = new QPushButton("Ok");
    this->setLayout(m_buttonsLayout);
    m_buttonsLayout->addLayout(m_layout);
    m_buttonsLayout->addWidget(m_ok);
    connect(m_ok,SIGNAL(clicked()),this,SLOT(ok()));
}
void PrivateKeyFixator::addCandidate(const QString & op)
{
    m_candidates.push_back(new CandidatePrivateKey(op));
    QHBoxLayout* layout =new QHBoxLayout();
    layout->addWidget(m_candidates[m_candidates.size()-1]->m_candidateName);
    layout->addWidget(m_candidates[m_candidates.size()-1]->m_candidatePrivatKey);
    layout->addWidget(m_candidates[m_candidates.size()-1]->m_generateRandom);
    layout->addWidget(m_candidates[m_candidates.size()-1]->m_setPivateKey);
    m_layout->addLayout(layout);
    m_layouts.push_back(layout);
}

void PrivateKeyFixator::ok ()
{

    Primality::key_type ret(1);
    for(int i =0;i< m_candidates.size(); i++)
    {
        if(!m_candidates[i]->is_seted)
        {
            QMessageBox* a = new QMessageBox;
            a->setText("not all candidates seted private keys");
            a->show();
            return;
        }
       ret = ret * m_candidates[i]->m_keyValue;
    }
    QString tmp = QString::fromStdString(ret.toString());
    emit privatKeyFixed(tmp);
}

PrivateKeyFixator::~PrivateKeyFixator(){}



}



