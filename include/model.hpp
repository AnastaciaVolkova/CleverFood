/*!
  \file Declaration of class which implements model
  \author Anastacia Volkova
*/
#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "controller_im.hpp"
#include "target.hpp"

#include <memory>
#include <string>

/*!
 * \brief The Model class
 */
class Model{
public:
    //! Class contains
    Model(ControllerIm* controller);
private:    
    ControllerIm* controller_;
    std::unique_ptr<Target> target_;
};

#endif // MODEL_HPP_
