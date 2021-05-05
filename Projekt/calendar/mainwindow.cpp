#include "mainwindow.h"
#include "./ui_mainwindow.h"
// #include "includes/date.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

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
    dayList.resize(3000);
    for (int i = 0; i < dayList.size(); i++) {
        dayList[i].resize(12);
        for (int j = 0; j < dayList[i].size(); j++) {
            calendar::day tempDay(tempToday);
            dayList[i][j].push_back(tempDay);
        }
    }
}

void MainWindow::showContextMenu(const QPoint &pos) {
    QPoint globalPos = this->ui->listView->mapToGlobal(pos);

    QMenu itemMenu;
    itemMenu.addAction("Usuń", this, SLOT(deleteTodoItem()));

    itemMenu.exec(globalPos);
}

void MainWindow::showContextMenuDayElement(const QPoint &pos) {
    QPoint globalPos = this->ui->monthTableView->mapToGlobal(pos);

    QMenu itemMenu;
    itemMenu.addAction("Dodaj przypomnienie", this,
                       SLOT(createNewReminderEvent()));
    itemMenu.addAction("Dodaj wakacje", this, SLOT());
    itemMenu.addAction("Dodaj urodziny", this, SLOT());

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
    this->newCalendarView.addEventFromDialog(
        this->ui->monthTableView, evName.toStdString(), "BRAK OPISU",
        evLocation.toStdString(), evType.toStdString(), "TEST", "TEST",
        *selectedDate, tempDate, tempDate, tempDate, calendar::None,
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
    this->dayList[datePlaceholder.getYear()][datePlaceholder.getMonth()] =
        this->newCalendarView.getDays();
}

void MainWindow::deleteTodoItem() {
    std::cout << "Deleting items\n";
    this->newTodoView.deleteItem(this->ui->listView, todoElementInterface);
}

void MainWindow::getEventsForDay(const QModelIndex &index) {
    // std::cout << index.data().toInt() << std::endl;
    this->newCalendarView.getEventsForDay(this->monthlyEventsInterface,
                                          index.data().toInt());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_changeCalendarViewMonthly_clicked() {}

void MainWindow::saveToFiles() {
    // @TODO implement saving to files
    // this->close();
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
    if (this->dayList[datePlaceholder.getYear()]
                     [(int)datePlaceholder.getMonth()]
                         .size() > 10) {
        newCalendarView.setDays(
            dayList[datePlaceholder.getYear()][datePlaceholder.getMonth()]);
    } else {
        dayList[datePlaceholder.getYear()][datePlaceholder.getMonth()] =
            newCalendarView.getDays();
    }
    ui->yearLabel->setText(std::to_string(datePlaceholder.getYear()).c_str());
    ui->monthLabel->setText(
        this->newCalendarView.getMonthName(datePlaceholder.getMonth()).c_str());
}

void MainWindow::on_prevMonth_clicked() {
    datePlaceholder.decrementMonth();
    dayElementInterface->clear();
    dayElementInterface->setHorizontalHeaderLabels(labelsList);
    newCalendarView.calculateCurrentMonth(
        dayElementInterface, datePlaceholder.getMonth(),
        datePlaceholder.getYear(), this->monthlyEventsInterface);
    if (this->dayList[datePlaceholder.getYear()][datePlaceholder.getMonth()]
            .size() > 10) {
        newCalendarView.setDays(
            dayList[datePlaceholder.getYear()][datePlaceholder.getMonth()]);
    } else {
        dayList[datePlaceholder.getYear()][datePlaceholder.getMonth()] =
            newCalendarView.getDays();
    }
    ui->yearLabel->setText(std::to_string(datePlaceholder.getYear()).c_str());
    ui->monthLabel->setText(
        this->newCalendarView.getMonthName(datePlaceholder.getMonth()).c_str());
}
