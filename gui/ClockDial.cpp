#include"ClockDial.h"
namespace E_voting
{
ClockDial::ClockDial(size_t op_low,size_t op_high):QwtDial(0)
{
    QwtDial::setRange(static_cast<double>(op_low),
             static_cast<double>(op_high),
             1,1);
    setScale(1,1,1);
    setPeriodic(true);
    setWrapping(true);
    needle = new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow, true, 
                                    Qt::red,QColor( Qt::gray ).light( 130 ) );
    setNeedle(needle);
    setReadOnly(true);
    connect(this,SIGNAL(valueChanged(double)),this,SLOT(handleValueChanged(double)));
}
void ClockDial::handleValueChanged(double op)
{
    emit valueChanged(static_cast<int>(op));
}

void ClockDial::setRange(size_t op_low, size_t op_high)
{
    QwtDial::setRange(static_cast<double>(op_low),
             static_cast<double>(op_high),
             1,1);
}

size_t ClockDial::getValue() const
{
    
    return static_cast<size_t>(exactValue());
}
void ClockDial::setValue(int op)
{
    QwtDial::setValue(static_cast<double>(op));
}

}
