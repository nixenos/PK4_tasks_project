#include "dayModel.h"
#include "event.h"
#include "eventBirthdayModel.h"
#include "eventReminderModel.h"
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <vector>

namespace calendar {
class calendarView {
  private:
    date today;
    std::vector<day> days;
    std::vector<std::string> monthNames;

  public:
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

    void calculateCurrentMonth(QStandardItemModel *dayModelInterface,
                               const monthModel &month, const int &year,
                               QStandardItemModel *monthEventsInterface);

    std::string getMonthName(const monthModel &month);

    void getEventsForDay(QStandardItemModel *monthEventsInterface,
                         const int &day);

    QStandardItem *displayReminderEvent(event *newEvent);

    void addEventFromDialog(
        QTableView *calendarMonthlyView, const std::string &newEvName,
        const std::string &newEvDescription, const std::string &newEvLocation,
        const std::string &newEvType, const std::string &newEvFirstname,
        const std::string &newEvLastname, const date &newEvDate,
        const date &newBirthdate, const date &beginDate, const date &endDate,
        const repeatCycle &newEvRepeat, const std::string &eventClass);

    std::vector<day> getDays() const noexcept;

    void setDays(std::vector<day> newDays);
};
} // namespace calendar