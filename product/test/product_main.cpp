#include <iostream>
#include "product_ctrl_iv.hpp"
#include "product_ctrl.hpp"
#include "product_mdl.hpp"
#include "storage_text.hpp"

#include "product_main.hpp"
#include <memory>

// View
int main()
{
    std::unique_ptr<IVProductCtrl> controller = std::make_unique<ProductCtrl>(
        std::make_unique<StorageText>("../../../data/products.txt"));
    std::unique_ptr<IProductView> view = std::make_unique<ProductView>(controller.get());
    controller->SetView(view.get());
    view->Run();
    std::cout << "Done" << std::endl;
}
