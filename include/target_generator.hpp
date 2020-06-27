/*!
\file
\brief Declaration of class which keeps information on target generator
\author Anastacia Volkova
*/

#ifndef TARGET_GENERATOR_HPP_
#define TARGET_GENERATOR_HPP_
#include <memory>
#include <string>
#include <vector>
#include "target.hpp"

class TargetGenerator{
public:
  TargetGenerator(std::string name):name_(name){};
  virtual std::unique_ptr<Target> GetTarget() = 0;
protected:
  std::string name_;
};

class TargetGeneratorText : public TargetGenerator{
public:
  TargetGeneratorText(std::string name);
  virtual std::unique_ptr<Target> GetTarget() override;
private:
  std::string record_;
};

#endif
