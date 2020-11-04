#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include <map>
#include <string>
#include <memory>
#include "state.hpp"

class Context{
public:
    enum class Fields {kName = 0, kProtein, kFat, kCarb} ;
    std::map<Fields, std::string> fields_;
private:
    std::shared_ptr<IState> cur_state_;
    std::shared_ptr<NoState> not_state_;
    std::shared_ptr<AddOK> add_ok_state_;
    std::shared_ptr<AddNOK> add_nok_state_;
    std::shared_ptr<AddReady> add_ready_;
    std::shared_ptr<UpdateOK> update_ok_state_;
    std::shared_ptr<UpdateNOK> update_nok_state_;
public:
    Context();

    bool AllOK();

    bool Ready();

    bool ReadyToUpdate();

    void SetState(std::shared_ptr<IState> new_state);

    std::shared_ptr<IState> GetNoState();

    std::shared_ptr<IState> GetAddOKState();

    std::shared_ptr<IState> GetAddReady();

    std::shared_ptr<IState> GetAddNOKState();

    std::shared_ptr<IState> GetUpdateOKState();

    std::shared_ptr<IState> GetUpdateNOKState();

    void HandleVEnter();

    void HandleInvEnter();

    void HandleAGo();

    void HandleUDGo();

    void HandleOtRowCellEnter();

    void HandleAddPressed();

    std::string PrintCurrentState();
};
#endif
