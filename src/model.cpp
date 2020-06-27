/*!
  \file Definition of class which implements Model
  \author Anastacia Volkova
*/
#include "model.hpp"

using std::make_unique;

Model::Model(ControllerIm* controller):controller_(controller){
    target_ = controller_->GetTarget();
}
