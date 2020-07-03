#ifndef CONTROLLER_IV_HPP_
#define CONTROLLER_IV_HPP_

#include <QString>

class ControllerIv{
public:
    virtual void ShowAllElements() = 0;
    //! Check if input target kilocalories value is valid
    /*!
     * \param [in] kc target kilocalories to set
     */
    virtual bool CheckTargetKC(QString kc ) = 0;
};

#endif // CONTROLLER_IV_HPP_
