/*!
 * \file Definition of Controller class
 * \author Anastacia Volkova
*/

#include "controller.hpp"
#include "model.hpp"
#include "mainwindow.h"

using std::unique_ptr;
using std::make_unique;
using std::string;

Controller::Controller()
{
    target_generator_ = make_unique<TargetGeneratorText>(data_file_name_);
}

unique_ptr<Target> Controller::GetTarget() {return target_generator_->GetTarget();};
void Controller::ShowTarget(
        string calories,
        string protein,
        string fat,
        string carb
        ){
    view_->ShowTarget(calories, protein, fat, carb);
};

void Controller::SetView(MainWindow *view){view_ = view;}

void Controller::SetModel(Model *model){model_ = model;}

void Controller::ShowAllElements(){
    model_->SignalToShow();
}
