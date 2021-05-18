/**
 * @file calendarView.h
 * @author Wojciech Janota
 * @brief
 * @version 0.1
 * @date 2021-05-18
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "dayModel.h"
#include "event.h"
#include "eventBirthdayModel.h"
#include "eventHolidayModel.h"
#include "eventReminderModel.h"
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <vector>

namespace calendar {
/**
 * @brief klasa opisująca model widoku miesięcznego.
 *
 */
class calendarView {
  private:
    date today;
    std::vector<day> days;
    std::vector<std::string> monthNames;
    std::vector<event *> events;

  public:
    /**
     * @brief Konstruktor bezargumentowy.
     *
     */
    calendarView();

    /**
     * @brief Ustawia dzisiejszą datę
     *
     */
    void setTodayDate();

    /**
     * @brief Pobiera dzisiejszą datę
     *
     * @return date dzisiejsza data
     */
    date getTodayDate() const noexcept;

    /**
     * @brief Ustawia i oblicza dni w obecnym miesiącu.
     *
     * @param dayModelInterface model widoku dni
     * @param month obecny miesiąc
     * @param year obecny rok
     * @param monthEventsInterface model widoku wydarzeń
     */
    void calculateCurrentMonth(QStandardItemModel *dayModelInterface,
                               const monthModel &month, const int &year,
                               QStandardItemModel *monthEventsInterface);

    /**
     * @brief Pobiera nazwę miesiąca
     *
     * @param month dany miesiąć
     * @return std::string nazwa miesiąca
     */
    std::string getMonthName(const monthModel &month);

    /**
     * @brief Pobiera wydarzenia dla danego dnia.
     *
     * @param monthEventsInterface model widoku wydarzeń
     * @param day dany dzień
     */
    void getEventsForDay(QStandardItemModel *monthEventsInterface,
                         const int &day);

    /**
     * @brief Zwraca opis wydarzenia
     *
     * @param newEvent wydarzenie do opisania
     * @return QStandardItem* obiekt Qt z opisem wydarzenia
     */
    QStandardItem *displayReminderEvent(event *newEvent);

    /**
     * @brief Dodaje wydarzenie z okna dialogowego.
     *
     * @param calendarMonthlyView widok tabelaryczny
     * @param newEvName nazwa wydarzenia
     * @param newEvDescription opis wydarzenia
     * @param newEvLocation lokalizacja wydarzenia
     * @param newEvType typ wydarzenia
     * @param newEvFirstname imię osoby, która ma urodziny
     * @param newEvLastname nazwisko osoby, która ma urodziny
     * @param newEvDate data wydarzenia
     * @param newBirthdate data narodzin osoby
     * @param beginDate data rozpoczęcia wakacji
     * @param endDate data zakończenia wakacji
     * @param newEvRepeat sposób powtarzania wydarzenia
     * @param eventClass rodzaj wydarzenia
     */
    void addEventFromDialog(
        QTableView *calendarMonthlyView, const std::string &newEvName,
        const std::string &newEvDescription, const std::string &newEvLocation,
        const std::string &newEvType, const std::string &newEvFirstname,
        const std::string &newEvLastname, const date &newEvDate,
        const date &newBirthdate, const date &beginDate, const date &endDate,
        const repeatCycle &newEvRepeat, const std::string &eventClass);

    /**
     * @brief Pobiera listę wydarzeń.
     *
     * @return std::vector<event *> lista wydarzeń
     */
    std::vector<event *> getEvents() const noexcept;

    /**
     * @brief Ustawia listę wydarzeń
     *
     * @param newEvents lista wydarzeń
     */
    void setEvents(std::vector<event *> newEvents);

    /**
     * @brief Usuwa wydarzenie o określonym opisie.
     *
     * @param exportedEventData opis wydarzenia
     */
    void deleteEvent(std::string exportedEventData);
};
} // namespace calendar