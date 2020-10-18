#include "state.hpp"
#include "context.hpp"
#include "product_ctrl.hpp"

//! No State
NoState::NoState(Context* context):IState(context){};

void NoState::HandleVEnter(){};

void NoState::HandleInvEnter(){};

void NoState::HandleLastRowGo(){
    context_->SetState(context_->GetAddOKState());
};

void NoState::HandleOtRowGo(){};

void NoState::HandleOtRowCellEnter(){};

NoState::operator std::string() const {return "NoState";};

//! AddOK
AddOK::AddOK(Context* context):IState(context){};

void AddOK::HandleVEnter(){
    if (context_->Ready()) context_->SetState(context_->GetAddReady());
};

void AddOK::HandleInvEnter(){
    context_->SetState(context_->GetAddNOKState());
};

void AddOK::HandleLastRowGo(){};

void AddOK::HandleOtRowGo(){};

void AddOK::HandleOtRowCellEnter(){
    context_->SetState(context_->GetNoState());
};

AddOK::operator std::string() const {return "AddOK";};

//!AddNOK
AddNOK::AddNOK(Context* context):IState(context){};

void AddNOK::HandleVEnter(){
    if (context_->AllOK())
        context_->SetState(context_->GetAddOKState());
};

void AddNOK::HandleInvEnter(){
    context_->SetState(context_->GetAddNOKState());
};

void AddNOK::HandleLastRowGo(){};

void AddNOK::HandleOtRowGo(){};

void AddNOK::HandleOtRowCellEnter(){
    context_->SetState(context_->GetNoState());
};

AddNOK::operator std::string() const {return "AddNOK";};

//!AddReady
AddReady::AddReady(Context* context):IState(context){};

void AddReady::HandleVEnter(){};

void AddReady::HandleInvEnter(){
    context_->SetState(context_->GetAddNOKState());
};

void AddReady::HandleLastRowGo(){};

void AddReady::HandleOtRowGo(){};

void AddReady::HandleOtRowCellEnter(){};

AddReady::operator std::string() const {return "AddReady";};

