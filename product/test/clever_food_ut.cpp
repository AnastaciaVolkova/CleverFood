#include "gtest/gtest.h"
#include "product_ctrl_iv.hpp"
#include "product_ctrl.hpp"
#include "storage_text.hpp"

//enum class Parameter { protein, fet, carbohydrate };
//virtual void SetView(ProductView* view) = 0;
//virtual void Show() = 0;
//virtual void Save() = 0;
//virtual bool AddProduct(std::string name, std::string p, std::string f, std::string c) = 0;
//virtual bool UpdateProduct(std::string name, Parameter parameter, std::string meaning) = 0;
//virtual bool DeleteProduct(std::string name) = 0;
//virtual bool CheckName(std::string name) = 0;
//virtual bool CheckFat(std::string meaning) = 0;
//virtual bool CheckCarbo(std::string meaning) = 0;
//virtual ~IVProductCtrl() {};

class IVProductTest : public ::testing::Test {
protected:
    void SetUp() override {
        product_ctrl = std::make_unique<ProductCtrl>(std::move(std::make_unique<StorageText>("./test_data.txt")));
    };
    std::unique_ptr<IVProductCtrl> product_ctrl;
};

TEST_F(IVProductTest, CheckProtein) {
    EXPECT_TRUE(product_ctrl->CheckProtein("3.4"));
    EXPECT_TRUE(product_ctrl->CheckProtein("3.48"));
    EXPECT_TRUE(product_ctrl->CheckProtein("39.57"));
    EXPECT_TRUE(product_ctrl->CheckProtein("12.7"));
    EXPECT_TRUE(product_ctrl->CheckProtein("4"));
    EXPECT_TRUE(product_ctrl->CheckProtein(".5"));
    EXPECT_TRUE(product_ctrl->CheckProtein("6."));

    EXPECT_TRUE(product_ctrl->CheckProtein("3,4"));
    EXPECT_TRUE(product_ctrl->CheckProtein("3,48"));
    EXPECT_TRUE(product_ctrl->CheckProtein("39,57"));
    EXPECT_TRUE(product_ctrl->CheckProtein("12,7"));
    EXPECT_TRUE(product_ctrl->CheckProtein("4"));
    EXPECT_TRUE(product_ctrl->CheckProtein(",5"));
    EXPECT_TRUE(product_ctrl->CheckProtein("6,"));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}
