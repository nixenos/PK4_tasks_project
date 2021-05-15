#include "todoElement.h"
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <vector>

namespace calendar {
class todoView {
  private:
    std::vector<todoElement> todoItems;

  public:
    void addItem(std::string inputText, QStandardItemModel *todoListModel);

    void deleteItem(QListView *todoListView, QStandardItemModel *todoListModel);

    std::vector<todoElement> getItems();

    void setItems(std::vector<todoElement> newList,
                  QStandardItemModel *todoListModel);
};
} // namespace calendar