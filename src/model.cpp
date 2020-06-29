/*!
  \file Definition of class which implements Model
  \author Anastacia Volkova
*/
#include "model.hpp"

using std::make_unique;
using std::to_string;

Model::Model(ControllerIm* controller):controller_(controller){
    target_ = controller_->GetTarget();
}

void Model::SignalToShow(){
    controller_->ShowTarget(
                to_string(target_->GetKCal()),
                to_string(target_->GetProteinGr()),
                to_string(target_->GetFatGr()),
                to_string(target_->GetCarbGr())
                );
}
