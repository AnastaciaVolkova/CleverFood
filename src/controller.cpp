/*!
 * \file Definition of Controller class
 * \author Anastacia Volkova
*/

#include "controller.hpp"
#include "model.hpp"
#include "mainwindow.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <QDebug>

using std::unique_ptr;
using std::make_unique;
using std::string;
using std::stringstream;
using std::setprecision;
using std::fixed;
using std::invalid_argument;

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

void Controller::ShowProducts(){

}

void Controller::SetView(MainWindow *view){view_ = view;}

void Controller::SetModel(Model *model){model_ = model;}

void Controller::ShowAllElements(){
    model_->SignalToShow();
}

bool Controller::CheckTargetKC(QString kc ){
    return CheckDigitInputs(kc);
};

bool Controller::CheckDigitInputs(QString in_val){
    string in_val_s = in_val.toStdString();
    string::iterator f_it;
    while ((f_it = find(in_val_s.begin(), in_val_s.end(), ' ')) == in_val_s.begin())
        in_val_s.erase(f_it);

    string::reverse_iterator f_rit;
    while ((f_rit = find(in_val_s.rbegin(), in_val_s.rend(), ' ')) == in_val_s.rbegin())
        in_val_s.erase(next(f_rit).base());

    auto it = find_if(in_val_s.begin(), in_val_s.end(),
                 [](auto v){
        return ((v < '0')||(v > '9'))&&(v!=',')&&(v != '.');
    });
    // ((v >= '0')&&(v <='9')) || (v == ',') || (v == '.')
    return it == in_val_s.end();
}

/*
void Controller::SetTargetKC(QString kc){
    string kcs = kc.toStdString();
    try{
        float kc = stof(kcs);
        model_->
    } catch (invalid_argument exc){

    }
}
*/
