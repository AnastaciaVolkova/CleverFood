#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qstring.h"
#include <QDebug>
#include <QPalette>

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

void MainWindow::on_te_kc_t_editingFinished()
{
    QPalette p;
    if (controller_->CheckTargetKC(ui->te_kc_t->text())){
        p.setColor(QPalette::Text, Qt::black);
    } else {
        p.setColor(QPalette::Text, Qt::red);
    }
    ui->te_kc_t->setPalette(p);
}

void MainWindow::on_te_p_t_editingFinished()
{
    QPalette p;
    if (controller_->CheckTargetKC(ui->te_p_t->text())){
        p.setColor(QPalette::Text, Qt::black);
    } else {
        p.setColor(QPalette::Text, Qt::red);
    }
    ui->te_p_t->setPalette(p);
}

void MainWindow::on_te_f_t_editingFinished()
{
    QPalette p;
    if (controller_->CheckTargetKC(ui->te_f_t->text())){
        p.setColor(QPalette::Text, Qt::black);
    } else {
        p.setColor(QPalette::Text, Qt::red);
    }
    ui->te_f_t->setPalette(p);
}

void MainWindow::on_te_c_t_editingFinished()
{
    QPalette p;
    if (controller_->CheckTargetKC(ui->te_c_t->text())){
        p.setColor(QPalette::Text, Qt::black);
    } else {
        p.setColor(QPalette::Text, Qt::red);
    }
    ui->te_c_t->setPalette(p);
}
