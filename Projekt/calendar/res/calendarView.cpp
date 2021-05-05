#include "../includes/calendarView.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <regex>
#include <string>
namespace calendar {

calendarView::calendarView() {
    this->setTodayDate();
    this->monthNames.push_back("Styczeń");
    this->monthNames.push_back("Luty");
    this->monthNames.push_back("Marzec");
    this->monthNames.push_back("Kwiecień");
    this->monthNames.push_back("Maj");
    this->monthNames.push_back("Czerwiec");
    this->monthNames.push_back("Lipiec");
    this->monthNames.push_back("Sierpnień");
    this->monthNames.push_back("Wrzesień");
    this->monthNames.push_back("Październik");
    this->monthNames.push_back("Listopad");
    this->monthNames.push_back("Grudzień");
}

void calendarView::setTodayDate() {
    date *newDate = new date;
    newDate->setCurrentDate();
    this->today = *newDate;
}

date calendarView::getTodayDate() const noexcept { return this->today; }

void calendarView::calculateCurrentMonth(
    QStandardItemModel *dayElementInterface, const monthModel &month,
    const int &year, QStandardItemModel *monthEventsInterface) {
    days.clear();
    int weekCounter = 0;
    /*for (int i = 0; i < 31; i++) {
        QString tempString("");
        QStandardItem *tempItem = new QStandardItem(tempString);
        tempItem->setTextAlignment(Qt::AlignCenter);
        tempItem->setEditable(0);
        if (i % 7 == 0 && i != 0) {
            weekCounter++;
        }
        dayElementInterface->setItem(weekCounter, i % 7, tempItem);
    }*/
    for (int i = 1; i <= 31; i++) {
        date tempDate(i, month, year);
        if (tempDate.getDay()) {
            day tempDay(tempDate);
            date tempEvDate(24, May, 2021);
            // eventBirthday tempEvent(tempDate, "Urodziny test", Annually,
            //"Tester", "Testowy", tempBirthDate);
            if (tempDate.getDay() == tempEvDate.getDay() &&
                tempDate.getMonth() == tempEvDate.getMonth() &&
                tempDate.getYear() == tempEvDate.getYear()) {
                eventReminder *tempEvent = new eventReminder(
                    tempDate, "NAME", None, "LOCATION", "TYPE");
                tempDay.addEvent(tempEvent);
            }
            this->days.push_back(tempDay);
        }
    }
    weekCounter = 0;
    for (auto dayIt : days) {
        int tempDay = dayIt.getDate().getDay();
        int tempWeekDay = dayIt.getDate().getWeekDay();
        QString tempString(std::to_string(tempDay).c_str());
        QStandardItem *tempItem = new QStandardItem(tempString);
        tempItem->setTextAlignment(Qt::AlignCenter);
        tempItem->setEditable(0);
        if (dayIt.getDate().getDay() == today.getDay() &&
            dayIt.getDate().getMonth() == today.getMonth() &&
            dayIt.getDate().getYear() == today.getYear()) {
            tempItem->setBackground(Qt::darkBlue);
            tempItem->setForeground(Qt::white);
        }
        if (dayIt.getDate().getWeekDay() == Sun) {
            tempItem->setForeground(Qt::red);
        }
        if (tempWeekDay == 0) {
            weekCounter++;
        }
        if (dayIt.getEvents().size()) {
            tempItem->setForeground(Qt::darkGreen);
        }
        dayElementInterface->setItem(weekCounter, tempWeekDay, tempItem);
        // std::cerr << "DEBUG: " << tempDay << ", " << tempWeekDay <<
        // std::endl;
    }
}

std::string calendarView::getMonthName(const monthModel &month) {
    std::string result;
    result = this->monthNames[month];
    return result;
}

void calendarView::getEventsForDay(QStandardItemModel *monthEventsInterface,
                                   const int &qDay) {
    // @todo
    day tempDay;
    monthEventsInterface->clear();
    try {
        tempDay = this->days[qDay - 1];
        std::cout << tempDay.getDate().getDay() << std::endl;
        for (auto eventItem : tempDay.getEvents()) {
            std::cout << eventItem->getEvName() << std::endl;
            /*QStandardItem *tempItem =
                new QStandardItem(QString(eventItem.getEvName().c_str()));*/
            QStandardItem *tempItem = this->displayReminderEvent(eventItem);
            monthEventsInterface->appendRow(tempItem);
        }
    } catch (std::bad_alloc) {
        std::cout << "OUT OF RANGE\n";
    }
}

QStandardItem *calendarView::displayReminderEvent(event *newEvent) {
    QStandardItem *tempItem =
        new QStandardItem(newEvent->stringifyEvent().c_str());
    return tempItem;
}

void calendarView::addEventFromDialog(
    QTableView *calendarMonthlyView, const std::string &newEvName,
    const std::string &newEvDescription, const std::string &newEvLocation,
    const std::string &newEvType, const std::string &newEvFirstname,
    const std::string &newEvLastname, const date &newEvDate,
    const date &newBirthdate, const date &beginDate, const date &endDate,
    const repeatCycle &newEvRepeat, const std::string &eventClass) {
    if (eventClass == "REMINDER") {
        eventReminder *tempEvent = new eventReminder(
            newEvDate, newEvName, newEvRepeat, newEvLocation, newEvType);
        // QModelIndex index :
        //  todoListView->selectionModel()->selectedIndexes()
        this->days[newEvDate.getDay() - 1].addEvent(tempEvent);
        // return tempEvent;
    }
    // return nullptr;
}

std::vector<day> calendarView::getDays() const noexcept { return this->days; }

void calendarView::setDays(std::vector<day> newDays) { this->days = newDays; }

} // namespace calendar