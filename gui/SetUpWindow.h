#include<QWidget>
#include<QLineEdit>
#include"MainWindow.h"
#include<QLineEdit>
#include"Primality.h"
#ifndef SET_UP_WINDOW
#define SET_UP_WINDOW
class QSpinBox;
namespace E_voting
{
class SetUpWindow : public QWidget 
{
    Q_OBJECT
private:

    QLineEdit* m_candidateLine;
    QLineEdit* m_generator;
    QLineEdit* m_basePrime;
    QSpinBox* m_numbersCount;
//pushbottons
    QPushButton* m_addCandidate;
    QPushButton* m_setGenerator;
    QPushButton* m_randomGenerator;
    QPushButton* m_setNumbersCount;
    QPushButton* m_ok;
    QPushButton* m_setBasePrime;
    QPushButton* m_randomBasePrime;
    QPushButton* m_randomY;
    QPushButton* m_setY;
//layouts
    QVBoxLayout *m_layout;
    QHBoxLayout* m_candidateLayout;
    QHBoxLayout* m_generatorLayout;
    QHBoxLayout* m_numbersLayout;
    QHBoxLayout* m_basePrimeLayout;
    
private slots:
    void getRandomGenerator();
    void getRandomBasePrime();
    void addCandidate();
    void setGenerator();
    void setBasePrime();
    void setNumbersCount();
    
signals:
    void addCandidate(const QString &);
    void setGenerator(const QString &);
    void setNumbersCount(int);
    void setBasePrime(const QString&);
    void ok();
public:
    SetUpWindow(QWidget* parrent=0);
};
}
#endif
