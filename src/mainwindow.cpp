#include "mainwindow.h"
#include "ui_mainwindow.h"

using std::make_unique;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    target_generator_ = make_unique<TargetGeneratorText>("data/target.txt");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    target_ = target_generator_->GetTarget();
}
