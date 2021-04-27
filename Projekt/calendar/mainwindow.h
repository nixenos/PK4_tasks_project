#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "includes/todoElement.h"
#include <QMainWindow>
#include <QStandardItemModel>
#include <vector>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void saveToFiles();

    void closeWindow();

  private slots:

    void on_changeCalendarViewMonthly_clicked();

    void on_addTodoItemButton_clicked();

  private:
    Ui::MainWindow *ui;

    std::vector<calendar::todoElement> todoElementList;

    QStandardItemModel *todoElementInterface;

    QStandardItemModel *dayElementInterface;
};
#endif // MAINWINDOW_H
