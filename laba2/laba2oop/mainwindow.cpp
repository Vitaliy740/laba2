#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->addButton->setEnabled(false);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->deleteDateEdit->setDate(QDate::currentDate());
    ui->saveButton->setEnabled(false);
    ui->loadButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
}

int hashFromDate(QDate date) {
    return date.toString("yyyyMMdd").toInt();
}

std::string dateFromHash(int hash) {
    std::string year = std::to_string(hash / 10000);
    std::string month = std::to_string((hash % 10000) / 100);
    if ((hash % 10000) / 100 < 10) {
        month = "0" + month;
    }
    std::string day = std::to_string(hash % 100);
    if (hash % 100 < 10) {
        day = "0" + day;
    }
    return month + "/" + day + "/" + year;
}

void MainWindow::refresh_list() {
    ui->listWidget->clear();
    List<int, std::string> *List = Tree->OrderedList();
    ListNode<int, std::string> *it = List->Head;
    while (it != nullptr) {
        std::string title = it->value + " @ " + dateFromHash(it->key);
        ui->listWidget->addItem(QString::fromStdString(title));
        it = it->next;
    }
    delete it;
    delete List;
    if(ui->listWidget->count() > 0) {
        ui->deleteButton->setEnabled(true);
        ui->clearButton->setEnabled(true);
    }
}

void MainWindow::on_addButton_clicked() {
    int dateHash = hashFromDate(ui->dateEdit->date());
    Tree->Add(dateHash, ui->nameField->text().toUtf8().constData());
    refresh_list();
}

void MainWindow::on_deleteButton_clicked() {
    int dateHash = hashFromDate(ui->deleteDateEdit->date());
    Tree->RemoveAt(dateHash);
    refresh_list();
}

void MainWindow::on_saveButton_clicked() const {
    Tree->WriteInFile(ui->fileNameField->text().toUtf8().constData());
}

void MainWindow::on_clearButton_clicked() {
    Tree->DeleteTree();
    ui->listWidget->clear();
    ui->deleteButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
}

void MainWindow::on_loadButton_clicked() {
Tree->ReadFromFile(ui->fileNameField->text().toUtf8().constData());
    refresh_list();
}

void MainWindow::throwError(std::string errMessage) const {
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(errMessage));
    msgBox.exec();
}

void MainWindow::on_nameField_textChanged(QString str) {
    ui->addButton->setEnabled(!str.isEmpty());
}

void MainWindow::on_fileNameField_textChanged(QString str) {
    ui->saveButton->setEnabled(!str.isEmpty());
    ui->loadButton->setEnabled(!str.isEmpty());
}

MainWindow::~MainWindow()
{
    delete ui;
}

