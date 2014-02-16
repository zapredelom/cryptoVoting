#include<QLabel>
#include<QSpinBox>
#include<QVBoxLayout>
#include<QRadioButton>
#ifndef __NUMBER_H__
#define __NUMBER_H__
namespace E_voting
{
class Number : public QLabel
{
	Q_OBJECT
private:

	QVBoxLayout *m_layout;
	QSpinBox *m_spinbox;
	QRadioButton *m_radiobutton;

signals:
	void checked(Number*);
    void valueChanged(int );
private slots:
	void selected(bool);
public slots:
    void setValue(int  op);
public:
	bool isChecked() const;
	void checke(bool);
    size_t getValue()const ;
	Number(int op_low = 1,int op_high= 10 ,QLabel* = 0);
    void setRange(size_t low,size_t high);
};
}
#endif
