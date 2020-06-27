/*!
  \file Abstract class declaration of controller (interface for model)
*/
#ifndef CONTROLLER_IM_HPP
#define CONTROLLER_IM_HPP

#include "target.hpp"
#include <memory>

class ControllerIm{
public:
    virtual std::unique_ptr<Target> GetTarget() = 0;
};

#endif // CONTROLLER_IM_HPP
