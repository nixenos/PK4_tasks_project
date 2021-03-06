/**
 * @file todoElement.h
 * @author Wojciech Janota
 * @brief
 * @version 0.1
 * @date 2021-05-18
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <iostream>
#include <string>

namespace calendar {
/**
 * @brief klasa przechowująca elementy listy zadań do zrobienia
 *
 */
class todoElement {
  private:
    unsigned long int position;
    std::string dataRecord;

  public:
    /**
     * @brief Konstruktor bezargumentowy, tworzy obiekt ignorowany przez widok
     * (position=0, dataRecord="NULL")
     *
     */
    todoElement();

    /**
     * @brief Właściwy konstruktor dwuargumentowy
     *
     * @param position pozycja elementu na liście
     * @param dataRecord rekord dodawany do listy
     */
    todoElement(const unsigned long int &position,
                const std::string &dataRecord);

    /**
     * @brief Pobiera wartość pola position (pozycję elementu na liście)
     *
     * @return const unsigned long int& pozycja elementu na liście
     */
    const unsigned long int &getPosition() const;

    /**
     * @brief Ustawia wartość pola position (pozycję elementu na liście)
     *
     * @param newPosition nowa pozycja elementu na liście
     */
    void setPosition(const unsigned long int &newPosition);

    /**
     * @brief Pobiera wartość pola dataRecord
     *
     * @return const std::string& rekord danego elementu listy
     */
    const std::string &getDataRecord() const;

    /**
     * @brief Ustawia wartość pola dataRecord
     *
     * @param newDataRecord nowa wartość rekordu danych elementu listy
     */
    void setDataRecord(const std::string &newDataRecord);

    /**
     * @brief Inkrementuje pozycję elementu
     *
     */
    void incrementPosition();

    /**
     * @brief Dekrementuje pozycję elementu
     *
     */
    void decrementPosition();

    /**
     * @brief Eksportuje dane do zapisu
     *
     * @return std::string wyeksportowane dane
     */
    std::string exportData() const noexcept;
};
} // namespace calendar
// namespace todo
