#include "context.hpp"
#include <algorithm>

Context::Context(){
    not_state_ = std::make_unique<NoState>(this);
    add_ok_state_ = std::make_unique<AddOK>(this);
    add_nok_state_ = std::make_unique<AddNOK>(this);
    add_ready_ = std::make_unique<AddReady>(this);
    cur_state_ = std::move(not_state_);
};

bool Context::AllOK(){
    return std::all_of(fields_.begin(), fields_.end(), [](auto a){return a.second != "";});
};

bool Context::Ready(){
  return ((fields_.size()==4) && std::all_of(fields_.begin(), fields_.end(), [](auto a){return a.second != "";}));
};

void Context::SetState(std::unique_ptr<IState> new_state){
    IState* p = cur_state_.get();
    std::string s = static_cast<std::string>(*p);
    cur_state_ = std::move(new_state);
    p = cur_state_.get();
    s = static_cast<std::string>(*p);
};

std::unique_ptr<IState> Context::GetNoState(){return std::move(not_state_);};

std::unique_ptr<IState> Context::GetAddOKState(){return std::move(add_ok_state_);};

std::unique_ptr<IState> Context::GetAddReady(){return std::move(add_ready_);};

std::unique_ptr<IState> Context::GetAddNOKState(){return std::move(add_nok_state_);};

void Context::HandleVEnter(){
    cur_state_->HandleVEnter();
};

void Context::HandleInvEnter(){cur_state_->HandleInvEnter();};

void Context::HandleLastRowGo(){cur_state_->HandleLastRowGo();};

void Context::HandleOtRowGo(){cur_state_->HandleOtRowGo();};

void Context::HandleOtRowCellEnter(){cur_state_->HandleOtRowCellEnter();};
