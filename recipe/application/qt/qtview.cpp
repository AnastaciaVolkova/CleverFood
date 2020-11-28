#include "qtview.h"
#include "ui_qtview.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRelationalDelegate>
#include <QSqlQueryModel>

QTView::QTView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QTView)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("clever_food_sch");
    db.setUserName("root");
    db.setPassword("iago");
    if (!db.open())
        qDebug() << db.lastError().text();

    model_recipes_ = new QSqlTableModel();
    model_ingredients_ = new QSqlRelationalTableModel();
    model_ingredients_->setEditStrategy(QSqlTableModel::OnRowChange);

    ui->tbl_recipes->setModel(model_recipes_);
    ui->tbl_ingredients->setModel(model_ingredients_);

    ui->tbl_ingredients->setModel(model_ingredients_);
    ui->tbl_ingredients->setItemDelegate(new QSqlRelationalDelegate(ui->tbl_ingredients));
    model_ingredients_->setTable("recipes");

    model_ingredients_->setHeaderData(2, Qt::Horizontal, "product");
    model_ingredients_->setHeaderData(3, Qt::Horizontal, "weight");
    model_ingredients_->setRelation(2, QSqlRelation("products", "name", "name"));
    ui->tbl_ingredients->hideColumn(0);
    ui->tbl_ingredients->hideColumn(1);
    model_ingredients_->select();

    recipes_selection_model_ = ui->tbl_recipes->selectionModel();

    connect(recipes_selection_model_, &QItemSelectionModel::selectionChanged, this, &QTView::onSelectionChanged);
}

void QTView::showEvent(QShowEvent *) {
    model_recipes_->setQuery(
                "select recipes.name, \
                truncate(sum(recipes.weight*(products.protein*4+products.fat*9+products.carbo*4)), 2)  as callories,\
                truncate(sum(recipes.weight), 2) as weight\
                from recipes inner join products\
                on recipes.product = products.name\
                group by recipes.name"
                );

    QModelIndex index = ui->tbl_recipes->model()->index(0, 0);
    QItemSelectionModel::SelectionFlags flags = QItemSelectionModel::Toggle;
    ui->tbl_recipes->selectionModel()->select(index, flags);
    model_ingredients_->select();
};

void QTView::onSelectionChanged(const QItemSelection &selected){
    int row = recipes_selection_model_->currentIndex().row();
    if (row < 0) row = 0;
    QString recipe = ui->tbl_recipes->model()->index(row, 0).data().toString();
    model_ingredients_->setFilter("recipes.name=\'" + recipe + "\'");
};

QTView::~QTView()
{
    delete ui;
}
