#include "context.hpp"
#include <algorithm>

Context::Context(){
    not_state_ = std::make_shared<NoState>(this);
    add_ok_state_ = std::make_shared<AddOK>(this);
    add_nok_state_ = std::make_shared<AddNOK>(this);
    add_ready_ = std::make_shared<AddReady>(this);
    update_nok_state_ = std::make_shared<UpdateNOK>(this);
    update_ok_state_ = std::make_shared<UpdateOK>(this);
    cur_state_ = not_state_;
};

bool Context::AllOK(){
    return std::all_of(fields_.begin(), fields_.end(), [](auto a){return a.second != "";});
};

bool Context::Ready(){
  return ((fields_.size()==4) && std::all_of(fields_.begin(), fields_.end(), [](auto a){return a.second != "";}));
};

bool Context::ReadyToUpdate(){
    std::shared_ptr<UpdateOK> s = std::dynamic_pointer_cast<UpdateOK>(cur_state_);
    return (s != nullptr);
};

void Context::SetState(std::shared_ptr<IState> new_state){cur_state_ = new_state; };

std::shared_ptr<IState> Context::GetNoState(){return not_state_; };

std::shared_ptr<IState> Context::GetAddOKState(){return add_ok_state_;};

std::shared_ptr<IState> Context::GetAddReady(){return add_ready_;};

std::shared_ptr<IState> Context::GetAddNOKState(){return add_nok_state_;};

std::shared_ptr<IState> Context::GetUpdateOKState(){return update_ok_state_;};

std::shared_ptr<IState> Context::GetUpdateNOKState(){return update_nok_state_;};

void Context::HandleVEnter(){cur_state_->HandleVEnter();};

void Context::HandleInvEnter(){cur_state_->HandleInvEnter();};

void Context::HandleAGo(){cur_state_->HandleLastRowGo();};

void Context::HandleUDGo(){cur_state_->HandleUDGo();};

void Context::HandleOtRowCellEnter(){cur_state_->HandleOtRowCellEnter();};

void Context:: HandleAddPressed(){ SetState(not_state_);};

std::string Context::PrintCurrentState(){
    IState* state = cur_state_.get();
    return static_cast<std::string>(*state);
};
