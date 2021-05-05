#include "../includes/date.h"
#include <iostream>

calendar::date::date() { this->setCurrentDate(); }

calendar::date::date(const unsigned short &day,
                     const calendar::monthModel &month,
                     const unsigned long &year) {
    this->day = 1;
    this->month = Jan;
    this->year = 2012;
    this->setYear(year);
    this->setMonth(month);
    this->setDay(day);
}

calendar::weekDayModel
calendar::date::calculateWeekDay(const unsigned short &qDay,
                                 const calendar::monthModel &qMonth,
                                 const unsigned long &qYear) const {
    int calcWeekDay = 0;
    int Y, C, M, N, D;
    M = 1 + (9 + qMonth + 1) % 12;
    Y = qYear - (M > 10);
    C = Y / 100;
    D = Y % 100;
    N = ((13 * M - 1) / 5 + D + D / 4 + C / 4 + 5 * C + qDay) % 7;
    N = (6 + N) % 7;
    calcWeekDay = N;
    calendar::weekDayModel result =
        static_cast<calendar::weekDayModel>(calcWeekDay);
    return result;
}

void calendar::date::setCurrentDate() {
    time_t currentTime = time(0); // get current time to time_t struct
    struct tm tstruct;
    char buffer[80];
    tstruct = *localtime(&currentTime);
    strftime(buffer, sizeof(buffer), "%Y%m%d", &tstruct);
    std::string tempDateContainer(buffer);
    // std::cout << "BUFFER: " << tempDateContainer << std::endl;
    unsigned long int newYear = atoi(tempDateContainer.substr(0, 4).c_str());
    std::string tempMonth = "00";
    tempMonth[0] = tempDateContainer[4];
    tempMonth[1] = tempDateContainer[5];
    std::string tempDay = "00";
    tempDay[0] = tempDateContainer[6];
    tempDay[1] = tempDateContainer[7];
    unsigned short int newMonth = atoi(tempMonth.c_str()) - 1;
    unsigned short int newDay = atoi(tempDay.c_str());
    this->year = newYear;
    this->month = static_cast<calendar::monthModel>(newMonth);
    // this->day = static_cast<calendar::weekDayModel>(newDay);
    this->day = newDay;
    this->weekDay = this->calculateWeekDay(this->day, this->month, this->year);
}

void calendar::date::setDay(const unsigned short &newDay) {
    /*if (newDay > 0 && newDay <= 31) {
        if (this->month < 7 && !this->month % 2) {
            this->day = newDay;
        } else if (this->month > 6 && this->month % 2) {
            this->day = newDay;
        } else if (this->month == 1 && newDay <= 29) {
            if (!this->year % 4) {
                this->day = newDay;
            } else {
                if (newDay < 29) {
                    this->day = newDay;
                } else {
                    this->day = 0;
                }
            }
        } else if (newDay < 31) {
            this->day = newDay;
        } else {
            this->day = 0;
        }
    } else {
        this->day = 0;
    } */
    if ((this->month < 7 && this->month % 2 == 0) ||
        (this->month >= 7 && this->month % 2 == 1)) {
        if (newDay <= 31 && newDay > 0) {
            this->day = newDay;
        } else {
            this->day = 0;
        }
    } else if (this->month == 1) {
        if (this->year % 4 == 0) {
            if (newDay > 0 && newDay <= 29) {
                this->day = newDay;
            } else {
                this->day = 0;
            }
        } else {
            if (newDay > 0 && newDay < 29) {
                this->day = newDay;
            } else {
                this->day = 0;
            }
        }
    } else {
        if (newDay > 0 && newDay < 31) {
            this->day = newDay;
        } else {
            this->day = 0;
        }
    }
    this->weekDay = this->calculateWeekDay(this->day, this->month, this->year);
}

void calendar::date::setMonth(const calendar::monthModel &newMonth) {
    if (newMonth >= 0 && newMonth < 12) {
        this->month = newMonth;
        this->weekDay =
            this->calculateWeekDay(this->day, this->month, this->year);
    }
}

void calendar::date::setYear(const long unsigned int &newYear) {
    if (newYear < MAX_YEAR_CAP) {
        this->year = newYear;
        this->weekDay =
            this->calculateWeekDay(this->day, this->month, this->year);
    }
}

const calendar::monthModel calendar::date::getMonth() const {
    return this->month;
}

const calendar::weekDayModel calendar::date::getWeekDay() const {
    return this->weekDay;
}

const unsigned long int calendar::date::getYear() const { return this->year; }

const unsigned short calendar::date::getDay() const { return this->day; }

void calendar::date::incrementMonth() {
    int temp = this->month;
    if (temp == 11) {
        this->year++;
    }
    temp = (temp + 1) % 12;
    std::cout << temp << std::endl;
    monthModel newMonth = static_cast<calendar::monthModel>(temp);
    this->setMonth(newMonth);
}

void calendar::date::decrementMonth() {
    int temp = this->month;
    if (temp == 0) {
        this->year--;
        temp = 11;
    } else {
        temp = (temp - 1);
    }
    monthModel newMonth = static_cast<calendar::monthModel>(temp);
    this->setMonth(newMonth);
}