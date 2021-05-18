#include "mainwindow.h"
#include "./ui_mainwindow.h"
// #include "includes/date.h"
#include "iostream"
#include <functional>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    monthlyView = true;
    ui->setupUi(this);
    this->eventDataInterface.importDataFromSaveFile();
    this->eventList = this->eventDataInterface.loadDataFromInterface();
    this->newCalendarView.setEvents(this->eventList);
    this->todoElementDataInterface.importDataFromSaveFile();

    connect(ui->saveAction, &QAction::triggered, this,
            &MainWindow::saveToFiles);
    connect(ui->closeAction, &QAction::triggered, this,
            &MainWindow::closeWindow);
    todoElementInterface = new QStandardItemModel(nullptr);
    ui->listView->setModel(todoElementInterface);
    dayElementInterface = new QStandardItemModel(0, 0, nullptr);
    monthlyEventsInterface = new QStandardItemModel(nullptr);
    weeklyEventsInterface = new QStandardItemModel(nullptr);
    labelsList << "Poniedziałek"
               << "Wtorek"
               << "Środa"
               << "Czwartek"
               << "Piatek"
               << "Sobota"
               << "Niedziela";
    dayElementInterface->setHorizontalHeaderLabels(labelsList);
    ui->monthTableView->setModel(dayElementInterface);
    ui->monthTableView->setWordWrap(true);
    ui->monthTableView->setTextElideMode(Qt::ElideNone);
    // temp @TODO
    // QStandardItem *tempItem = new QStandardItem("1");
    // tempItem->setTextAlignment(Qt::AlignCenter);
    // tempItem->setEditable(0);
    // dayElementInterface->setItem(0, 0, tempItem);
    calendar::date tempToday;
    tempToday.setCurrentDate();
    newCalendarView.setTodayDate();
    newWeeklyCalendarView.setTodayDate();
    currentWeek = newWeeklyCalendarView.getCurrentWeekNumber(tempToday);
    std::cout << "DEBUG: " << (int)tempToday.getMonth() << std::endl;
    newCalendarView.calculateCurrentMonth(
        dayElementInterface, tempToday.getMonth(), tempToday.getYear(),
        this->monthlyEventsInterface);
    datePlaceholder.setDay(tempToday.getDay());
    datePlaceholder.setMonth(tempToday.getMonth());
    datePlaceholder.setYear(tempToday.getYear());
    datePlaceholder.setWeekNum(
        newWeeklyCalendarView.getCurrentWeekNumber(datePlaceholder));
    ui->yearLabel->setText(std::to_string(datePlaceholder.getYear()).c_str());
    ui->monthLabel->setText(
        newCalendarView.getMonthName(datePlaceholder.getMonth()).c_str());
    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listView, SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(showContextMenu(QPoint)));
    ui->monthTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->monthTableView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showContextMenuDayElement(QPoint)));
    ui->eventsListView->setModel(this->monthlyEventsInterface);
    connect(ui->monthTableView, SIGNAL(clicked(const QModelIndex &)), this,
            SLOT(getEventsForDay(const QModelIndex &)));
    newTodoView.setItems(this->todoElementDataInterface.loadDataFromInterface(),
                         todoElementInterface);
    this->ui->eventsListView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->eventsListView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showContextMenuEventElement(QPoint)));
}

void MainWindow::showContextMenu(const QPoint &pos) {
    QPoint globalPos = this->ui->listView->mapToGlobal(pos);

    QMenu itemMenu;
    itemMenu.addAction("Usuń", this, SLOT(deleteTodoItem()));

    itemMenu.exec(globalPos);
}

void MainWindow::showContextMenuEventElement(const QPoint &pos) {
    QPoint globalPos = this->ui->eventsListView->mapToGlobal(pos);

    QMenu itemMenu;
    itemMenu.addAction("Usuń", this, SLOT(deleteEventItem()));

    itemMenu.exec(globalPos);
}

void MainWindow::showContextMenuDayElement(const QPoint &pos) {
    QPoint globalPos = this->ui->monthTableView->mapToGlobal(pos);
    // std::cout << globalPos.x() << ", " << globalPos.y() << std::endl;
    int tempData = 0;
    QMenu itemMenu;
    for (auto index :
         this->ui->monthTableView->selectionModel()->selectedIndexes()) {
        tempData = index.data().toInt();
        std::cout << tempData << std::endl;
    }
    if (monthlyView) {
        itemMenu.addAction("Dodaj przypomnienie", this,
                           SLOT(createNewReminderEvent()));
        itemMenu.addAction("Dodaj wakacje", this,
                           SLOT(createNewHolidayEvent()));
        itemMenu.addAction("Dodaj urodziny", this,
                           SLOT(createNewBirthdayEvent()));
    } else if (!monthlyView) {
        if (tempData) {
            itemMenu.addAction("Dodaj przypomnienie", this,
                               SLOT(createNewReminderEvent()));
            itemMenu.addAction("Dodaj wakacje", this,
                               SLOT(createNewHolidayEvent()));
            itemMenu.addAction("Dodaj urodziny", this,
                               SLOT(createNewBirthdayEvent()));
        } else {
            itemMenu.addAction("Usuń wydarzenie", this,
                               SLOT(deleteEventItem()));
        }
    }
    itemMenu.exec(globalPos);
}

void MainWindow::createNewReminderEvent() {
    calendar::date tempDate(12, calendar::Jan, 2021);
    calendar::date *selectedDate;
    if (monthlyView == true) {
        for (auto index :
             this->ui->monthTableView->selectionModel()->selectedIndexes()) {
            int tempData = index.data().toInt();
            selectedDate =
                new calendar::date(tempData, datePlaceholder.getMonth(),
                                   datePlaceholder.getYear());
        }
    } else {
        for (auto index :
             this->ui->monthTableView->selectionModel()->selectedIndexes()) {
            // std::cout << this->weeklyEventsInterface->item(0, index.column())
            //                  ->data()
            //                  .toString()
            //                  .toStdString()

            //           << std::endl;
            // int tempData = this->weeklyEventsInterface->item(0,
            // index.column())
            //                    ->data()
            //                    .toInt();
            int tempData = index.data().toInt();
            std::cout << tempData;
            selectedDate =
                new calendar::date(tempData, datePlaceholder.getMonth(),
                                   datePlaceholder.getYear());
        }
    }
    if (selectedDate->getDay() == 0) {
        return;
    }
    QString evName = QInputDialog::getText(
        this, tr("Podaj dane 1/4"), tr("Nazwa wydarzenia:"), QLineEdit::Normal);
    QString evLocation = QInputDialog::getText(
        this, tr("Podaj dane 2/4"), tr("Lokalizacja:"), QLineEdit::Normal);
    QString evType =
        QInputDialog::getText(this, tr("Podaj dane 3/4"),
                              tr("Typ przypomnienia:"), QLineEdit::Normal);
    QString evRepeat = QInputDialog::getText(
        this, tr("Podaj dane 4/4"),
        tr("Powtarzanie (roczny, miesięczny, tygodniowy, dzienny, brak):"),
        QLineEdit::Normal);
    // td::vector<calendar::day> tempDays = 0;
    calendar::repeatCycle evRepeatType = calendar::None;
    std::hash<std::string> hashString;
    if (hashString(evRepeat.toStdString()) == hashString("brak")) {
        evRepeatType = calendar::None;
    } else if (hashString(evRepeat.toStdString()) == hashString("roczny")) {
        evRepeatType = calendar::Annually;
    } else if (hashString(evRepeat.toStdString()) == hashString("miesięczny")) {
        evRepeatType = calendar::Monthly;
    } else if (hashString(evRepeat.toStdString()) == hashString("tygodniowy")) {
        evRepeatType = calendar::Weekly;
    } else if (hashString(evRepeat.toStdString()) == hashString("dzienny")) {
        evRepeatType = calendar::Daily;
    } else {
        evRepeatType = calendar::None;
    }
    if (monthlyView) {
        this->newCalendarView.addEventFromDialog(
            this->ui->monthTableView, evName.toStdString(), "BRAK OPISU",
            evLocation.toStdString(), evType.toStdString(), "TEST", "TEST",
            *selectedDate, tempDate, tempDate, tempDate, evRepeatType,
            "REMINDER");
        // eventList[datePlaceholder.getYear()][datePlaceholder.getMonth()].push_back(
        //    tempEvent);
        for (auto index :
             this->ui->monthTableView->selectionModel()->selectedIndexes()) {
            getEventsForDay(index);
            QStandardItem *tempItem =
                this->dayElementInterface->itemFromIndex(index);
            tempItem->setForeground(Qt::darkGreen);
        }
        newCalendarView.calculateCurrentMonth(
            dayElementInterface, datePlaceholder.getMonth(),
            datePlaceholder.getYear(), this->monthlyEventsInterface);
        eventList = this->newCalendarView.getEvents();
    } else {
        this->newCalendarView.addEventFromDialog(
            this->ui->monthTableView, evName.toStdString(), "BRAK OPISU",
            evLocation.toStdString(), evType.toStdString(), "TEST", "TEST",
            *selectedDate, tempDate, tempDate, tempDate, evRepeatType,
            "REMINDER");
        eventList = this->newCalendarView.getEvents();
        newWeeklyCalendarView.setEvents(eventList);
        newWeeklyCalendarView.calculateCurrentWeek(
            dayElementInterface, datePlaceholder.getMonth(),
            datePlaceholder.getYear(), currentWeek,
            this->weeklyEventsInterface);
        ui->monthTableView->resizeRowsToContents();
    }
}

void MainWindow::createNewBirthdayEvent() {
    calendar::date tempDate(12, calendar::Jan, 2021);
    calendar::date *selectedDate;
    if (monthlyView == true) {
        for (auto index :
             this->ui->monthTableView->selectionModel()->selectedIndexes()) {
            int tempData = index.data().toInt();

            selectedDate =
                new calendar::date(tempData, datePlaceholder.getMonth(),
                                   datePlaceholder.getYear());
        }
    } else {
        for (auto index :
             this->ui->monthTableView->selectionModel()->selectedIndexes()) {
            // int tempData = this->weeklyEventsInterface->item(0,
            // index.column())
            //                    ->data()
            //                    .toInt();
            int tempData = index.data().toInt();
            selectedDate =
                new calendar::date(tempData, datePlaceholder.getMonth(),
                                   datePlaceholder.getYear());
        }
    }
    if (selectedDate->getDay() == 0) {
        return;
    }
    int inputYear = 2012;
    QString inputName = QInputDialog::getText(this, tr("Podaj dane 1/3"),
                                              tr("Imię:"), QLineEdit::Normal);
    QString inputSurname = QInputDialog::getText(
        this, tr("Podaj dane 2/3"), tr("Nazwisko:"), QLineEdit::Normal);
    inputYear = QInputDialog::getInt(this, tr("Podaj dane 3/3"),
                                     tr("Rok urodzenia:"), QLineEdit::Normal);
    calendar::date tempBirthDate(selectedDate->getDay(),
                                 selectedDate->getMonth(), inputYear);
    // td::vector<calendar::day> tempDays = 0;
    if (monthlyView) {
        this->newCalendarView.addEventFromDialog(
            this->ui->monthTableView, "Urodziny", "BRAK OPISU", "BRAK", "BRAK",
            inputName.toStdString(), inputSurname.toStdString(), *selectedDate,
            tempBirthDate, tempDate, tempDate, calendar::Annually, "BIRTHDAY");
        // eventList[datePlaceholder.getYear()][datePlaceholder.getMonth()].push_back(
        //    tempEvent);
        for (auto index :
             this->ui->monthTableView->selectionModel()->selectedIndexes()) {
            getEventsForDay(index);
            QStandardItem *tempItem =
                this->dayElementInterface->itemFromIndex(index);
            tempItem->setForeground(Qt::darkGreen);
            newCalendarView.calculateCurrentMonth(
                dayElementInterface, datePlaceholder.getMonth(),
                datePlaceholder.getYear(), this->monthlyEventsInterface);
            eventList = this->newCalendarView.getEvents();
        }
    } else {
        this->newCalendarView.addEventFromDialog(
            this->ui->monthTableView, "Urodziny", "BRAK OPISU", "BRAK", "BRAK",
            inputName.toStdString(), inputSurname.toStdString(), *selectedDate,
            tempBirthDate, tempDate, tempDate, calendar::Annually, "BIRTHDAY");
        eventList = this->newCalendarView.getEvents();
        newWeeklyCalendarView.setEvents(eventList);
        newWeeklyCalendarView.calculateCurrentWeek(
            dayElementInterface, datePlaceholder.getMonth(),
            datePlaceholder.getYear(), currentWeek,
            this->weeklyEventsInterface);
        ui->monthTableView->resizeRowsToContents();
    }
}

void MainWindow::createNewHolidayEvent() {
    calendar::date tempDate(12, calendar::Jan, 2021);
    calendar::date *selectedDate;
    if (monthlyView == true) {
        for (auto index :
             this->ui->monthTableView->selectionModel()->selectedIndexes()) {
            int tempData = index.data().toInt();
            selectedDate =
                new calendar::date(tempData, datePlaceholder.getMonth(),
                                   datePlaceholder.getYear());
        }
    } else {
        for (auto index :
             this->ui->monthTableView->selectionModel()->selectedIndexes()) {
            // int tempData = this->weeklyEventsInterface->item(0,
            // index.column())
            //                    ->data()
            //                    .toInt();
            int tempData = index.data().toInt();
            selectedDate =
                new calendar::date(tempData, datePlaceholder.getMonth(),
                                   datePlaceholder.getYear());
        }
    }
    if (selectedDate->getDay() == 0) {
        return;
    }
    QString evName = QInputDialog::getText(
        this, tr("Podaj dane 1/4"), tr("Nazwa wydarzenia:"), QLineEdit::Normal);
    QString evDesc = QInputDialog::getText(this, tr("Podaj dane 2/4"),
                                           tr("Opis:"), QLineEdit::Normal);
    QString evDate = QInputDialog::getText(
        this, tr("Podaj dane 3/4"),
        tr("Data końca wolnego (w formacie DD-MM-YYYY):"), QLineEdit::Normal);
    std::vector<std::string> tempResult;
    std::stringstream sstream(evDate.toStdString());
    while (sstream.good()) {
        std::string substr;
        getline(sstream, substr, '-');
        tempResult.push_back(substr);
        std::cout << substr << std::endl;
    }
    calendar::date endDate(
        atoi(tempResult[0].c_str()),
        static_cast<calendar::monthModel>(atoi(tempResult[1].c_str()) - 1),
        atoi(tempResult[2].c_str()));
    std::cout << endDate.stringify();
    QString evRepeat = QInputDialog::getText(
        this, tr("Podaj dane 4/4"),
        tr("Powtarzanie (roczny, miesięczny, tygodniowy, dzienny, brak):"),
        QLineEdit::Normal);
    // td::vector<calendar::day> tempDays = 0;
    calendar::repeatCycle evRepeatType = calendar::None;
    std::hash<std::string> hashString;
    if (hashString(evRepeat.toStdString()) == hashString("brak")) {
        evRepeatType = calendar::None;
    } else if (hashString(evRepeat.toStdString()) == hashString("roczny")) {
        evRepeatType = calendar::Annually;
    } else if (hashString(evRepeat.toStdString()) == hashString("miesięczny")) {
        evRepeatType = calendar::Monthly;
    } else if (hashString(evRepeat.toStdString()) == hashString("tygodniowy")) {
        evRepeatType = calendar::Weekly;
    } else if (hashString(evRepeat.toStdString()) == hashString("dzienny")) {
        evRepeatType = calendar::Daily;
    } else {
        evRepeatType = calendar::None;
    }
    if (monthlyView) {
        this->newCalendarView.addEventFromDialog(
            this->ui->monthTableView, evName.toStdString(),
            evDesc.toStdString(), "NONE", "NONE", "TEST", "TEST", *selectedDate,
            tempDate, *selectedDate, endDate, evRepeatType, "HOLIDAY");
        // eventList[datePlaceholder.getYear()][datePlaceholder.getMonth()].push_back(
        //    tempEvent);
        for (auto index :
             this->ui->monthTableView->selectionModel()->selectedIndexes()) {
            getEventsForDay(index);
            QStandardItem *tempItem =
                this->dayElementInterface->itemFromIndex(index);
            tempItem->setForeground(Qt::darkGreen);
            newCalendarView.calculateCurrentMonth(
                dayElementInterface, datePlaceholder.getMonth(),
                datePlaceholder.getYear(), this->monthlyEventsInterface);
            eventList = this->newCalendarView.getEvents();
        }
    } else {
        this->newCalendarView.addEventFromDialog(
            this->ui->monthTableView, evName.toStdString(),
            evDesc.toStdString(), "NONE", "NONE", "TEST", "TEST", *selectedDate,
            tempDate, *selectedDate, endDate, evRepeatType, "HOLIDAY");
        eventList = this->newCalendarView.getEvents();
        newWeeklyCalendarView.setEvents(eventList);
        newWeeklyCalendarView.calculateCurrentWeek(
            dayElementInterface, datePlaceholder.getMonth(),
            datePlaceholder.getYear(), currentWeek,
            this->weeklyEventsInterface);
        ui->monthTableView->resizeRowsToContents();
    }
    // delete selectedDate;
}

void MainWindow::deleteTodoItem() {
    std::cout << "Deleting items\n";
    this->newTodoView.deleteItem(this->ui->listView, todoElementInterface);
}

void MainWindow::deleteEventItem() {
    std::cout << "Deleting items\n";
    // monthlyEventsInterface <- model
    // ui->eventsListView
    if (monthlyView) {
        for (QModelIndex index :
             ui->eventsListView->selectionModel()->selectedIndexes()) {
            QStandardItem *tempItem =
                monthlyEventsInterface->itemFromIndex(index);
            newCalendarView.deleteEvent(index.data().toString().toStdString());
            monthlyEventsInterface->removeRow(index.row());
            this->eventList = newCalendarView.getEvents();
            // delete tempItem;
        }
        newCalendarView.calculateCurrentMonth(
            dayElementInterface, datePlaceholder.getMonth(),
            datePlaceholder.getYear(), this->monthlyEventsInterface);
        // this->newTodoView.deleteItem(this->ui->listView,
        // todoElementInterface);
    } else {
        std::string tempData = "";
        for (auto index :
             this->ui->monthTableView->selectionModel()->selectedIndexes()) {
            tempData = index.data().toString().toStdString();
            std::cout << tempData << std::endl;
            newCalendarView.deleteEvent(tempData);
            newWeeklyCalendarView.deleteEvent(tempData);
            this->eventList = newCalendarView.getEvents();
            newWeeklyCalendarView.setEvents(eventList);
            newWeeklyCalendarView.calculateCurrentWeek(
                dayElementInterface, datePlaceholder.getMonth(),
                datePlaceholder.getYear(), currentWeek,
                this->weeklyEventsInterface);
            weeklyEventsInterface->setData(index, "");
            ui->monthTableView->resizeRowsToContents();
        }
    }
}

void MainWindow::getEventsForDay(const QModelIndex &index) {
    // std::cout << index.data().toInt() << std::endl;
    this->newCalendarView.getEventsForDay(this->monthlyEventsInterface,
                                          index.data().toInt());
}

MainWindow::~MainWindow() {
    delete ui;
    delete monthlyEventsInterface;
    delete weeklyEventsInterface;
    delete dayElementInterface;
    delete todoElementInterface;
    for (auto ptr : eventList) {
        delete ptr;
    }
}

void MainWindow::on_changeCalendarViewMonthly_clicked() {
    // this->eventList = newWeeklyCalendarView.getEvents();
    // this->newCalendarView.setEvents(this->eventList);
    ui->eventsListView->show();
    ui->monthTableView->setModel(dayElementInterface);
    ui->monthTableView->show();
    ui->nextMonth->setText("Nast. miesiąc");
    ui->prevMonth->setText("Pop. miesiąc");
    monthlyView = true;
    newCalendarView.calculateCurrentMonth(
        dayElementInterface, datePlaceholder.getMonth(),
        datePlaceholder.getYear(), this->monthlyEventsInterface);
    ui->monthTableView->resizeRowsToContents();
}

void MainWindow::saveToFiles() {
    // @TODO implement saving to files
    // this->close();
    this->eventDataInterface.loadDataToInterface(this->eventList);
    this->eventDataInterface.exportDataToSaveFile();
    this->todoElementDataInterface.loadDataToInterface(newTodoView.getItems());
    this->todoElementDataInterface.exportDataToSaveFile();
    std::cout << "Saving...\n";
}

void MainWindow::closeWindow() {
    this->saveToFiles();
    this->close();
    monthlyEventsInterface->clear();
    weeklyEventsInterface->clear();
    dayElementInterface->clear();
    todoElementInterface->clear();
}

void MainWindow::on_addTodoItemButton_clicked() {
    /*QString inputText = ui->todoItemTextInput->toPlainText();
    std::string inputTextSTD = inputText.toStdString();
    std::cout << inputTextSTD << std::endl;
    int position = 1;
    if (inputTextSTD != "") {
        calendar::todoElement newElement(position, inputTextSTD);
        this->todoElementList.push_back(newElement);
        QStandardItem *tempNewItem =
            new QStandardItem(QString(newElement.getDataRecord().c_str()));
        this->todoElementInterface->appendRow(tempNewItem);
        ui->todoItemTextInput->clear();
    }*/
    QString inputText = ui->todoItemTextInput->toPlainText();
    std::string inputTextSTD = inputText.toStdString();
    this->newTodoView.addItem(inputTextSTD, this->todoElementInterface);
    ui->todoItemTextInput->clear();
}

void MainWindow::on_nextMonth_clicked() {
    if (monthlyView == true) {
        datePlaceholder.incrementMonth();
        dayElementInterface->clear();
        dayElementInterface->setHorizontalHeaderLabels(labelsList);
        newCalendarView.calculateCurrentMonth(
            dayElementInterface, datePlaceholder.getMonth(),
            datePlaceholder.getYear(), this->monthlyEventsInterface);
        ui->yearLabel->setText(
            std::to_string(datePlaceholder.getYear()).c_str());
        ui->monthLabel->setText(
            this->newCalendarView.getMonthName(datePlaceholder.getMonth())
                .c_str());
        monthlyEventsInterface->clear();
    } else {
        datePlaceholder.incrementWeek();
        if (++currentWeek == 53) {
            currentWeek = 1;
        }
        weeklyEventsInterface->clear();
        weeklyEventsInterface->setHorizontalHeaderLabels(labelsList);
        ui->yearLabel->setText(
            std::to_string(datePlaceholder.getYear()).c_str());
        ui->monthLabel->setText(
            this->newCalendarView.getMonthName(datePlaceholder.getMonth())
                .c_str());
        newWeeklyCalendarView.calculateCurrentWeek(
            dayElementInterface, datePlaceholder.getMonth(),
            datePlaceholder.getYear(), currentWeek,
            this->weeklyEventsInterface);
        ui->monthTableView->resizeRowsToContents();
    }
}

void MainWindow::on_prevMonth_clicked() {
    if (monthlyView == true) {
        datePlaceholder.decrementMonth();
        dayElementInterface->clear();
        dayElementInterface->setHorizontalHeaderLabels(labelsList);
        newCalendarView.calculateCurrentMonth(
            dayElementInterface, datePlaceholder.getMonth(),
            datePlaceholder.getYear(), this->monthlyEventsInterface);
        ui->yearLabel->setText(
            std::to_string(datePlaceholder.getYear()).c_str());
        ui->monthLabel->setText(
            this->newCalendarView.getMonthName(datePlaceholder.getMonth())
                .c_str());
        monthlyEventsInterface->clear();
    } else {
        datePlaceholder.decrementWeek();
        if (--currentWeek == 0) {
            currentWeek = 52;
        }
        weeklyEventsInterface->clear();
        weeklyEventsInterface->setHorizontalHeaderLabels(labelsList);
        ui->yearLabel->setText(
            std::to_string(datePlaceholder.getYear()).c_str());
        ui->monthLabel->setText(
            this->newCalendarView.getMonthName(datePlaceholder.getMonth())
                .c_str());
        newWeeklyCalendarView.calculateCurrentWeek(
            dayElementInterface, datePlaceholder.getMonth(),
            datePlaceholder.getYear(), currentWeek,
            this->weeklyEventsInterface);
        ui->monthTableView->resizeRowsToContents();
    }
}

void MainWindow::on_changeCalendarViewWeekly_clicked() {
    this->eventList = newCalendarView.getEvents();
    this->newWeeklyCalendarView.setEvents(this->eventList);
    // ui->monthTableView->hide();
    ui->monthTableView->setModel(weeklyEventsInterface);
    ui->eventsListView->hide();
    ui->nextMonth->setText("Nast. tydzień");
    ui->prevMonth->setText("Pop. tydzień");
    weeklyEventsInterface->setHorizontalHeaderLabels(labelsList);
    monthlyView = false;
    currentWeek = datePlaceholder.getWeekNum();
    newWeeklyCalendarView.calculateCurrentWeek(
        dayElementInterface, datePlaceholder.getMonth(),
        datePlaceholder.getYear(), currentWeek, this->weeklyEventsInterface);
    ui->monthTableView->resizeRowsToContents();
}
