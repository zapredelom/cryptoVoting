#include<QWidget>
#include"Numbers.h"
#include"Canditates.h"
#include<QMainWindow>
#include"ClockDial.h"
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
namespace E_voting
{
class MainWindow : public QWidget
{
    Q_OBJECT
private:
	Numbers* m_numbers;
	Candidates* m_candidates;
    ClockDial* m_clockDial;
public:
	MainWindow(QWidget* parretn = 0);
    void enableFreezing(bool);
    void enableSelecting(bool);
    void setClockDialReadOnly(bool);
    int getCandidatesCount();
    void enableCandidates(bool);
    void generateRandomNumbers();
    void setNumbersRange();
    size_t getClockValue();
    const QVector<int>  getNumVector() const;
private slots:
    void handleNumberFreezed(size_t op);
public slots:
    void setClockValue(size_t );
    void incrClockValue(size_t);
	void addCandidate(const QString&);
    void setNumbersCount(int);
    void setClocklReadOnly(bool);
    void handleNumberSelected();
signals:
    void numberSelected();
    void numberFreezed(size_t op);
    void candidatSelected(const Candidate * );
    void freezCandidates();
};
}
#endif
