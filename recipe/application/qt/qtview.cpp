#include "qtview.h"
#include "ui_qtview.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRelationalDelegate>
#include <QSqlQueryModel>
#include <algorithm>

QTView::QTView(const QApplication* app, QWidget *parent)
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
    connect(ui->tbl_ingredients->selectionModel(), &QItemSelectionModel::selectionChanged, this, &QTView::onSelectionIngredientsChanged);
    connect(model_ingredients_,&QAbstractItemModel::dataChanged, this, &QTView::onDataChanged);
    connect(app, &QApplication::focusChanged, this, &QTView::onFocusChanged);
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

    qDebug() << "Recipes" << ui->tbl_recipes->selectionModel()->currentIndex().row() << ", "
             << ui->tbl_recipes->selectionModel()->currentIndex().column();
    qDebug() << "Ingredients" << ui->tbl_ingredients->selectionModel()->currentIndex().row() << ", "
             << ui->tbl_ingredients->selectionModel()->currentIndex().column();
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
    model_recipes_->setQuery(select_recipes_list_);
    qDebug() << "onDataChanged";
    qDebug() << topLeft.row() << " " << topLeft.column();
    qDebug() << bottomRight.row() << " " << bottomRight.column();
};

void QTView::on_btn_delete_pressed()
{
    // Delete ingredient
    if ((ui->tbl_ingredients->selectionModel()->currentIndex().row() != -1) &&
            (ui->tbl_ingredients->selectionModel()->currentIndex().row() != -1)){
        QString product = ui->tbl_ingredients->model()->index(ui->tbl_ingredients->selectionModel()->currentIndex().row(), 2).data().toString();
        QString recipe = ui->tbl_recipes->model()->index(recipes_selection_model_->currentIndex().row(), 0).data().toString();
        qDebug() << product;
        qDebug() << recipe;
        QSqlQuery query;
        query.prepare("delete from recipes where product=:product and name=:name");
        query.bindValue(":product", product);
        query.bindValue(":name", recipe);
        if (!query.exec())
            qDebug() << db.lastError().text();
        model_ingredients_->select();
        ui->tbl_ingredients->selectionModel()->setCurrentIndex(ui->tbl_ingredients->model()->index(0,2), QItemSelectionModel::Select);
        query.prepare("select * from recipes where name=:name");
        query.bindValue(":name", recipe);
        query.exec();
        if (query.size() == 0){
            model_recipes_->setQuery(select_recipes_list_);
            ui->tbl_recipes->selectionModel()->setCurrentIndex(ui->tbl_recipes->model()->index(
                                                                   std::max(0, previous_row_-1),
                                                                    0),
                                                               QItemSelectionModel::Select);
        }

    } else { // Delete recipe
        QString recipe = ui->tbl_recipes->model()->index(recipes_selection_model_->currentIndex().row(), 0).data().toString();
        qDebug() << recipe;
        QSqlQuery query;
        query.prepare("delete from recipes where name=:name");
        query.bindValue(":name", recipe);
        if (!query.exec())
            qDebug() << db.lastError().text();
        model_recipes_->setQuery(select_recipes_list_);
        recipes_selection_model_->setCurrentIndex(ui->tbl_recipes->model()->index(std::max(0, previous_row_-1), 0), QItemSelectionModel::Select);
    }
}

void QTView::onSelectionIngredientsChanged(const QItemSelection &selected){
    qDebug() << "Recipes" << ui->tbl_recipes->selectionModel()->currentIndex().row() << ", "
             << ui->tbl_recipes->selectionModel()->currentIndex().column();
    qDebug() << "Ingredients" << ui->tbl_ingredients->selectionModel()->currentIndex().row() << ", "
             << ui->tbl_ingredients->selectionModel()->currentIndex().column();
};

void QTView::onFocusChanged ( QWidget * old, QWidget * now ){
    if (now == ui->le_new_recipe_name){
        //Insert empty product to products
        QSqlQuery query;
        query.exec("select * from products where name=\"\"");
        if (query.size() == 0)
            if (!query.exec("insert into products(name) values(\"\")"))
                qDebug() << db.lastError().text();
        //Create recipe with empty ingredient
        AddEmptyRowToIngredients();
        model_ingredients_->setFilter("recipes.name=\'\'");
    } else {
        // Delete empty product from produts
        QSqlQuery query;
        query.exec("select * from products where name=\"\"");
        if (query.size() != 0)
            if (!query.exec("delete from products where name=\"\""))
                qDebug() << db.lastError().text();
    }
};

void QTView::on_le_new_recipe_name_editingFinished()
{
    std::string query_str = "update recipes set name=\'" + ui->le_new_recipe_name->text().toStdString() + "\' where name=\'\'";
    qDebug() << QString(query_str.c_str());
    QSqlQuery query;
    if (!query.exec(QString(query_str.c_str())))
        qDebug() << db.lastError().text();
}

void QTView::AddEmptyRowToIngredients(std::string name){
    QSqlQuery query;
    // Create empty ingredients
    query.exec("select * from recipes where name=\"\"");
    if (query.size() == 0){
        QString query_pat = QString("insert into recipes(name, product) values(\'") + QString(name.c_str()) + QString("\', \'\')");
        qDebug() << query_pat;
        if (!query.exec(query_pat))
            qDebug() << db.lastError().text();
    }
};
