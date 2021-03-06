#include "../includes/eventReminderModel.h"
#include <iostream>
#include <typeinfo>
namespace calendar {
eventReminder::eventReminder(const date &newDate, const std::string &newName,
                             const repeatCycle &newRepeat,
                             const std::string &newEvLocation,
                             const std::string &newEvType)
    : event(newDate, newName, "null", newRepeat) {
    this->setEvLocation(newEvLocation);
    this->setEvType(newEvType);
}

eventReminder::eventReminder() {}

void eventReminder::setEvLocation(const std::string &newEvLocation) {
    this->evLocation = newEvLocation;
}

void eventReminder::setEvType(const std::string &newEvType) {
    this->evType = newEvType;
}
std::string eventReminder::stringifyEvent() const noexcept {
    std::string resultString = event::stringifyEvent() +
                               "LOKALIZACJA: " + this->getEvLocation() +
                               ", TYP: " + this->getEvType();
    std::cout << "DERIVED\n";
    return resultString;
}

std::string eventReminder::getEvType() const noexcept { return this->evType; }

std::string eventReminder::getEvLocation() const noexcept {
    return this->evLocation;
}

std::string calendar::eventReminder::exportData() const noexcept {
    std::string objName = typeid(this).name();
    std::string result = objName + ":" + this->getEvName() + ":" +
                         this->getEvDescription() + ":" +
                         this->getEvDate().stringify() + ":" +
                         std::to_string(this->getEvRepeat()) + ":" +
                         this->getEvLocation() + ":" + this->getEvType() + "\n";
    return result;
}

} // namespace calendar