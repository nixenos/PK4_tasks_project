#include "../includes/todoView.h"
#include <QModelIndex>
#include <iostream>

namespace calendar {
void todoView::addItem(std::string inputText,
                       QStandardItemModel *todoListModel) {
    int position = this->todoItems.size();
    if (!inputText.empty()) {
        todoElement tempElement(position, inputText);
        this->todoItems.push_back(tempElement);
        QStandardItem *tempQItem =
            new QStandardItem(QString(inputText.c_str()));
        todoListModel->appendRow(tempQItem);
    }
}

void todoView::deleteItem(QListView *todoListView,
                          QStandardItemModel *todoListModel) {
    for (int i = 0; i < this->todoItems.size(); i++) {
        std::cout << this->todoItems[i].getDataRecord() << std::endl;
    }
    for (QModelIndex index :
         todoListView->selectionModel()->selectedIndexes()) {
        QStandardItem *tempItem = todoListModel->itemFromIndex(index);
        todoListModel->removeRow(index.row());
        int position = index.row();
        for (int i = position; i < this->todoItems.size() - 1; i++) {
            this->todoItems[i].setPosition(i + 1);
        }
        this->todoItems.pop_back();
        // delete tempItem;
    }
}
} // namespace calendar