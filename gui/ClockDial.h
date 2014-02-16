#include<qwt_dial.h>
#include<qwt_dial_needle.h>
#include<qpainter.h>
#ifndef CLOCK_DIAL_H
#define CLOCK_DIAL_H
namespace E_voting {

class ClockDial : public QwtDial
{
    Q_OBJECT
private:
    void setRange(double  vmin,double  vmax, 
                  double  vstep , int pageSize );
    size_t m_candidatesCount;
    QwtDialSimpleNeedle *needle;
private slots:
    void handleValueChanged(double op);
public slots:
    void setValue(int );
//    void incrValue(size_t);
public:
    
    ClockDial(size_t , size_t);
    using QwtDial::setRange;
    void setRange(size_t low,size_t high);
    using QwtDial::setValue;
    size_t getValue()const;
signals:
    void valueChanged(int);
};
}
#endif
