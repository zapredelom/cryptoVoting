#include"Numbers.h"
#include"Number.h"
#include<assert.h>
namespace E_voting
{

void GenerateRandomNumbers::setNumbers(Number * op)
{
    m_numbers = op;
}
void GenerateRandomNumbers::setCount(size_t op)
{
    m_size = op;
}
void GenerateRandomNumbers::run()
{
    for ( int i = 0;i < 5 ; i++ )
    {
        sleep(100);
        for(int j = 0 ; j< m_size;j++)
        {
            m_numbers[j].setValue(rand()% 10);
        }
    }
}

Numbers::Numbers(QWidget *parrent):
	QWidget(parrent)
{
	m_numbers =  nullptr;
    m_numbersCount = 0;
    m_activeChois = nullptr;
    m_numGenerator = new GenerateRandomNumbers();
    m_numGenerator-> setNumbers(m_numbers);
    

	m_verticalLayout = new QVBoxLayout;
	m_numbersHorizontalLayout = new QHBoxLayout;
	for(size_t i = 0;i<m_numbersCount;++i)
	{
		m_numbersHorizontalLayout->addWidget(m_numbers+i);
		connect(m_numbers+i,SIGNAL(checked(Number*)),this,SLOT(numSelected(Number*)));
	}

    QHBoxLayout *m_buttonsHorizontalLayout = new QHBoxLayout;
    m_freezButton = new QPushButton("freez");
    m_freezButton->setEnabled(false);
    m_selectButton = new QPushButton("select");
	m_buttonsHorizontalLayout->addWidget(m_freezButton);
	m_buttonsHorizontalLayout->addWidget(m_selectButton);

	m_verticalLayout->addLayout(m_buttonsHorizontalLayout);
	m_verticalLayout->addLayout(m_numbersHorizontalLayout);
	setLayout(m_verticalLayout);
	connect(m_selectButton,SIGNAL(clicked()),this,SLOT(selectNumber()));
    connect(m_freezButton,SIGNAL(clicked()),this,SLOT(numFreezed()));
}

void Numbers::numSelected(Number* op)
{
	if(op->isChecked())
	for(size_t i =0 ; i < m_numbersCount ; i++ )
	{
		if( op != &m_numbers[i] )
		{
			(m_numbers + i)->checke(false);
		}
	}
}

void Numbers::selectNumber()
{
	int count = 0;
	for(size_t i = 0; i<m_numbersCount;i++)
	{
		if( !(m_numbers+i)->isChecked() )
		{
			(m_numbers+i)->setEnabled(false);
		}
		else 
        {
            m_activeChois = m_numbers+i;
			count++;
        }
	}
	assert ( 1 == count);
    emit numberSelected();
} 
void Numbers::setNumbersCount(int op)
{
   delete []  m_numbers;
   m_numbers = new Number[op];
   m_numbersCount = op;
   for(size_t i =0;i<m_numbersCount;i++)
   {
       m_numbersHorizontalLayout->addWidget(m_numbers+i);
       connect(m_numbers+i,SIGNAL(checked(Number*)),this,SLOT(numSelected(Number*)));
   }
   m_numGenerator->setCount(op);

}

void Numbers::numFreezed()
{
    assert(0 != m_activeChois);
    emit numberFreezed(m_activeChois->getValue());
}
const QVector<int>  Numbers::getNumVector() const
{
    QVector<int> ret;
    for(size_t i =0 ;i< m_numbersCount;i++)
    {
        ret.push_back(m_numbers[i].getValue());
    }
    return ret;
}
void Numbers::enableFreezing(bool op)
{
    m_freezButton->setEnabled(op);

}

void Numbers::enableSelecting(bool op)
{
    m_selectButton->setEnabled(op);

}
void Numbers::setRange(size_t low,size_t high)
{
    for(size_t i =0;i < m_numbersCount;i++)
    {
        m_numbers[i].setRange(low,high);
    }
}
void Numbers::generateRandomNumbers()
{
    for ( int i = 0;i < 5 ; i++ )
    {
        //sleep(1);
        for(size_t j = 0 ; j< m_numbersCount ;j++)
        {
            m_numbers[j].setValue(rand()% 10);
        }
    }
  // m_numGenerator->start();
}
Number* Numbers::getActiveChois()
{
    return m_activeChois;
}
}
