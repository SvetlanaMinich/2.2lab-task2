#include "books.h"
#include <string>

Books::Books()
{
    number = 0;
    author = "";
    name = "";
    date = QDate::currentDate();
    publishing_house = "";
    pages_num = 0;
}

Books::Books(int numb, QString a, QString nam, QDate d, QString ph, int pn)
{
    number = numb;
    author = a;
    name = nam;
    date = d;
    publishing_house = ph;
    pages_num = pn;
}

QString Books::GetNumber()
{
    return QString::number(number);
}

QString Books::GetAuthor()
{
    return author;
}

QString Books::GetName()
{
    return name;
}

QString Books::GetDate()
{
    return QString::number(date.year());
}

QString Books::GetPublishing()
{
    return publishing_house;
}

QString Books::GetPages()
{
    return QString::number(pages_num);
}








