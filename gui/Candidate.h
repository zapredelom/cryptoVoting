#include<QLayout>
#include<QLabel>
#include<QRadioButton>
#include<QCheckBox>
#ifndef CANDIDATE_H
#define CANDIDATE_H
namespace E_voting
{
typedef int c_value_type;
class Candidate :
    public QLabel
{
    Q_OBJECT
private:
    QCheckBox    *m_chois;
    QLabel       *m_candidate;   
    QHBoxLayout  *m_layout;
    c_value_type m_number;

public slots:
    void isChanged(bool status);
signals:
    void isChaked(const QString &,c_value_type);
    void isUnChaked(const QString&,c_value_type);
public:
    void setChecked(bool op);
    Candidate(const QString &,c_value_type num,QWidget* parrent=0);
    void setText(const QString & str) ;
    const QString getText() const;
    void setNumber(c_value_type);
    c_value_type getNumber()const;
};
}
#endif
