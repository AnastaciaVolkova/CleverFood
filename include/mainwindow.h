#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <string>
#include "controller_iv.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ControllerIv* controller, QWidget *parent = nullptr);
    ~MainWindow();
    void show();
    void ShowTarget(std::string calories, std::string protein, std::string fat, std::string carb);
private slots:
    void on_pushButton_3_clicked();
    void on_te_kc_t_editingFinished();

    void on_te_p_t_editingFinished();

    void on_te_f_t_editingFinished();

    void on_te_c_t_editingFinished();

private:
    ControllerIv* controller_;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
