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

void NoState::HandleUDGo(){
    context_->SetState(context_->GetUpdateOKState());
};

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

void AddOK::HandleUDGo(){
    context_->SetState(context_->GetUpdateOKState());
};

void AddOK::HandleOtRowCellEnter(){
    context_->SetState(context_->GetNoState());
};

AddOK::operator std::string() const {return "AddOK";};

//!AddNOK
AddNOK::AddNOK(Context* context):IState(context){};

void AddNOK::HandleVEnter(){
    if (!context_->AnyError())
        context_->SetState(context_->GetAddOKState());
};

void AddNOK::HandleInvEnter(){
    context_->SetState(context_->GetAddNOKState());
};

void AddNOK::HandleLastRowGo(){};

void AddNOK::HandleUDGo(){
    context_->SetState(context_->GetUpdateOKState());
};

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

void AddReady::HandleUDGo(){
    context_->SetState(context_->GetUpdateOKState());
};

void AddReady::HandleOtRowCellEnter(){};

AddReady::operator std::string() const {return "AddReady";};

//!Update
//! UpdateOK
UpdateOK::UpdateOK(Context* context):IState(context){};

void UpdateOK::HandleVEnter(){};

void UpdateOK::HandleInvEnter(){
    context_->SetState(context_->GetUpdateNOKState());
};

void UpdateOK::HandleLastRowGo(){
    context_->SetState(context_->GetAddOKState());
};

void UpdateOK::HandleUDGo(){};

void UpdateOK::HandleOtRowCellEnter(){
    context_->SetState(context_->GetNoState());
};

UpdateOK::operator std::string() const {return "UpdateOK";};

//!UpdateNOK
UpdateNOK::UpdateNOK(Context* context):IState(context){};

void UpdateNOK::HandleVEnter(){
    if (!context_->AnyError())
        context_->SetState(context_->GetUpdateOKState());
};

void UpdateNOK::HandleInvEnter(){
    context_->SetState(context_->GetUpdateNOKState());
};

void UpdateNOK::HandleLastRowGo(){};

void UpdateNOK::HandleUDGo(){};

void UpdateNOK::HandleOtRowCellEnter(){
    context_->SetState(context_->GetNoState());
};

UpdateNOK::operator std::string() const {return "UpdateNOK";};
