#include<QLabel>
#include<QPushButton>
#include<QVector>
#include<QThread>
#ifndef __NUMBERS_H
#define __NUMBERS_H
class QVBoxLayout;
class QHBoxLayout;

namespace E_voting
{
class Number;
 class GenerateRandomNumbers: public QThread
 {
 public:
     void setNumbers(Number* );
     void setCount(size_t op);

 protected:

     void run();
 private:
     Number     *m_numbers;
     size_t      m_size;

 };

class Number;
class Numbers : public QWidget
{
	Q_OBJECT
private:
    GenerateRandomNumbers    *m_numGenerator;
    size_t m_numbersCount;
	QVBoxLayout 			 *m_verticalLayout;
    QHBoxLayout              *m_numbersHorizontalLayout;
	QPushButton  			 *m_selectButton;
	QPushButton              *m_freezButton;
	Number 			    	 *m_numbers;
    Number                   *m_activeChois;
public:
	Numbers(QWidget*parrent = 0);
    Number*  getActiveChois();
    void setNumbersCount(int);
    void enableFreezing(bool);
    void enableSelecting(bool);
    void setRange(size_t low,size_t high);
    const QVector<int>  getNumVector() const;
    void generateRandomNumbers();
private slots:
	void numSelected(Number *);
    void numFreezed();
public slots:
	void selectNumber();
signals:
    void numberFreezed(size_t);
    void numberSelected();
    
};
}
#endif



