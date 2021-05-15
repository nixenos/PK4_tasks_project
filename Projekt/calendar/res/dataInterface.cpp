#include "../includes/dataInterface.h"

namespace calendar {
template <> void dataInterface<event *>::exportDataToSaveFile() {
    this->saveFile.open("savefileEvents.yml",
                        std::ios::out | std::fstream::out);
    for (auto item : itemList) {
        std::cout << "ZAPISYWANIE:";
        std::cout << item->exportData() << std::endl;
        this->saveFile << item->exportData();
    }
    saveFile.close();
}

template <> void dataInterface<todoElement>::exportDataToSaveFile() {
    this->saveFile.open("savefileTodoElements.yml",
                        std::ios::out | std::fstream::out);
    for (auto item : itemList) {
        std::cout << "ZAPISYWANIE:";
        std::cout << item.exportData() << std::endl;
        this->saveFile << item.exportData();
    }
    saveFile.close();
}

template <> void dataInterface<event *>::importDataFromSaveFile() {
    this->saveFile.open("savefileEvents.yml", std::ios::in | std::ios::out |
                                                  std::fstream::in |
                                                  std::fstream::out);
    std::string buffer;
    std::vector<std::string> result;
    if (saveFile.is_open()) {
        while (getline(saveFile, buffer)) {
            // std::cout << buffer << std::endl;
            result.clear();
            std::stringstream sstream(buffer);
            while (sstream.good()) {
                std::string substr;
                getline(sstream, substr, ':');
                result.push_back(substr);
                std::cout << substr << std::endl;
            }
            if (result[0].find("eventReminder") != std::string::npos) {
                date tempDate(atoi(result[3].c_str()),
                              static_cast<monthModel>(atoi(result[4].c_str())),
                              atoi(result[5].c_str()));
                eventReminder *tempEvent = new eventReminder(
                    tempDate, result[1],
                    static_cast<repeatCycle>(atoi(result[6].c_str())),
                    result[7], result[8]);
                this->itemList.push_back(tempEvent);
                std::cout << "DEBUGDATAINTERFACE:"
                          << tempEvent->stringifyEvent();
            } else if (result[0].find("eventBirthday") != std::string::npos) {
                date tempDate(atoi(result[3].c_str()),
                              static_cast<monthModel>(atoi(result[4].c_str())),
                              atoi(result[5].c_str()));
                date tempBirthDate(
                    atoi(result[7].c_str()),
                    static_cast<monthModel>(atoi(result[8].c_str())),
                    atoi(result[9].c_str()));
                eventBirthday *tempEvent = new eventBirthday(
                    tempDate, result[1],
                    static_cast<repeatCycle>(atoi(result[6].c_str())),
                    result[10], result[11], tempBirthDate);
                this->itemList.push_back(tempEvent);
                std::cout << "DEBUGDATAINTERFACE:"
                          << tempEvent->stringifyEvent();
            } else if (result[0].find("eventHoliday") != std::string::npos) {
                date tempDate(atoi(result[3].c_str()),
                              static_cast<monthModel>(atoi(result[4].c_str())),
                              atoi(result[5].c_str()));
                date tempEvBegin(
                    atoi(result[7].c_str()),
                    static_cast<monthModel>(atoi(result[8].c_str())),
                    atoi(result[9].c_str()));
                date tempEvEnd(
                    atoi(result[10].c_str()),
                    static_cast<monthModel>(atoi(result[11].c_str())),
                    atoi(result[12].c_str()));
                eventHoliday *tempEvent = new eventHoliday(
                    tempDate, result[1],
                    static_cast<repeatCycle>(atoi(result[6].c_str())),
                    result[2], tempEvBegin, tempEvEnd);
                this->itemList.push_back(tempEvent);
                std::cout << "DEBUGDATAINTERFACE:"
                          << tempEvent->stringifyEvent();
            }
        }
        saveFile.close();
    }
}

template <> void dataInterface<todoElement>::importDataFromSaveFile() {
    this->saveFile.open("savefileTodoElements.yml",
                        std::ios::in | std::ios::out | std::fstream::in |
                            std::fstream::out);
    std::string buffer;
    std::vector<std::string> result;
    if (saveFile.is_open()) {
        while (getline(saveFile, buffer)) {
            // std::cout << buffer << std::endl;
            result.clear();
            std::stringstream sstream(buffer);
            while (sstream.good()) {
                std::string substr;
                getline(sstream, substr, ':');
                result.push_back(substr);
                std::cout << substr << std::endl;
            }
            todoElement tempTodoElement(atoi(result[0].c_str()), result[1]);
            itemList.push_back(tempTodoElement);
        }
        saveFile.close();
    }
}

} // namespace calendar