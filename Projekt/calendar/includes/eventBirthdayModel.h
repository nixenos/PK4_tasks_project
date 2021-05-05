#pragma once
#include "eventModel.h"
#include <utility>

namespace calendar {
class eventBirthday : public event {
  private:
    std::string firstName;
    std::string lastName;
    date birthDate;

  public:
    /**
     * @brief konstruktor bezargumentowy, tworzy pusty obiekt, wszystko ustawia
     * na NULL
     */
    eventBirthday();

    /**
     * @brief konstruktor tworzący pełny obiekt klasy eventBirthday
     */
    eventBirthday(const date &newDate, const std::string &newName,
                  const repeatCycle &newRepeat, const std::string &newFirstName,
                  const std::string &newLastName, const date &newBirthDate);

    /**
     * @brief pobiera dane osoby mającej urodziny
     *
     * @return para imię, nazwisko osoby
     */
    std::pair<std::string, std::string> getPersonalData() const noexcept;

    /**
     * @brief ustawia dane osoby mającej urodziny
     *
     * @param newPersonalData nowe dane osoby
     */
    void
    setPersonalData(const std::pair<std::string, std::string> &newPersonalData);

    /**
     * @brief pobiera dzień urodzin osoby
     *
     * @return data narodzin osoby
     */
    date getBirthDate() const noexcept;

    /**
     * @brief ustawia nowy dzień urodzin osoby
     *
     * @param newBirthDate nowa data narodzin osoby
     */
    void setBirthDate(const date &newBirthDate);

    /**
     * @brief redeclaration of setEvRepeat function
     */
    void setEvRepeat(const calendar::repeatCycle &newEvRepeat);

    /**
     * @brief deklaracja metody wirtualnej z klasy event
     *
     */
    virtual std::string stringifyEvent() const noexcept;
};
} // namespace calendar
