#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QDate>
#include "books.h"
#include "arraylist.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->bookList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->addFirst->setEnabled(false);
    ui->addFront->setEnabled(false);
    ui->addBack->setEnabled(false);
    ui->removeBack->setEnabled(false);
    ui->removeFront->setEnabled(false);
    ui->removeNum->setEnabled(false);
    ui->searchNum->setEnabled(false);
    ui->searchAuth->setEnabled(false);
    ui->isHere->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString path;
ArrayList arr;

Books MainWindow::add()
{

    QString number;
    QString author;
    QString name;
    QString date;
    QString publishing_house;
    QString pages_num;

    bool repeat = true;
    while(repeat)
    {
        repeat = false;
        try {
            bool ok;
            number = QInputDialog::getText(this,tr("Номер"),
                                                 tr("Введите номер книги"),
                                                 QLineEdit::Normal,"",&ok);

            if(number.isEmpty())
            {
                repeat = true;
                throw std::invalid_argument("Введена пустая строка");
            }

            bool is_all_digital = true;
            for(QChar ch : number)
            {
                if(!ch.isDigit())
                {
                    is_all_digital = false;
                    break;
                }
            }
            if(!is_all_digital)
            {
                repeat = true;
                throw std::invalid_argument("В номере книги должны "
                                            "присутствовать только цифры");
            }
        } catch (std::invalid_argument& e) {
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    repeat = true;
    while(repeat)
    {
        repeat = false;
        try {
            bool ok;
            author = QInputDialog::getText(this,tr("Автор"),
                                                 tr("Введите ФИО автора"),
                                                 QLineEdit::Normal,"",&ok);

            if(author.isEmpty())
            {
                repeat = true;
                throw std::invalid_argument("Введена пустая строка");
            }

            for(QChar ch : author)
            {
                if(ch.isDigit())
                {
                    repeat = true;
                    throw std::invalid_argument("ФИО автора не должно содержать цифр");
                    break;
                }
            }

            if(author[0]<'A' || author[0]>'Z')
            {
                repeat = true;
                throw std::invalid_argument("ФИО должно начинаться с большой буквы");
            }
            for(int i =0;i<author.size();i++)
            {
                if(author[i]==' ' && (author[i+1]<'A' || author[i+1]>'Z'))
                {
                    repeat = true;
                    throw std::invalid_argument("ФИО должно начинаться с большой буквы");
                }
            }
        } catch (std::invalid_argument& e) {
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    repeat = true;
    while(repeat)
    {
        repeat = false;

        try {
        bool ok;
        name = QInputDialog::getText(this,tr("Название"),
                                     tr("Введите название книги"),
                                     QLineEdit::Normal,"",&ok);

        if(name.isEmpty())
        {
            repeat = true;
            throw std::invalid_argument("Введена пустая строка");
        }

        } catch(std::invalid_argument& e){
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    repeat = true;
    while(repeat)
    {
        repeat = false;
        try {
            bool ok;
            date = QInputDialog::getText(this,tr("Год"),
                                         tr("Введите год издания книги"),
                                         QLineEdit::Normal,"",&ok);

            QDate d = QDate::fromString(date, "yyyy");
            if(!d.isValid())
            {
                repeat = true;
                throw std::invalid_argument("Дата не валидна");
            }

        } catch (std::invalid_argument& e) {
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    repeat = true;
    while(repeat)
    {
        repeat = false;
        try {
            bool ok;
            publishing_house = QInputDialog::getText(this,tr("Издательство"),
                                                     tr("Введите название издательства"),
                                                     QLineEdit::Normal,"",&ok);

            if(publishing_house.isEmpty())
            {
                repeat = true;
                throw std::invalid_argument("Введена пустая строка");
            }
        } catch (std::invalid_argument& e) {
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    repeat = true;
    while(repeat)
    {
        repeat = false;
        try {
            bool ok;
            pages_num = QInputDialog::getText(this,tr("Страницы"),
                                           tr("Введите количество страниц"),
                                           QLineEdit::Normal,"",&ok);

            if(pages_num.isEmpty())
            {
                repeat = true;
                throw std::invalid_argument("Введена пустая строка");
            }

            bool is_not_digit = false;
            for(QChar ch : pages_num)
            {
                if(ch<'0'||ch>'9')
                {
                    repeat = true;
                    throw std::invalid_argument("Количество страниц должно "
                                                "содержать только цифры");
                    break;
                }
            }

            if(pages_num.toInt()==0)
            {
                repeat = true;
                throw std::invalid_argument("Число должно быть больше 0");
            }
        } catch (std::invalid_argument& e) {
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    Books b(number.toInt(), author, name, QDate::fromString(date, "yyyy"),
            publishing_house, pages_num.toInt());
    return b;
}

void MainWindow::on_openFile_clicked()
{
    path = QFileDialog::getOpenFileName(this, "Выбор файла",
                                        QDir::cleanPath("C:/QTlab2/task22try/a"), "*.txt");
    FILE* file;
    std::string p = path.toStdString();
    const char* pathres = p.c_str();
    if(!fopen_s(&file,pathres,"r"))
    {
        int empty = 1;
        int c = fgetc(file);
        if (c != EOF) {
            empty = 0;
        }
        if(empty)
        {
            ui->bookList->setColumnCount(6);
            ui->bookList->setHorizontalHeaderLabels(QStringList()<<"Номер"<<"Автор"
                                                    <<"Название"<<"Год"
                                                    <<"Издательство"<<"Страницы");
        }
        else
        {
            QMessageBox::information(this,tr("Ошибка"),
                                     tr("Файл должен быть пустым при открытии"));
        }
    }
    fclose(file);

    ui->addFirst->setEnabled(true);
}


void MainWindow::on_addFirst_clicked()
{


    Books b = add();
    arr.CreateFirstNode(b);

    ui->bookList->insertRow(0);

    QTableWidgetItem* numberQ = new QTableWidgetItem(b.GetNumber());
    QTableWidgetItem* authorQ = new QTableWidgetItem(b.GetAuthor());
    QTableWidgetItem* nameQ = new QTableWidgetItem(b.GetName());
    QTableWidgetItem* dateQ = new QTableWidgetItem(b.GetDate());
    QTableWidgetItem* phQ = new QTableWidgetItem(b.GetPublishing());
    QTableWidgetItem* pnQ = new QTableWidgetItem(b.GetPages());

    ui->bookList->setItem(0,0,numberQ);
    ui->bookList->setItem(0,1,authorQ);
    ui->bookList->setItem(0,2,nameQ);
    ui->bookList->setItem(0,3,dateQ);
    ui->bookList->setItem(0,4,phQ);
    ui->bookList->setItem(0,5,pnQ);

    ui->addFirst->setEnabled(false);
    ui->addBack->setEnabled(true);
    ui->addFront->setEnabled(true);
    ui->removeBack->setEnabled(true);
    ui->removeFront->setEnabled(true);
    ui->openFile->setEnabled(false);

}

void MainWindow::on_addFront_clicked()
{

    Books b = add();
    arr.PushFront(b);

    ui->bookList->insertRow(0);

    QTableWidgetItem* numberQ = new QTableWidgetItem(b.GetNumber());
    QTableWidgetItem* authorQ = new QTableWidgetItem(b.GetAuthor());
    QTableWidgetItem* nameQ = new QTableWidgetItem(b.GetName());
    QTableWidgetItem* dateQ = new QTableWidgetItem(b.GetDate());
    QTableWidgetItem* phQ = new QTableWidgetItem(b.GetPublishing());
    QTableWidgetItem* pnQ = new QTableWidgetItem(b.GetPages());

    ui->bookList->setItem(0,0,numberQ);
    ui->bookList->setItem(0,1,authorQ);
    ui->bookList->setItem(0,2,nameQ);
    ui->bookList->setItem(0,3,dateQ);
    ui->bookList->setItem(0,4,phQ);
    ui->bookList->setItem(0,5,pnQ);

    ui->removeNum->setEnabled(true);
    ui->searchNum->setEnabled(true);
    ui->searchAuth->setEnabled(true);
    ui->isHere->setEnabled(true);
}

void MainWindow::on_addBack_clicked()
{
    Books b = add();
    arr.PushBack(b);

    ui->bookList->insertRow(ui->bookList->rowCount());

    QTableWidgetItem* numberQ = new QTableWidgetItem(b.GetNumber());
    QTableWidgetItem* authorQ = new QTableWidgetItem(b.GetAuthor());
    QTableWidgetItem* nameQ = new QTableWidgetItem(b.GetName());
    QTableWidgetItem* dateQ = new QTableWidgetItem(b.GetDate());
    QTableWidgetItem* phQ = new QTableWidgetItem(b.GetPublishing());
    QTableWidgetItem* pnQ = new QTableWidgetItem(b.GetPages());

    ui->bookList->setItem(ui->bookList->rowCount()-1,0,numberQ);
    ui->bookList->setItem(ui->bookList->rowCount()-1,1,authorQ);
    ui->bookList->setItem(ui->bookList->rowCount()-1,2,nameQ);
    ui->bookList->setItem(ui->bookList->rowCount()-1,3,dateQ);
    ui->bookList->setItem(ui->bookList->rowCount()-1,4,phQ);
    ui->bookList->setItem(ui->bookList->rowCount()-1,5,pnQ);

    ui->removeNum->setEnabled(true);
    ui->searchNum->setEnabled(true);
    ui->searchAuth->setEnabled(true);
    ui->isHere->setEnabled(true);
}

void MainWindow::on_removeFront_clicked()
{
    if(ui->bookList->rowCount() == 1)
    {
        arr.RemoveOneNode();
        ui->removeBack->setEnabled(false);
        ui->removeFront->setEnabled(false);
        ui->addBack->setEnabled(false);
        ui->addFront->setEnabled(false);
        ui->addFirst->setEnabled(true);
        ui->removeNum->setEnabled(false);
        ui->searchNum->setEnabled(false);
        ui->searchAuth->setEnabled(false);
        ui->isHere->setEnabled(false);
    }
    else
    {
        arr.RemoveFront();
    }
    ui->bookList->removeRow(0);
}

void MainWindow::on_removeBack_clicked()
{
    if(ui->bookList->rowCount() == 1)
    {
        arr.RemoveOneNode();
        ui->removeBack->setEnabled(false);
        ui->removeFront->setEnabled(false);
        ui->addBack->setEnabled(false);
        ui->addFront->setEnabled(false);
        ui->addFirst->setEnabled(true);
        ui->removeNum->setEnabled(false);
        ui->searchNum->setEnabled(false);
        ui->searchAuth->setEnabled(false);
        ui->isHere->setEnabled(false);
    }
    else
    {
        arr.RemoveBack();
    }
    ui->bookList->removeRow(ui->bookList->rowCount()-1);
}

void MainWindow::on_removeNum_clicked()
{

    QString number;
    bool repeat = true;
    while(repeat)
    {
        repeat = false;
        try {
            bool ok;
            number = QInputDialog::getText(this,tr("Номер"),
                                                 tr("Введите номер книги"),
                                                 QLineEdit::Normal,"",&ok);

            if(number.isEmpty())
            {
                repeat = true;
                throw std::invalid_argument("Введена пустая строка");
            }

            bool is_all_digital = true;
            for(QChar ch : number)
            {
                if(!ch.isDigit())
                {
                    is_all_digital = false;
                    break;
                }
            }
            if(!is_all_digital)
            {
                repeat = true;
                throw std::invalid_argument("В номере книги должны "
                                            "присутствовать только цифры");
            }
        } catch (std::invalid_argument& e) {
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }


    int del = arr.RemoveNumber(number);

    if(del == -2)
    {
        arr.RemoveFront();
        del = 0;
    }
    if(del == -3)
    {
        arr.RemoveBack();
        del = ui->bookList->rowCount()-1;
    }
    if(del == -4)
    {
        arr.RemoveOneNode();
        del = 0;
        ui->removeBack->setEnabled(false);
        ui->removeFront->setEnabled(false);
        ui->addBack->setEnabled(false);
        ui->addFront->setEnabled(false);
        ui->addFirst->setEnabled(true);
        ui->removeNum->setEnabled(false);
        ui->searchNum->setEnabled(false);
        ui->searchAuth->setEnabled(false);
        ui->isHere->setEnabled(false);
    }
    if(del > -1)
    {
        ui->bookList->removeRow(del);
    }
}

void MainWindow::on_searchNum_clicked()
{
    QString number;
    bool repeat = true;
    while(repeat)
    {
        repeat = false;
        try {
            bool ok;
            number = QInputDialog::getText(this,tr("Номер"),
                                                 tr("Введите номер книги"),
                                                 QLineEdit::Normal,"",&ok);

            if(number.isEmpty())
            {
                repeat = true;
                throw std::invalid_argument("Введена пустая строка");
            }

            bool is_all_digital = true;
            for(QChar ch : number)
            {
                if(!ch.isDigit())
                {
                    is_all_digital = false;
                    break;
                }
            }
            if(!is_all_digital)
            {
                repeat = true;
                throw std::invalid_argument("В номере книги должны "
                                            "присутствовать только цифры");
            }
        } catch (std::invalid_argument& e) {
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    Books search = arr.NodeSearchNumber(number);

    if(search.GetNumber().toInt()==0)
    {
        QMessageBox::information(this, tr("Ошибка"), tr("Нет книги с таким номером"));
    }
    else
    {
        QMessageBox::information(this, "Книга " + search.GetNumber(),
                                 "Название: " + search.GetName() + '\n' +
                                 "Автор: " + search.GetAuthor() + '\n' +
                                 "Год издания: " + search.GetDate());
    }
}

void MainWindow::on_searchAuth_clicked()
{
    QString author;
    bool repeat = true;
    while(repeat)
    {
        repeat = false;
        try {
            bool ok;
            author = QInputDialog::getText(this,tr("Автор"),
                                                 tr("Введите ФИО автора"),
                                                 QLineEdit::Normal,"",&ok);

            if(author.isEmpty())
            {
                repeat = true;
                throw std::invalid_argument("Введена пустая строка");
            }

            for(QChar ch : author)
            {
                if(ch.isDigit())
                {
                    repeat = true;
                    throw std::invalid_argument("ФИО автора не должно содержать цифр");
                    break;
                }
            }

            if(author[0]<'A' || author[0]>'Z')
            {
                repeat = true;
                throw std::invalid_argument("ФИО должно начинаться с большой буквы");
            }
            for(int i =0;i<author.size();i++)
            {
                if(author[i]==' ' && (author[i+1]<'A' || author[i+1]>'Z'))
                {
                    repeat = true;
                    throw std::invalid_argument("ФИО должно начинаться с большой буквы");
                }
            }
        } catch (std::invalid_argument& e) {
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    Books search = arr.NodeSearchAuthor(author);

    if(search.GetAuthor()=="")
    {
        QMessageBox::information(this, tr("Ошибка"), tr("Нет книги с таким автором"));
    }
    else
    {
        QMessageBox::information(this, "Книга " + search.GetNumber(),
                                 "Название: " + search.GetName() + '\n' +
                                 "Автор: " + search.GetAuthor() + '\n' +
                                 "Год издания: " + search.GetDate());
    }
}

void MainWindow::on_isHere_clicked()
{
    QString name;
    QString date;

    bool repeat = true;
    while(repeat)
    {
        repeat = false;

        try {
        bool ok;
        name = QInputDialog::getText(this,tr("Название"),
                                     tr("Введите название книги"),
                                     QLineEdit::Normal,"",&ok);

        if(name.isEmpty())
        {
            repeat = true;
            throw std::invalid_argument("Введена пустая строка");
        }

        } catch(std::invalid_argument& e){
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    repeat = true;
    while(repeat)
    {
        repeat = false;
        try {
            bool ok;
            date = QInputDialog::getText(this,tr("Год"),
                                         tr("Введите год издания книги"),
                                         QLineEdit::Normal,"",&ok);

            QDate d = QDate::fromString(date, "yyyy");
            if(!d.isValid())
            {
                repeat = true;
                throw std::invalid_argument("Дата не валидна");
            }

        } catch (std::invalid_argument& e) {
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    bool here = arr.NodeSearchNameYear(name, date);

    if(here)
    {
        QMessageBox::information(this, "Книга " + name, "Есть в наличии");
    }
    else
    {
        QMessageBox::information(this, "Ошибка", "Такой книги нет в наличии");
    }
}

void MainWindow::on_saveFile_clicked()
{
    FILE* file;
    std::string p = path.toStdString();
    const char* pathres = p.c_str();
    if(!fopen_s(&file,pathres,"w"))
    {
        for(int i=0; i<ui->bookList->rowCount(); i++)
        {
            for(int j=0; j<ui->bookList->columnCount()-1; j++)
            {
                for(int k=0; k<ui->bookList->item(i,j)->text().size(); k++)
                {
                    fprintf(file, "%c", ui->bookList->item(i,j)->text()[k]);
                }
                fprintf(file, "%c", '\n');
            }
        }
    }
    fclose(file);
}
























