#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imagetree.h"
#include <QMessageBox>
#include <stdio.h>
#include "string.h"
#include "iostream"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ImageTree<int,std::string> Tree;
    void refresh_list();
    void throwError(std::string errMessage)const;

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_saveButton_clicked() const;
    void on_loadButton_clicked();
    void on_clearButton_clicked();
    void on_nameField_textChanged(QString str);
    void on_fileNameField_textChanged(QString str);
};
#endif // MAINWINDOW_H
