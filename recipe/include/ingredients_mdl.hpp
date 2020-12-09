#ifndef INGREDIENTS_MDL_H
#define INGREDIENTS_MDL_H

#include <QSqlRelationalTableModel>

class IngredientsModel : public QSqlRelationalTableModel {
    Q_OBJECT
public:
    IngredientsModel(QObject *parent=nullptr);
    QVariant data(const QModelIndex& item, int role) const override;
private:
    bool IsDigitF(std::string s) const;
};

#endif
