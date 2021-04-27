#include "../includes/calendarView.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <regex>
#include <string>
namespace calendar {
void calendarView::setTodayDate() {
    date *newDate = new date;
    newDate->setCurrentDate();
    this->today = *newDate;
}

date calendarView::getTodayDate() const noexcept { return this->today; }

void calendarView::calculateCurrentMonth(
    QStandardItemModel *dayElementInterface, const monthModel &month,
    const int &year) {
    days.clear();
    int weekCounter = 0;
    for (int i = 0; i < 31; i++) {
        QString tempString("");
        QStandardItem *tempItem = new QStandardItem(tempString);
        tempItem->setTextAlignment(Qt::AlignCenter);
        tempItem->setEditable(0);
        if (i % 7 == 0 && i != 0) {
            weekCounter++;
        }
        dayElementInterface->setItem(weekCounter, i % 7, tempItem);
    }
    for (int i = 1; i <= 31; i++) {
        date tempDate(i, month, year);
        if (tempDate.getDay()) {
            day tempDay(tempDate);
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
        if (tempWeekDay == 0) {
            weekCounter++;
        }
        dayElementInterface->setItem(weekCounter, tempWeekDay, tempItem);
        // std::cerr << "DEBUG: " << tempDay << ", " << tempWeekDay <<
        // std::endl;
    }
}

} // namespace calendar