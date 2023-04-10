#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "books.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Books add();
    ~MainWindow();

private slots:
    void on_openFile_clicked();

    void on_addFirst_clicked();

    void on_addFront_clicked();

    void on_addBack_clicked();

    void on_removeFront_clicked();

    void on_removeBack_clicked();

    void on_removeNum_clicked();

    void on_searchNum_clicked();

    void on_searchAuth_clicked();

    void on_isHere_clicked();

    void on_saveFile_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
