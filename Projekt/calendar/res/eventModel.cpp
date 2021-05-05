#include "../includes/eventModel.h"
#include <iostream>

calendar::event::event() {
    calendar::date nullDate(1, Jan, 2012);
    std::string nullName = "NULL";
    repeatCycle nullRepeat = None;
    this->setEvDate(nullDate);
    this->setEvName(nullName);
    this->setEvDescription(nullName);
    this->setEvRepeat(nullRepeat);
}

calendar::event::event(const date &newDate, const std::string &newName,
                       const std::string &newEvDescription,
                       const repeatCycle &newRepeat) {
    this->setEvDate(newDate);
    this->setEvName(newName);
    this->setEvDescription(newEvDescription);
    this->setEvRepeat(newRepeat);
}

calendar::date calendar::event::getEvDate() const noexcept {
    return this->evDate;
}

void calendar::event::setEvDate(const calendar::date &newDate) {
    this->evDate = newDate;
}

std::string calendar::event::getEvDescription() const noexcept {
    return this->evDescription;
}

void calendar::event::setEvDescription(const std::string &newEvDesription) {
    this->evDescription = newEvDesription;
}

std::string calendar::event::getEvName() const noexcept { return this->evName; }

void calendar::event::setEvName(const std::string &newEvName) {
    this->evName = newEvName;
}

calendar::repeatCycle calendar::event::getEvRepeat() const noexcept {
    return this->evRepeat;
}

void calendar::event::setEvRepeat(const calendar::repeatCycle &newEvRepeat) {
    this->evRepeat = newEvRepeat;
}

std::string calendar::event::stringifyEvent() const noexcept {
    std::string result = "NAZWA: " + this->getEvName() +
                         ", OPIS: " + this->getEvDescription() + ", ";
    std::cout << "BASE\n";
    return result;
}
