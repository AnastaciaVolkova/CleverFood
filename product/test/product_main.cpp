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
    ProductView view(controller.get());
    controller->SetView(&view);
    view.Run();
    std::cout << "Done" << std::endl;
}
