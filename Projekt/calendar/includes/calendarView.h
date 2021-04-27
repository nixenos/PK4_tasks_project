#include "dayModel.h"
#include <QMainWindow>
#include <QStandardItemModel>

namespace calendar {
class calendarView {
  private:
    date today;

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
                               const monthModel &month);
};
} // namespace calendar