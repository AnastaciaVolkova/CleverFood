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

    QSqlQuery query;

    query.exec("select * from products where name=\"\"");
    if (query.size() == 0)
        if (!query.exec("insert into products(name) values(\"\")"))
            qDebug() << db.lastError().text();

    query.exec("select * from recipes where name=\"\"");
    if (query.size() == 0)
        if (!query.exec("insert into recipes(name, product) values(\"\",\"\")"))
            qDebug() << db.lastError().text();


    select_recipes_list_ = "select recipes.name, \
            truncate(sum(recipes.weight*(products.protein*4+products.fat*9+products.carbo*4)), 2)  as callories,\
            truncate(sum(recipes.weight), 2) as weight\
            from recipes inner join products\
            on recipes.product = products.name\
            group by recipes.name";

    model_recipes_ = new QSqlQueryModel();
    model_ingredients_ = new QSqlRelationalTableModel();
    model_ingredients_->setEditStrategy(QSqlTableModel::OnFieldChange);

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
    connect(model_ingredients_,&QAbstractItemModel::dataChanged, this, &QTView::onDataChanged);
}

void QTView::showEvent(QShowEvent *) {
    model_recipes_->setQuery(select_recipes_list_);

    QModelIndex index = ui->tbl_recipes->model()->index(0, 0);
    QItemSelectionModel::SelectionFlags flags = QItemSelectionModel::Toggle;
    ui->tbl_recipes->selectionModel()->select(index, flags);
    model_ingredients_->select();
};

void QTView::onSelectionChanged(const QItemSelection &selected){
    int row = recipes_selection_model_->currentIndex().row();
    if (row < 0) {
        row = 0;
        previous_row_ = 0;
    };
    if ((previous_row_ == ui->tbl_recipes->model()->rowCount()-1) && (row != previous_row_)){
        // Check ingredients table
        bool all_ok = true;
        QAbstractItemModel* model = ui->tbl_ingredients->model();
        for (int r = 0; r < model->rowCount(); r++){
            for (int c = 0; c < model->columnCount(); c++){
                QString s = model->data(model->index(r, c)).toString();
                all_ok += (s != "");
            }
        }
    }
    current_recipe_ = ui->tbl_recipes->model()->index(row, 0).data().toString();
    model_ingredients_->setFilter("recipes.name=\'" + current_recipe_ + "\'");
    ui->le_recipe_name->setText(current_recipe_);
    previous_row_ = row;
};

QTView::~QTView()
{
    delete ui;
}

void QTView::on_le_recipe_name_editingFinished()
{
    QSqlQuery query;
    query.prepare("update recipes set name=:new_name where name=:old_name");
    query.bindValue(":new_name", ui->le_recipe_name->text());
    query.bindValue(":old_name", current_recipe_);
    query.exec();
    model_recipes_->setQuery(select_recipes_list_);
    int row = recipes_selection_model_->currentIndex().row();
    if (row < 0) row = 0;
    current_recipe_ = ui->tbl_recipes->model()->index(row, 0).data().toString();
    qDebug() << current_recipe_;
}

void QTView::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles){
    qDebug() << topLeft;
    qDebug() << bottomRight;
    model_recipes_->setQuery(select_recipes_list_);
};

void QTView::on_btn_delete_pressed()
{
    int row = recipes_selection_model_->currentIndex().row();
    QString recipe = ui->tbl_recipes->model()->index(row, 0).data().toString();
    qDebug() << recipe;
    qDebug() << recipes_selection_model_->currentIndex().row();
    QSqlQuery query;
    query.prepare("delete from recipes where name=:name");
    query.bindValue(":name", recipe);
    if (!query.exec())
        qDebug() << db.lastError().text();
    model_recipes_->setQuery(select_recipes_list_);
    recipes_selection_model_->setCurrentIndex(ui->tbl_recipes->model()->index(0,0), QItemSelectionModel::Select);
}
