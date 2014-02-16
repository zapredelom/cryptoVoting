#include"Number.h"
#include<QFont>
namespace E_voting
{
Number::Number(int op_low,int op_high,QLabel* parrent) :
	QLabel(parrent)
{
	m_layout = new QVBoxLayout;
	m_spinbox = new QSpinBox;
	m_spinbox->setRange(op_low,op_high);
	m_spinbox->setWrapping(true);
	m_spinbox->setSizeIncrement(60,60);
    setFont(QFont("aral",25));
	m_radiobutton = new QRadioButton;
	m_layout->addWidget(m_radiobutton);
	m_layout->addWidget(m_spinbox);
	setLayout(m_layout);
	connect(m_radiobutton,SIGNAL(toggled(bool)),this,SLOT(selected(bool)));
    connect(m_spinbox,SIGNAL(valueChanged(int)),this,SIGNAL(valueChanged(int)));
	
}

void Number::selected(bool op)
{
    m_radiobutton->setChecked(op);
	emit checked(this);
}

bool Number::isChecked() const
{
	return m_radiobutton->isChecked();
}
void Number::checke(bool op)
{
	m_radiobutton->setChecked(op);
}
size_t Number::getValue() const
{
    return static_cast<size_t>(m_spinbox->value());
}
void Number::setRange(size_t low,size_t high)
{
    m_spinbox->setRange(low,high);
}
void Number::setValue(int  op)
{
   this->m_spinbox->setValue(op);

}
}
