#ifndef BOOKS_H
#define BOOKS_H
#include <QString>
#include <QDate>

class Books
{
private:
    int number;
    QString author;
    QString name;
    QDate date;
    QString publishing_house;
    int pages_num;
public:
    Books();
    Books(int numb, QString a, QString nam, QDate d, QString ph, int pn);
    QString GetNumber();
    QString GetAuthor();
    QString GetName();
    QString GetDate();
    QString GetPublishing();
    QString GetPages();
};

#endif // BOOKS_H
