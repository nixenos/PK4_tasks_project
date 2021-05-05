/*!
 * \file dayModel.h
 * \author Wojciech Janota
 * \version 0.1
 * \date 27/04/2021
 *
 *
 *
 */

#pragma once
#include "eventBirthdayModel.h"
#include "eventHolidayModel.h"
#include "eventModel.h"
#include "eventReminderModel.h"
#include <vector>

namespace calendar {
class day {
  private:
    date dayDate;
    std::vector<event *> events;

  public:
    /**
     * @brief Konstruktor tworzący pusty obiekt o dacie 1.1.2012.
     */
    day();

    /**
     * @brief Konstruktor przyjmujący datę
     *
     * @param newDate nowa data dnia
     */
    day(const date &newDate);

    /**
     * @brief Pobiera datę dnia
     *
     * @return data
     */
    date getDate() const noexcept;

    /**
     * @brief Ustawia datę dnia
     *
     * @param newDate nowa data
     */
    void setDate(const date &newDate);

    /**
     * @brief Dodaje nowe wydarzenie
     *
     * @param newEvent nowe wydarzenie
     */
    void addEvent(event *newEvent);

    /**
     * @brief usuwa podane wydarzenie z listy
     *
     * @param delEvent wydarzenie do usunięcia
     */
    void deleteEvent(const event &delEvent);

    /**
     * @brief Pobiera wydarzenia danego dnia
     *
     * @return std::vector<date> wydarzenia
     */
    std::vector<event *> getEvents() const noexcept;
};
} // namespace calendar