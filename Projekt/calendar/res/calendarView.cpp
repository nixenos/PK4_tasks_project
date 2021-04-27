#include "../includes/calendarView.h"
#include <chrono>
#include <ctime>
#include <regex>

namespace calendar {
void calendarView::setTodayDate() {
    date *newDate = new date;
    newDate->setCurrentDate();
    this->today = *newDate;
    std::vector<day> days;
}

date calendarView::getTodayDate() const noexcept { return this->today; }

void calendarView::calculateCurrentMonth(
    QStandardItemModel *dayElementInterface) {
    for (int i = 0; i < 31; i++) {
    }
}

} // namespace calendar