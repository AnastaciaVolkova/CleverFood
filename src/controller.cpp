/*!
 * \file Definition of Controller class
 * \author Anastacia Volkova
*/

#include "controller.hpp"
#include "model.hpp"
#include "mainwindow.h"
#include <sstream>
#include <iomanip>

using std::unique_ptr;
using std::make_unique;
using std::string;
using std::stringstream;
using std::setprecision;
using std::fixed;

Controller::Controller()
{
    target_generator_ = make_unique<TargetGeneratorText>(data_file_name_);
}

unique_ptr<Target> Controller::GetTarget() {return target_generator_->GetTarget();};
void Controller::ShowTarget(
        float calories,
        float protein,
        float fat,
        float carb
        ){
    stringstream iss_cal, iss_p, iss_f, iss_c;
    iss_cal << fixed << setprecision(2) << calories;
    iss_p << fixed << setprecision(2) << protein;
    iss_f << fixed << setprecision(2) << fat;
    iss_c << fixed << setprecision(2) << carb;
    view_->ShowTarget(
                iss_cal.str(),
                iss_p.str(),
                iss_f.str(),
                iss_c.str());
};

void Controller::SetView(MainWindow *view){view_ = view;}

void Controller::SetModel(Model *model){model_ = model;}

void Controller::ShowAllElements(){
    model_->SignalToShow();
}
