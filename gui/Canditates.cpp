#include"Canditates.h"
#include<assert.h>
#include<iostream>
#include<QTextStream>
namespace E_voting
{
Candidates::Candidates(QWidget* parrent):
    QWidget(parrent)
{
    m_confirmButton = new QPushButton("Confirm");
    m_layout = new QVBoxLayout;
    setLayout(m_layout);
    m_layout->addWidget(m_confirmButton);
    connect(m_confirmButton,SIGNAL(clicked()),this,SIGNAL(freezCandidates()));
}

void Candidates::addCandidate(Candidate * op_candidate)
{
    op_candidate->setNumber(m_candidates.size()+1);
    m_candidates.push_back(op_candidate);
    m_layout->addWidget(op_candidate);
    connect(op_candidate,SIGNAL(isUnChaked(const QString &)),
            this,SLOT(unSelectCandidate(const QString&)));
    connect(op_candidate,SIGNAL(isChaked(const QString &)),
            this,  SLOT(selectCandidate(const QString&)));
}

void Candidates::addCandidate(const QString & op_candidate)
{
    Candidate * new_candidate = new Candidate(op_candidate,m_candidates.size()+1);
    new_candidate->setNumber(m_candidates.size()+1);
    m_layout->addWidget(new_candidate);
    m_candidates.push_back(new_candidate);
    setGeometry(10,10,sizeHint().height(),sizeHint().width());
    connect(new_candidate,SIGNAL(isUnChaked(const QString &,c_value_type)),
            this,SLOT(unSelectCandidate(const QString&)));
    connect(new_candidate,SIGNAL(isChaked(const QString&,c_value_type)),
            this,SLOT(selectCandidate(const QString&)));
} 
void Candidates::removeCandidate(const Candidate & op_toRemove)
{
    for(int i = 0;i < m_candidates.size() ; ++i)
    {
        if(m_candidates[i]->getText() == op_toRemove.getText() )
        {
            m_layout->removeWidget(m_candidates[i]);
            // m_layout->setGeometry(sizeHint());
            m_candidates.remove(i);
        }
    }
}
void Candidates::unSelectCandidate(const QString& op_candidate)
{
    Candidate * current = findCandidate(op_candidate);
    assert(NULL!= current);
    current->setChecked(false);
}
void Candidates::selectCandidate(const QString& op_candidate)
{
    for(int i = 0; i< m_candidates.size() ; i++)
    {
        if(m_candidates[i]->getText() != op_candidate)
            m_candidates[i]->setChecked(false);
        else
        {
            emit  candidatSelected(m_candidates[i]);
        }
    }

}
Candidate* Candidates::findCandidate(const QString& op)
{
    for(int i = 0 ; i < m_candidates.size() ;i++)
    {
        if(m_candidates[i]->getText() == op )
            return m_candidates[i];
    }
    return NULL;
}
int Candidates::getCount()
{
    return m_candidates.size();
}
}
