/**
 * @file todoView.h
 * @author Wojciech Janota
 * @brief
 * @version 0.1
 * @date 2021-05-18
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "todoElement.h"
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <vector>

namespace calendar {
/**
 * @brief Klasa opisująca widok elementów todo
 *
 */
class todoView {
  private:
    std::vector<todoElement> todoItems;

  public:
    /**
     * @brief Dodaje element.
     *
     * @param inputText tekst elementu
     * @param todoListModel model widoku listy elementów
     */
    void addItem(std::string inputText, QStandardItemModel *todoListModel);

    /**
     * @brief Usuwa element.
     *
     * @param todoListView widok listy elementów
     * @param todoListModel model widoku listy elementów
     */
    void deleteItem(QListView *todoListView, QStandardItemModel *todoListModel);

    /**
     * @brief Pobiera elementy todo.
     *
     * @return std::vector<todoElement> elementy todo
     */
    std::vector<todoElement> getItems();

    /**
     * @brief Ustawia elementy todo i wyświetla je
     *
     * @param newList nowa lista elementów todo
     * @param todoListModel model widoku listy elementów
     */
    void setItems(std::vector<todoElement> newList,
                  QStandardItemModel *todoListModel);
};
} // namespace calendar