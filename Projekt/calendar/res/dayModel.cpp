#include "../includes/dayModel.h"

namespace calendar {
/**
 * @brief Construct a new day object
 *
 */
day::day() {
    date newDate(12, Jan, 2012);
    this->setDate(newDate);
}

day::day(const date &newDate) { this->setDate(newDate); }

void day::setDate(const date &newDate) { this->dayDate = newDate; }

date day::getDate() const noexcept { return this->dayDate; }

void day::addEvent(event *newEvent) { this->events.push_back(newEvent); }

std::vector<event *> day::getEvents() const noexcept { return this->events; }
} // namespace calendar