/**
 * @file weeklyCalendarView.h
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
 * @brief Klasa operująca widokiem tygodniowym.
 *
 */
class weeklyCalendarView {
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
    weeklyCalendarView();

    /**
     * @brief Ustawia dzisiejszą datę.
     *
     */
    void setTodayDate();

    /**
     * @brief Pobiera dzisiejszą datę.
     *
     * @return date dzisiejsza data
     */
    date getTodayDate() const noexcept;

    /**
     * @brief Oblicza obecny tydzień oraz ustawia wartości w widoku.
     *
     * @param dayModelInterface model widoku
     * @param month obecny miesiąc
     * @param year obecny rok
     * @param weekNum numer obecnego tygodnia
     * @param monthEventsInterface model widoku
     */
    void calculateCurrentWeek(QStandardItemModel *dayModelInterface,
                              const monthModel &month, const int &year,
                              const int &weekNum,
                              QStandardItemModel *monthEventsInterface);

    /**
     * @brief Zwraca nazwę miesiąca dla obiektu monthModel.
     *
     * @param month miesiąc
     * @return std::string nazwa miesiąca
     */
    std::string getMonthName(const monthModel &month);

    /**
     * @brief Pobiera wydarzenia dla danego dnia.
     *
     * @param monthEventsInterface
     * @param day dzień dla którego mają być zwrócone wydarzenia
     */
    void getEventsForDay(QStandardItemModel *monthEventsInterface,
                         const int &day);

    /**
     * @brief Zwraca element Qt, który ma zostać wyświetlony
     *
     * @param newEvent
     * @return QStandardItem*
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
     * @brief Pobiera wydarzenia.
     *
     * @return std::vector<event *> lista wydarzeń
     */
    std::vector<event *> getEvents() const noexcept;

    /**
     * @brief Ustawia wydarzenia w modelu widoku.
     *
     * @param newEvents wydarzenia do ustawienia
     */
    void setEvents(std::vector<event *> newEvents);

    /**
     * @brief Usuwa wydarzenie.
     *
     * @param exportedEventData identyfikator danych do usunięcia
     */
    void deleteEvent(std::string exportedEventData);

    /**
     * @brief Pobiera aktualny numer tygodnia.
     *
     * @param tempDate data, dla której ma być podany numer tygodnia
     * @return int numer tygodnia
     */
    int getCurrentWeekNumber(const date &tempDate) const noexcept;
};
} // namespace calendar