#include "ingredients_mdl.hpp"
#include <QDebug>

IngredientsModel::IngredientsModel(QObject* parent) : QSqlRelationalTableModel(parent){}

QVariant IngredientsModel::data(const QModelIndex& index, int role) const{
    QVariant value = QSqlRelationalTableModel::data(index, role);
    if (value.isValid() && role == Qt::DisplayRole){
        if (index.column() == 1)
            if (!IsDigitF(value.toString().toStdString()))
                qDebug() << "Error";
    }
    return value;
}

bool IngredientsModel::IsDigitF(std::string s) const {
    size_t n = count_if(s.begin(), s.end(), [](char a) {return (a == ',') || (a == '.'); });
    if ((n >= 2) || (s==""))
        return false;
    auto it = s.begin();
    while ((it != s.end()) && ((*it == '.') | (*it == ',') | (isdigit(*it)))) { it++; };
    return it == s.end();
};
