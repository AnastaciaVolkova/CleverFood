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
            std::string calories,
            std::string protein,
            std::string fat,
            std::string carb
            ) = 0;
};

#endif // CONTROLLER_IM_HPP
