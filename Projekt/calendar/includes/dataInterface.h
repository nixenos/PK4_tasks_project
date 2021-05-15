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
template <class T> class dataInterface {
  private:
    std::vector<T> itemList;
    std::fstream saveFile;

  public:
    dataInterface();

    dataInterface(std::vector<T> newItemList);

    void loadDataToInterface(std::vector<T> importedList);

    std::vector<T> loadDataFromInterface();

    void exportDataToSaveFile();

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