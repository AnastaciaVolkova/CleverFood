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
                target_->GetKCal(),
                target_->GetProteinGr(),
                target_->GetFatGr(),
                target_->GetCarbGr()
                );
}
