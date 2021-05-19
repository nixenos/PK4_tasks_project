#include "../includes/eventHolidayModel.h"
#include <typeinfo>
namespace calendar {
eventHoliday::eventHoliday() {}

eventHoliday::eventHoliday(const date &newDate, const std::string &newName,
                           const repeatCycle &newRepeat,
                           const std::string &newEvDescription,
                           const date &newEvBegin, const date &newEvEnd) {
    this->setEvBegin(newEvBegin);
    this->setEvEnd(newEvEnd);
    this->setEvDate(newDate);
    this->setEvName(newName);
    this->setEvRepeat(newRepeat);
    this->setEvDescription(newEvDescription);
}

date eventHoliday::getEvBegin() const noexcept { return this->evBegin; }

void eventHoliday::setEvBegin(const date &newEvBegin) {
    this->evBegin = newEvBegin;
}

date eventHoliday::getEvEnd() const noexcept { return this->evEnd; }

void eventHoliday::setEvEnd(const date &newEvEnd) { this->evEnd = newEvEnd; }

std::string eventHoliday::stringifyEvent() const noexcept {
    return event::stringifyEvent();
}

std::string eventHoliday::exportData() const noexcept {
    std::string result = std::string(typeid(this).name()) + ":" +
                         this->getEvName() + ":" + this->getEvDescription() +
                         ":" + this->getEvDate().stringify() + ":" +
                         std::to_string(this->getEvRepeat()) + ":" +
                         this->getEvBegin().stringify() + ":" +
                         this->getEvEnd().stringify() + "\n";
    return result;
}

} // namespace calendar