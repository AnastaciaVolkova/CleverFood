#include "ingredients_mdl.hpp"

IngredientsModel::IngredientsModel(QObject* parent) : QSqlRelationalTableModel(parent){}

QVariant IngredientsModel::data(const QModelIndex& index, int role){
    QVariant value = QSqlRelationalTableModel::data(index, role);
    return value;
}
