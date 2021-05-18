/**
 * @file eventHolidayModel.h
 * @author Wojciech Janota
 * @brief
 * @version 0.1
 * @date 2021-05-18
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include "eventModel.h"

namespace calendar {
class eventHoliday : public event {
  private:
    date evBegin;
    date evEnd;

  public:
    /**
     * @brief konstruktor bezargumentowy, tworzy pusty obiekt
     */
    eventHoliday();

    /**
     * @brief konstrukot wieloargumentowy, tworzący pełny obiekt klasy
     * eventHoliday
     */
    eventHoliday(const date &newDate, const std::string &newName,
                 const repeatCycle &newRepeat,
                 const std::string &newEvDescription, const date &newEvBegin,
                 const date &newEvEnd);

    /**
     * @brief pobiera początek trwania wydarzenia
     *
     * @return początek trwania wydarzenia
     */
    date getEvBegin() const noexcept;

    /**
     * @brief ustawia początek trwania wydarzenia
     *
     * @param newEvBegin nowy początek
     */
    void setEvBegin(const date &newEvBegin);

    /**
     * @brief pobiera koniec trwania wydarzenia
     *
     * @return koniec trwania wydarzenia
     */
    date getEvEnd() const noexcept;

    /**
     * @brief ustawia koniec trwania wydarzenia
     *
     * @param newEvEnd nowy koniec
     */
    void setEvEnd(const date &newEvEnd);

    /**
     * @brief deklaracja metody wirtualnej z klasy event
     *
     */
    virtual std::string stringifyEvent() const noexcept;

    /**
     * @brief Eksportuje dane do zapisu
     *
     * @return std::string wyeksportowane dane
     */
    virtual std::string exportData() const noexcept;
};
} // namespace calendar
