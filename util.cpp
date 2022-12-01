#include "util.h"

QString numberToStr(double d)
{
    if(d < 0)
    {
        d *= -1;
    }
    QString str = QString::number(d,'f',0);
    size_t len = str.length();
    for(int index =(int) len-3; index > 0; index -= 3)
    {
        str.insert(index, ",");
    }
    if(d<0)
    {
        str = QString("-").append(str);
    }
    return str;
}
