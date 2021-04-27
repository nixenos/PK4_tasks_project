#include "../includes/eventHolidayModel.h"

namespace calendar {
eventHoliday::eventHoliday() {}

eventHoliday::eventHoliday(const date &newDate, const std::string &newName,
                           const repeatCycle &newRepeat, const date &newEvBegin,
                           const date &newEvEnd) {
    this->setEvBegin(newEvBegin);
    this->setEvEnd(newEvEnd);
    this->setEvDate(newDate);
    this->setEvName(newName);
    this->setEvRepeat(newRepeat);
}

} // namespace calendar