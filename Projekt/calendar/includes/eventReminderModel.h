#pragma once
#include "eventModel.h"
#include <string>

namespace calendar {
class eventReminder : public event {
  private:
    std::string evLocation;
    std::string evType;

  public:
    /**
     * @brief konstruktor bezargumentowy, tworzy pusty obiekt o wszystkich
     * polach NULL
     */
    eventReminder();

    /**
     * @brief konstruktor wieloargumentowy, tworzy obiekt o wszystkich
     * właściwościach
     */
    eventReminder(const date &newDate, const std::string &newName,
                  const repeatCycle &newRepeat,
                  const std::string &newEvLocation,
                  const std::string &newEvType);

    /**
     * @brief pobiera lokalizację wydarzenia
     *
     * @return lokalizacja wydarzenia
     */
    std::string getEvLocation() const noexcept;

    /**
     * @brief ustawia nową lokalizację wydarzenia
     *
     * @param newEvLocation nowa lokalizacja
     */
    void setEvLocation(const std::string &newEvLocation);

    /**
     * @brief pobiera typ wydarzenia
     *
     * @return typ wydarzenia
     */
    std::string getEvType() const noexcept;

    /**
     * @brief ustawia nowy typ wydarzenia
     *
     * @param newEvType nowy typ wydarzenia
     */
    void setEvType(const std::string &newEvType);

    /**
     * @brief deklaracja metody wirtualnej z klasy event
     *
     */
    virtual std::string stringifyEvent() const noexcept;

    virtual std::string exportData() const noexcept;
};
} // namespace calendar
