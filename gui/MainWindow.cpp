#include"MainWindow.h"
#include<iostream>
#include"Numbers.h"
#include"Number.h"
#include<cassert>
namespace E_voting
{
MainWindow::MainWindow(QWidget* parrent):
	QWidget(parrent)
{
	m_numbers = new Numbers;
	m_candidates = new Candidates;
    m_clockDial = new ClockDial(0,0);
	QVBoxLayout * vlayout = new QVBoxLayout;
    QHBoxLayout * hlayout = new QHBoxLayout;

	hlayout->addWidget(m_candidates);
	vlayout->addWidget(m_numbers);
    vlayout->addWidget(m_clockDial);
    hlayout->addLayout(vlayout);
	setLayout(hlayout);
    connect(m_numbers, SIGNAL(numberSelected()),this,SLOT(handleNumberSelected()));
    connect(m_numbers,SIGNAL(numberFreezed(size_t)),this,SLOT(handleNumberFreezed(size_t)));
    connect(m_candidates,SIGNAL(candidatSelected(const Candidate * )),
            this,SIGNAL(candidatSelected(const Candidate * )));
    connect(m_candidates,SIGNAL(freezCandidates()),this,SIGNAL(freezCandidates()));
    m_candidates->setEnabled(false);
}
void MainWindow::handleNumberFreezed(size_t op)
{
    Number* nm = m_numbers->getActiveChois();
    bool r = disconnect(m_clockDial,SIGNAL(valueChanged(int)),nm,SLOT(setValue(int)));
    Q_ASSERT(r);
    nm->setEnabled(false);
    emit numberFreezed(op);
}

size_t MainWindow::getClockValue()
{
    return m_clockDial->getValue();
}

void MainWindow::handleNumberSelected()
{
    Number* nm = m_numbers->getActiveChois();
    assert(nm);
    bool r;
    r=connect(nm,SIGNAL(valueChanged(int)),m_clockDial,SLOT(setValue(int)));
    Q_ASSERT(r);
    connect(m_clockDial,SIGNAL(valueChanged(int)),nm,SLOT(setValue(int)));
    Q_ASSERT(r);
    emit numberSelected();
}

void MainWindow::setNumbersRange()
{
    m_numbers->setRange(1,m_candidates->getCount());
}

void MainWindow::addCandidate(const QString& str)
{
	m_candidates->addCandidate(str);
}

void MainWindow::setNumbersCount(int op)
{
    m_numbers->setNumbersCount(op);
}

void MainWindow::enableFreezing(bool op)
{
    m_numbers->enableFreezing(op);
}

const QVector<int>  MainWindow::getNumVector() const
{
    return m_numbers->getNumVector();
}

void MainWindow::enableSelecting(bool op)
{
    m_numbers->enableSelecting(op);
}

void MainWindow::setClockValue(size_t op)
{
    m_clockDial->setValue(static_cast<int>(op));
}

void MainWindow::incrClockValue(size_t op)
{
    m_clockDial->incValue(static_cast<int>(op));
}

void MainWindow::setClocklReadOnly(bool op)
{
    m_clockDial->setReadOnly(op);
    if( !op)
    {
        m_clockDial->setRange(1,m_candidates->getCount()+1);
    }
}

void MainWindow::generateRandomNumbers()
{
    m_numbers->generateRandomNumbers();
}

void MainWindow::enableCandidates(bool op)
{
    m_candidates->setEnabled(op);
}

}












