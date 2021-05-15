#include "mainwindow.h"
#include "./ui_mainwindow.h"
// #include "includes/date.h"
#include "iostream"
#include <functional>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
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
    labelsList << "Poniedziałek"
               << "Wtorek"
               << "Środa"
               << "Czwartek"
               << "Piatek"
               << "Sobota"
               << "Niedziela";
    dayElementInterface->setHorizontalHeaderLabels(labelsList);
    ui->monthTableView->setModel(dayElementInterface);
    // temp @TODO
    // QStandardItem *tempItem = new QStandardItem("1");
    // tempItem->setTextAlignment(Qt::AlignCenter);
    // tempItem->setEditable(0);
    // dayElementInterface->setItem(0, 0, tempItem);
    calendar::date tempToday;
    tempToday.setCurrentDate();
    newCalendarView.setTodayDate();
    std::cout << "DEBUG: " << (int)tempToday.getMonth() << std::endl;
    newCalendarView.calculateCurrentMonth(
        dayElementInterface, tempToday.getMonth(), tempToday.getYear(),
        this->monthlyEventsInterface);
    datePlaceholder.setDay(tempToday.getDay());
    datePlaceholder.setMonth(tempToday.getMonth());
    datePlaceholder.setYear(tempToday.getYear());
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

    QMenu itemMenu;
    itemMenu.addAction("Dodaj przypomnienie", this,
                       SLOT(createNewReminderEvent()));
    itemMenu.addAction("Dodaj wakacje", this, SLOT(createNewHolidayEvent()));
    itemMenu.addAction("Dodaj urodziny", this, SLOT(createNewBirthdayEvent()));

    itemMenu.exec(globalPos);
}

void MainWindow::createNewReminderEvent() {
    calendar::date tempDate(12, calendar::Jan, 2021);
    calendar::date *selectedDate;
    for (auto index :
         this->ui->monthTableView->selectionModel()->selectedIndexes()) {
        int tempData = index.data().toInt();
        selectedDate = new calendar::date(tempData, datePlaceholder.getMonth(),
                                          datePlaceholder.getYear());
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
    this->newCalendarView.addEventFromDialog(
        this->ui->monthTableView, evName.toStdString(), "BRAK OPISU",
        evLocation.toStdString(), evType.toStdString(), "TEST", "TEST",
        *selectedDate, tempDate, tempDate, tempDate, evRepeatType, "REMINDER");
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
}

void MainWindow::createNewBirthdayEvent() {
    calendar::date tempDate(12, calendar::Jan, 2021);
    calendar::date *selectedDate;
    for (auto index :
         this->ui->monthTableView->selectionModel()->selectedIndexes()) {
        int tempData = index.data().toInt();

        selectedDate = new calendar::date(tempData, datePlaceholder.getMonth(),
                                          datePlaceholder.getYear());
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
}

void MainWindow::createNewHolidayEvent() {
    calendar::date tempDate(12, calendar::Jan, 2021);
    calendar::date *selectedDate;
    for (auto index :
         this->ui->monthTableView->selectionModel()->selectedIndexes()) {
        int tempData = index.data().toInt();
        selectedDate = new calendar::date(tempData, datePlaceholder.getMonth(),
                                          datePlaceholder.getYear());
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
    this->newCalendarView.addEventFromDialog(
        this->ui->monthTableView, evName.toStdString(), evDesc.toStdString(),
        "NONE", "NONE", "TEST", "TEST", *selectedDate, tempDate, *selectedDate,
        endDate, evRepeatType, "HOLIDAY");
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
}

void MainWindow::deleteTodoItem() {
    std::cout << "Deleting items\n";
    this->newTodoView.deleteItem(this->ui->listView, todoElementInterface);
}

void MainWindow::deleteEventItem() {
    // std::cout << "Deleting items\n";
    // this->newTodoView.deleteItem(this->ui->listView, todoElementInterface);
}

void MainWindow::getEventsForDay(const QModelIndex &index) {
    // std::cout << index.data().toInt() << std::endl;
    this->newCalendarView.getEventsForDay(this->monthlyEventsInterface,
                                          index.data().toInt());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_changeCalendarViewMonthly_clicked() {
    ui->eventsListView->show();
    ui->monthTableView->show();
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
    datePlaceholder.incrementMonth();
    dayElementInterface->clear();
    dayElementInterface->setHorizontalHeaderLabels(labelsList);
    newCalendarView.calculateCurrentMonth(
        dayElementInterface, datePlaceholder.getMonth(),
        datePlaceholder.getYear(), this->monthlyEventsInterface);
    ui->yearLabel->setText(std::to_string(datePlaceholder.getYear()).c_str());
    ui->monthLabel->setText(
        this->newCalendarView.getMonthName(datePlaceholder.getMonth()).c_str());
    monthlyEventsInterface->clear();
}

void MainWindow::on_prevMonth_clicked() {
    datePlaceholder.decrementMonth();
    dayElementInterface->clear();
    dayElementInterface->setHorizontalHeaderLabels(labelsList);
    newCalendarView.calculateCurrentMonth(
        dayElementInterface, datePlaceholder.getMonth(),
        datePlaceholder.getYear(), this->monthlyEventsInterface);
    ui->yearLabel->setText(std::to_string(datePlaceholder.getYear()).c_str());
    ui->monthLabel->setText(
        this->newCalendarView.getMonthName(datePlaceholder.getMonth()).c_str());
    monthlyEventsInterface->clear();
}

void MainWindow::on_changeCalendarViewWeekly_clicked() {
    ui->monthTableView->hide();
    ui->eventsListView->hide();
}
