#include "dayModel.h"
#include <QMainWindow>
#include <QStandardItemModel>

namespace calendar {
class calendarView {
  private:
    date today;
    std::vector<day> days;

  public:
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
                               const monthModel &month, const int &year);
};
} // namespace calendar