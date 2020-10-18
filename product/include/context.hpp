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
    std::unique_ptr<IState> cur_state_;
    std::unique_ptr<NoState> not_state_;
    std::unique_ptr<AddOK> add_ok_state_;
    std::unique_ptr<AddNOK> add_nok_state_;
    std::unique_ptr<AddReady> add_ready_;
public:
    Context();

    bool AllOK();

    bool Ready();

    void SetState(std::unique_ptr<IState> new_state);

    std::unique_ptr<IState> GetNoState();

    std::unique_ptr<IState> GetAddOKState();

    std::unique_ptr<IState> GetAddReady();

    std::unique_ptr<IState> GetAddNOKState();

    void HandleVEnter();

    void HandleInvEnter();

    void HandleLastRowGo();

    void HandleOtRowGo();

    void HandleOtRowCellEnter();
};
#endif
