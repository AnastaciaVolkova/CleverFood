#ifndef STATE_HPP
#define STATE_HPP

#include <string>

class Context;

class IState{
protected:
    Context* context_;
public:
    IState(Context* context):context_(context){};
    virtual void HandleVEnter() = 0;
    virtual void HandleInvEnter() = 0;
    virtual void HandleLastRowGo() = 0;
    virtual void HandleUDGo() = 0;
    virtual void HandleOtRowCellEnter() = 0;
    virtual operator std::string() const = 0;
};

class NoState:public IState{
public:
    NoState(Context* context);
    virtual void HandleVEnter() override;
    virtual void HandleInvEnter() override;
    virtual void HandleLastRowGo() override;
    virtual void HandleUDGo() override;
    virtual void HandleOtRowCellEnter() override;
    virtual operator std::string() const override;
};

class AddOK: public IState{
public:
    AddOK(Context* context);
    virtual void HandleVEnter() override;
    virtual void HandleInvEnter() override;
    virtual void HandleLastRowGo() override;
    virtual void HandleUDGo() override;
    virtual void HandleOtRowCellEnter() override;
    virtual operator std::string() const override;
};

class AddNOK: public IState{
public:
    AddNOK(Context* context);
    virtual void HandleVEnter() override;
    virtual void HandleInvEnter() override;
    virtual void HandleLastRowGo() override;
    virtual void HandleUDGo() override;
    virtual void HandleOtRowCellEnter() override;
    virtual operator std::string() const override;
};

class AddReady: public IState{
public:
    AddReady(Context* context);
    virtual void HandleVEnter() override;
    virtual void HandleInvEnter() override;
    virtual void HandleLastRowGo() override;
    virtual void HandleUDGo() override;
    virtual void HandleOtRowCellEnter() override;
    virtual operator std::string() const override;
};

class UpdateOK: public IState{
public:
    UpdateOK(Context* context);
    virtual void HandleVEnter() override;
    virtual void HandleInvEnter() override;
    virtual void HandleLastRowGo() override;
    virtual void HandleUDGo() override;
    virtual void HandleOtRowCellEnter() override;
    virtual operator std::string() const override;
};

class UpdateNOK: public IState{
public:
    UpdateNOK(Context* context);
    virtual void HandleVEnter() override;
    virtual void HandleInvEnter() override;
    virtual void HandleLastRowGo() override;
    virtual void HandleUDGo() override;
    virtual void HandleOtRowCellEnter() override;
    virtual operator std::string() const override;
};

#endif // STATE_HPP
