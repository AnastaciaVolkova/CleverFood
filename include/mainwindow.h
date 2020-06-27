#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "target.hpp"
#include "target_generator.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Target> target_;
    std::unique_ptr<TargetGenerator> target_generator_;
};
#endif // MAINWINDOW_H
