#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qstring.h"

using std::make_unique;
using std::string;

MainWindow::MainWindow(ControllerIv* controller,
                       QWidget *parent)
    : QMainWindow(parent)
    , controller_(controller)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show(){
    QMainWindow::show();
    controller_->ShowAllElements();
}

void MainWindow::on_pushButton_3_clicked()
{
}

void MainWindow::ShowTarget(string calories, string protein, string fat, string carb){
    ui->te_kc->setText(QString::fromStdString(calories));
    ui->te_p->setText(QString::fromStdString(protein));
    ui->te_f->setText(QString::fromStdString(fat));
    ui->te_c->setText(QString::fromStdString(carb));
};
