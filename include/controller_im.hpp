/*!
  \file Abstract class declaration of controller (interface for model)
*/
#ifndef CONTROLLER_IM_HPP
#define CONTROLLER_IM_HPP

#include "target.hpp"
#include <memory>
#include <string>

class ControllerIm{
public:
    virtual std::unique_ptr<Target> GetTarget() = 0;
    virtual void ShowTarget(
            float calories,
            float protein,
            float fat,
            float carb
            ) = 0;
};

#endif // CONTROLLER_IM_HPP
