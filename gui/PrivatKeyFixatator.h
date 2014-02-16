#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QWidget>
#include<QVector>
#include<QObject>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include"GmpWraper.h"
#ifndef PRIVATEKEYFIXATOR_H
#define PRIVATEKEYFIXATOR_H
namespace E_voting
{
class CandidatePrivateKey : public QObject {
     Q_OBJECT
public:
    typedef GmpWrapper key_type;
    CandidatePrivateKey(const QString&);
    QLabel * m_candidateName;
    QLineEdit * m_candidatePrivatKey;
    QPushButton * m_setPivateKey;
    QPushButton * m_generateRandom;
    bool is_seted;
    key_type m_keyValue;
private slots:
    void setKey();
    void generateRandomKey();
};

class PrivateKeyFixator : public QWidget
{
    Q_OBJECT
public:
    typedef GmpWrapper key_type;
    PrivateKeyFixator();
    void grupCandidateKeys();
    void addCandidate(const QString&);
 virtual   ~PrivateKeyFixator();

signals:
    void privatKeyFixed(const QString&);

private:
   QVBoxLayout * m_layout;
   QVBoxLayout * m_buttonsLayout;
   QPushButton * m_ok;
   QVector<CandidatePrivateKey*> m_candidates;
   QVector<QHBoxLayout *> m_layouts;

private slots:
   void ok ();

};
}
#endif
