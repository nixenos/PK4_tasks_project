/**
 * @file dataInterface.h
 * @author Wojciech Janota
 * @brief
 * @version 0.1
 * @date 2021-05-18
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include "event.h"
#include "eventBirthdayModel.h"
#include "eventHolidayModel.h"
#include "eventReminderModel.h"
#include "todoElement.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace calendar {
/**
 * @brief Klasa interfejs do zapisu danych do pliku.
 *
 * @tparam T todoElement lub event
 */
template <class T> class dataInterface {
  private:
    std::vector<T> itemList;
    std::fstream saveFile;

  public:
    /**
     * @brief Konstruktor bezargumentowy.
     *
     */
    dataInterface();

    /**
     * @brief Konstruktor przyjmujący listę elementów do zapisania.
     *
     * @param newItemList lista elementów
     */
    dataInterface(std::vector<T> newItemList);

    /**
     * @brief Pobiera dane do interfejsu.
     *
     * @param importedList lista elementów do importu
     */
    void loadDataToInterface(std::vector<T> importedList);

    /**
     * @brief Pobiera dane z interfejsu.
     *
     * @return std::vector<T> lista pobranych danych
     */
    std::vector<T> loadDataFromInterface();

    /**
     * @brief Zapisuje dane do plików.
     *
     */
    void exportDataToSaveFile();

    /**
     * @brief Pobiera dane z plików.
     *
     */
    void importDataFromSaveFile();
};

template <class T> dataInterface<T>::dataInterface(std::vector<T> newItemList) {
    this->itemList = newItemList;
}

template <class T> dataInterface<T>::dataInterface() {}

template <class T>
void dataInterface<T>::loadDataToInterface(std::vector<T> importedList) {
    this->itemList = importedList;
}

template <class T> std::vector<T> dataInterface<T>::loadDataFromInterface() {
    return this->itemList;
}

} // namespace calendar