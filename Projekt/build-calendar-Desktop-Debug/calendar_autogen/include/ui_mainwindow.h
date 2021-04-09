/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *saveAction;
    QAction *closeAction;
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *changeCalendarViewMonthly;
    QPushButton *changeCalendarViewWeekly;
    QHBoxLayout *horizontalLayout_3;
    QLabel *yearLabel;
    QLabel *monthLabel;
    QTableView *monthTableView;
    QHBoxLayout *horizontalLayout;
    QLabel *changeDateLabel;
    QDateEdit *changeDateItem;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QTextEdit *todoItemInsert;
    QPushButton *addTodoItemButton;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *todoLabel;
    QListView *listView;
    QMenuBar *menubar;
    QMenu *menutest;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1307, 759);
        saveAction = new QAction(MainWindow);
        saveAction->setObjectName(QString::fromUtf8("saveAction"));
        closeAction = new QAction(MainWindow);
        closeAction->setObjectName(QString::fromUtf8("closeAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 30, 851, 581));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        changeCalendarViewMonthly = new QPushButton(widget);
        changeCalendarViewMonthly->setObjectName(QString::fromUtf8("changeCalendarViewMonthly"));

        horizontalLayout_2->addWidget(changeCalendarViewMonthly);

        changeCalendarViewWeekly = new QPushButton(widget);
        changeCalendarViewWeekly->setObjectName(QString::fromUtf8("changeCalendarViewWeekly"));

        horizontalLayout_2->addWidget(changeCalendarViewWeekly);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        yearLabel = new QLabel(widget);
        yearLabel->setObjectName(QString::fromUtf8("yearLabel"));
        QFont font;
        font.setPointSize(12);
        yearLabel->setFont(font);

        horizontalLayout_3->addWidget(yearLabel);

        monthLabel = new QLabel(widget);
        monthLabel->setObjectName(QString::fromUtf8("monthLabel"));
        monthLabel->setFont(font);

        horizontalLayout_3->addWidget(monthLabel);


        verticalLayout_2->addLayout(horizontalLayout_3);

        monthTableView = new QTableView(widget);
        monthTableView->setObjectName(QString::fromUtf8("monthTableView"));

        verticalLayout_2->addWidget(monthTableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        changeDateLabel = new QLabel(widget);
        changeDateLabel->setObjectName(QString::fromUtf8("changeDateLabel"));
        changeDateLabel->setFont(font);
        changeDateLabel->setFrameShape(QFrame::NoFrame);
        changeDateLabel->setFrameShadow(QFrame::Raised);
        changeDateLabel->setScaledContents(false);

        horizontalLayout->addWidget(changeDateLabel);

        changeDateItem = new QDateEdit(widget);
        changeDateItem->setObjectName(QString::fromUtf8("changeDateItem"));
        changeDateItem->setCalendarPopup(true);

        horizontalLayout->addWidget(changeDateItem);


        verticalLayout_2->addLayout(horizontalLayout);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(890, 520, 381, 91));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        todoItemInsert = new QTextEdit(widget1);
        todoItemInsert->setObjectName(QString::fromUtf8("todoItemInsert"));
        todoItemInsert->setMaximumSize(QSize(16777215, 260));

        verticalLayout->addWidget(todoItemInsert);

        addTodoItemButton = new QPushButton(widget1);
        addTodoItemButton->setObjectName(QString::fromUtf8("addTodoItemButton"));

        verticalLayout->addWidget(addTodoItemButton);

        widget2 = new QWidget(centralwidget);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(892, 32, 381, 471));
        verticalLayout_3 = new QVBoxLayout(widget2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        todoLabel = new QLabel(widget2);
        todoLabel->setObjectName(QString::fromUtf8("todoLabel"));
        todoLabel->setFont(font);

        verticalLayout_3->addWidget(todoLabel);

        listView = new QListView(widget2);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout_3->addWidget(listView);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1307, 20));
        menutest = new QMenu(menubar);
        menutest->setObjectName(QString::fromUtf8("menutest"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menutest->menuAction());
        menutest->addAction(saveAction);
        menutest->addAction(closeAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        saveAction->setText(QCoreApplication::translate("MainWindow", "Zapisz wydarzenia", nullptr));
#if QT_CONFIG(shortcut)
        saveAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        closeAction->setText(QCoreApplication::translate("MainWindow", "Zamknij", nullptr));
        changeCalendarViewMonthly->setText(QCoreApplication::translate("MainWindow", "Miesi\304\231czny", nullptr));
        changeCalendarViewWeekly->setText(QCoreApplication::translate("MainWindow", "Tygodniowy", nullptr));
        yearLabel->setText(QCoreApplication::translate("MainWindow", "Rok", nullptr));
        monthLabel->setText(QCoreApplication::translate("MainWindow", "Miesi\304\205c", nullptr));
        changeDateLabel->setText(QCoreApplication::translate("MainWindow", "Skocz do dnia:", nullptr));
        todoItemInsert->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Nimbus Sans'; font-size:10.5pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Insert item here</p></body></html>", nullptr));
        addTodoItemButton->setText(QCoreApplication::translate("MainWindow", "Dodaj element", nullptr));
        todoLabel->setText(QCoreApplication::translate("MainWindow", "Lista ,,do zrobienia''", nullptr));
        menutest->setTitle(QCoreApplication::translate("MainWindow", "Plik", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
