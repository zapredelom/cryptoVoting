#include<QVector>
#include<QPair>
#include<QRadioButton>
#include<QLabel>
#include<QPushButton>
#include<QVector>
#include"Candidate.h"
#ifndef CANDITATES_H
#define CANDITATES_H

namespace E_voting
{
class Candidates : public QWidget
{
    Q_OBJECT
private:
    QVector < Candidate* > m_candidates;
    QPushButton * m_confirmButton;
    QVBoxLayout * m_layout;
    Candidate* findCandidate(const QString & op);
public:
    Candidates(QWidget* parrent = 0);
    void addCandidate(Candidate * );
    void addCandidate(const QString &);
    void removeCandidate(const Candidate &);
    int getCount();
//    void removeCandidate(const QString& );
signals:
    void candidatSelected(const Candidate * );
    void enable(bool );
    void freezCandidates();
public slots:
    void unSelectCandidate(const QString&);
    void selectCandidate(const QString&);
};
}
#endif





    


