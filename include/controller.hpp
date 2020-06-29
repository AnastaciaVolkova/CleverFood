/*!
  \file Declaration of class which implements controller
  \author Anastacia Volkova
*/

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include "controller_im.hpp"
#include "controller_iv.hpp"
#include "target_generator.hpp"
#include <string>
class Model;
class MainWindow;

class Controller : public ControllerIm, public ControllerIv{
public:
    Controller();
    void SetModel(Model* model);
    void SetView(MainWindow* view );
    virtual std::unique_ptr<Target> GetTarget() override;
    virtual void ShowTarget(float calories,
                            float protein,
                            float fat,
                            float carb) override;
    virtual void ShowAllElements() override;
private:
    Model* model_;
    MainWindow* view_;
    std::unique_ptr<TargetGenerator> target_generator_;
    const std::string data_file_name_ = "../data/target.txt";
};

#endif // CONTROLLER_HPP_
