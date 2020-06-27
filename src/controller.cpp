/*!
 * \file Definition of Controller class
 * \author Anastacia Volkova
*/

#include "controller.hpp"
#include "model.hpp"
#include "mainwindow.h"

using std::unique_ptr;
using std::make_unique;

Controller::Controller()
{
    target_generator_ = make_unique<TargetGeneratorText>(data_file_name_);
}

unique_ptr<Target> Controller::GetTarget() {return target_generator_->GetTarget();};

void Controller::SetView(MainWindow *view){view_ = view;}

void Controller::SetModel(Model *model){model_ = model;}
