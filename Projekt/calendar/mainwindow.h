#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "includes/calendarView.h"
#include "includes/dataInterface.h"
#include "includes/date.h"
#include "includes/eventModel.h"
#include "includes/inputDialog.h"
#include "includes/todoElement.h"
#include "includes/todoView.h"
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QInputDialog>
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

    void on_nextMonth_clicked();

    void on_prevMonth_clicked();

    void showContextMenu(const QPoint &pos);

    void showContextMenuEventElement(const QPoint &pos);

    void deleteTodoItem();

    void deleteEventItem();

    void showContextMenuDayElement(const QPoint &pos);

    void getEventsForDay(const QModelIndex &index);

    void createNewReminderEvent();

    void createNewBirthdayEvent();

    void createNewHolidayEvent();

    void on_changeCalendarViewWeekly_clicked();

  private:
    Ui::MainWindow *ui;

    std::vector<calendar::todoElement> todoElementList;

    QStandardItemModel *todoElementInterface;

    QStandardItemModel *dayElementInterface;

    calendar::calendarView newCalendarView;

    calendar::date datePlaceholder;

    QStringList labelsList;

    calendar::todoView newTodoView;

    QStandardItemModel *monthlyEventsInterface;

    std::vector<calendar::event *> eventList;

    calendar::dataInterface<calendar::event *> eventDataInterface;

    calendar::dataInterface<calendar::todoElement> todoElementDataInterface;
};
#endif // MAINWINDOW_H
