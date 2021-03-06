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
    date newDate;
    newDate.setCurrentDate();
    this->today = newDate;
}

date calendarView::getTodayDate() const noexcept { return this->today; }

void calendarView::calculateCurrentMonth(
    QStandardItemModel *dayElementInterface, const monthModel &month,
    const int &year, QStandardItemModel *monthEventsInterface) {
    days.clear();
    int weekCounter = 0;
    for (int i = 1; i <= 31; i++) {
        date tempDate(i, month, year);
        if (tempDate.getDay()) {
            day tempDay(tempDate);
            for (auto event : events) {
                std::cout << event->exportData() << std::endl;
                if (event->getEvDate() == tempDate &&
                    event->getEvRepeat() == None) {
                    tempDay.addEvent(event);
                } else if (event->getEvDate().getDay() == tempDate.getDay() &&
                           event->getEvRepeat() == Monthly) {
                    tempDay.addEvent(event);
                } else if (event->getEvDate().getWeekDay() ==
                               tempDate.getWeekDay() &&
                           event->getEvRepeat() == Weekly) {
                    tempDay.addEvent(event);
                } else if (event->getEvDate().getDay() == tempDate.getDay() &&
                           event->getEvDate().getMonth() ==
                               tempDate.getMonth() &&
                           event->getEvRepeat() == Annually) {
                    if (event->exportData().find("eventBirthday") !=
                        std::string::npos) {
                        eventBirthday *tempBirthdayEvent =
                            dynamic_cast<eventBirthday *>(event);
                        if (tempBirthdayEvent->getBirthDate().getYear() >
                            tempDate.getYear()) {
                            continue;
                        }
                        event->setEvDescription(
                            std::to_string(
                                tempDate.getYear() -
                                tempBirthdayEvent->getBirthDate().getYear()) +
                            " urodziny " +
                            tempBirthdayEvent->getPersonalData().first + " " +
                            tempBirthdayEvent->getPersonalData().second);
                    }
                    tempDay.addEvent(event);
                } else if (event->getEvRepeat() == Daily) {
                    tempDay.addEvent(event);
                }
                if (event->exportData().find("eventHoliday") !=
                    std::string::npos) {
                    std::cout << "DEBUGEVENTHOLIDAY:\n";
                    eventHoliday *tempHolidayEvent =
                        dynamic_cast<eventHoliday *>(event);
                    std::cout << "DATE EVENT START: "
                              << tempHolidayEvent->getEvBegin().stringify()
                              << "DATE DAY: " << tempDate.stringify()
                              << std::endl;
                    if (tempDate > tempHolidayEvent->getEvBegin() &&
                        tempHolidayEvent->getEvEnd() >= tempDate &&
                        tempDate.getYear() >=
                            tempHolidayEvent->getEvBegin().getYear() &&
                        tempDate.getYear() <=
                            tempHolidayEvent->getEvEnd().getYear()) {
                        std::cout << "DEBUG ADDED HOLIDAY\n";
                        tempDay.addEvent(event);
                    }
                }
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
    } catch (...) {
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
        this->events.push_back(tempEvent);
        // return tempEvent;
    } else if (eventClass == "BIRTHDAY") {
        eventBirthday *tempEvent =
            new eventBirthday(newEvDate, "Urodziny", Annually, newEvFirstname,
                              newEvLastname, newBirthdate);
        this->days[newEvDate.getDay() - 1].addEvent(tempEvent);
        this->events.push_back(tempEvent);
    } else if (eventClass == "HOLIDAY") {
        eventHoliday *tempEvent =
            new eventHoliday(newEvDate, newEvName, newEvRepeat,
                             newEvDescription, beginDate, endDate);
        std::cout << "DEBUG: " << tempEvent->exportData();
        this->days[newEvDate.getDay() - 1].addEvent(tempEvent);
        this->events.push_back(tempEvent);
    }
    // return nullptr;
}

std::vector<event *> calendarView::getEvents() const noexcept {
    return this->events;
}

void calendarView::setEvents(std::vector<event *> newEvents) {
    this->events = newEvents;
}

void calendarView::deleteEvent(std::string exportedEventData) {
    int indexToRemove = -1;
    for (int i = 0; i < events.size(); i++) {
        if (events[i]->stringifyEvent() == exportedEventData) {
            indexToRemove = i;
        }
    }
    if (indexToRemove >= 0) {
        events.erase(events.begin() + indexToRemove);
    }
}

} // namespace calendar