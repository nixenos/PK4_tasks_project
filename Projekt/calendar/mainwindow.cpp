#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->saveAction, &QAction::triggered, this, &MainWindow::saveToFiles);
    connect(ui->closeAction, &QAction::triggered, this, &MainWindow::closeWindow);
    todoElementInterface = new QStandardItemModel(nullptr);
    ui->listView->setModel(todoElementInterface);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_changeCalendarViewMonthly_clicked(){

}

void MainWindow::saveToFiles(){
    // @TODO implement saving to files
    this->close();
}

void MainWindow::closeWindow(){
    this->saveToFiles();
    // this->close();
}


void MainWindow::on_addTodoItemButton_clicked(){
    QString inputText = ui->todoItemTextInput->toPlainText();
    std::string inputTextSTD = inputText.toStdString();
    std::cout << inputTextSTD << std::endl;
    int position=1;
    if(inputTextSTD!=""){
        calendar::todoElement newElement(position, inputTextSTD);
        this->todoElementList.push_back(newElement);
        QStandardItem *tempNewItem = new QStandardItem(QString(newElement.getDataRecord().c_str()));
        this->todoElementInterface->appendRow(tempNewItem);
        ui->todoItemTextInput->clear();
    }
}
