#include "gtest/gtest.h"
#include "product_ctrl_iv.hpp"
#include "product_ctrl.hpp"
#include "storage_text.hpp"
#include "product_view_i.hpp"
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <initializer_list>
#include <fstream>

constexpr char data_path[] = "../../test/test_data.txt";

//virtual void Show() = 0;
//virtual void Save() = 0;
//virtual bool CheckName(std::string name) = 0;

struct MyMap {
    using ViewOut = std::map<std::string, std::vector<float>>;
    ViewOut data;
    MyMap() = default;
    MyMap(std::initializer_list<std::pair<const std::string, std::vector<float>>> x) :data{ x } {};
    bool operator==(const MyMap& ot) const {
        if (data.size() != ot.data.size()) return false;
        for (auto k : data) {
            if (ot.data.find(k.first) == ot.data.end()) return false;
            auto it = k.second.begin();
            auto it_ot = ot.data.at(k.first).begin();
            float diff = 0;
            while (it != k.second.end()) {
                diff += fabsf(*it - *it_ot);
                it++;
                it_ot++;
            }
            if (diff > 1e-3) return false;
        }
        return true;
    }
};

class UnitTestView :public IProductView {
    std::string output_str;
public:
    void Run() override {};

    void Show(std::vector<std::vector<std::string>> records) override {
        output_str = "";
        for (auto line : records) {
            for (auto cell : line)
                output_str += (cell + " ");
            output_str[output_str.size() - 1] = '\n';
        }
    };

    void Output2Map(MyMap::ViewOut& out_m, std::string x_str = "") {
        if (x_str.size() == 0)
            x_str = output_str;
        out_m.clear();
        std::istringstream iss(x_str);
        std::string line;
        while (std::getline(iss, line)) {
            std::istringstream s(line);
            std::vector<std::string> lines{ std::istream_iterator<std::string>{s}, std::istream_iterator<std::string>() };
            out_m.emplace(std::make_pair(lines[0], std::vector<float>{std::stof(lines[1]), std::stof(lines[2]), std::stof(lines[3])}));
        }
    };
};

class IVProductCtrlTest : public ::testing::Test {
protected:
    void SetUp() override {
        product_ctrl = std::make_unique<ProductCtrl>(std::move(std::make_unique<StorageText>(data_path)));
        product_view = std::make_unique<UnitTestView>();
        product_ctrl->SetView(product_view.get());
        data_to_check_true = { "3.4", "3.48", "39.57", "12.7", "4", ".5", "6.",
        "3,4", "3,48", "39,57", "12,7", "4", ",5" };
        data_to_check_false = { "absd", "ab,sd", "1..2", "1.,2", ",12,", ",12.", ".12," };
    };
    void TearDown() {

    };
    std::unique_ptr<IVProductCtrl> product_ctrl;
    std::unique_ptr<IProductView> product_view;
    std::vector<std::string> data_to_check_true;
    std::vector<std::string> data_to_check_false;
};

TEST_F(IVProductCtrlTest, CheckProtein) {
    for (auto a : data_to_check_true)
        EXPECT_TRUE(product_ctrl->CheckProtein(a));
    for (auto a : data_to_check_false)
        EXPECT_FALSE(product_ctrl->CheckProtein(a));
}

TEST_F(IVProductCtrlTest, CheckFat) {
    for (auto a : data_to_check_true)
        EXPECT_TRUE(product_ctrl->CheckFat(a));
    for (auto a : data_to_check_false)
        EXPECT_FALSE(product_ctrl->CheckFat(a));
}

TEST_F(IVProductCtrlTest, CheckCarbo) {
    for (auto a : data_to_check_true)
        EXPECT_TRUE(product_ctrl->CheckCarbo(a));
    for (auto a : data_to_check_false)
        EXPECT_FALSE(product_ctrl->CheckCarbo(a));
}

TEST(IVProductCtrl, AddProduct) {
    std::unique_ptr<IVProductCtrl> product_ctrl =
        std::make_unique<ProductCtrl>(std::move(std::make_unique<StorageText>(data_path)));
    std::unique_ptr<IProductView> product_view = std::make_unique<UnitTestView>();
    product_ctrl->SetView(product_view.get());

    EXPECT_TRUE(product_ctrl->AddProduct("Chocolate", "1.", "10,5", "20.0"));
    EXPECT_FALSE(product_ctrl->AddProduct("Eier", "1.", "10,5", ".0"));
    EXPECT_FALSE(product_ctrl->AddProduct("mAndel", "1.", "10,5", ".0"));
    EXPECT_FALSE(product_ctrl->AddProduct("avocado", "1.", "10,5", ".0"));
    EXPECT_FALSE(product_ctrl->AddProduct("puten", "10..", "10,5", ".0"));
    EXPECT_FALSE(product_ctrl->AddProduct("ggg", "10..", "10,5", ".0"));
    product_ctrl->Show();
    UnitTestView* ut = dynamic_cast<UnitTestView*>(product_view.get());

    MyMap m_out;
    ut->Output2Map(m_out.data);

    MyMap m_ref{
        {"avocado", std::vector<float>{ 4.1f, 20.1f, 6.2f }},
        {"chocolate", std::vector<float>{ 1.0, 10.5, 20.0f }},
        {"eier", std::vector<float>{12.7f, 11.5f, 0.7f}},
        {"mandel", std::vector<float>{ 24.0f, 53.0f, 5.7f }}
    };

    EXPECT_EQ(m_out, m_ref);
}

TEST(IVProductCtrl, UpdateProduct) {
    std::unique_ptr<IVProductCtrl> product_ctrl =
        std::make_unique<ProductCtrl>(std::move(std::make_unique<StorageText>(data_path)));
    std::unique_ptr<IProductView> product_view = std::make_unique<UnitTestView>();
    product_ctrl->SetView(product_view.get());

    EXPECT_TRUE(product_ctrl->UpdateProduct("mandel", IVProductCtrl::Parameter::carbohydrate, "5,9"));
    EXPECT_FALSE(product_ctrl->UpdateProduct("fff", IVProductCtrl::Parameter::carbohydrate, "20,5"));
    product_ctrl->Show();
    MyMap m_out;
    UnitTestView* ut = dynamic_cast<UnitTestView*>(product_view.get());
    ut->Output2Map(m_out.data);
    MyMap m_ref{
    {"avocado", std::vector<float>{ 4.1f, 20.1f, 6.2f }},
    {"eier", std::vector<float>{12.7f, 11.5f, 0.7f}},
    {"mandel", std::vector<float>{ 24.0f, 53.0f, 5.9f }}
    };
    EXPECT_EQ(m_out, m_ref);
}

TEST(IVProductCtrl, DeleteProduct) {
    std::unique_ptr<IVProductCtrl> product_ctrl =
        std::make_unique<ProductCtrl>(std::move(std::make_unique<StorageText>(data_path)));
    std::unique_ptr<IProductView> product_view = std::make_unique<UnitTestView>();
    product_ctrl->SetView(product_view.get());

    EXPECT_TRUE(product_ctrl->DeleteProduct("mandel"));
    EXPECT_FALSE(product_ctrl->DeleteProduct("fff"));
    product_ctrl->Show();
    MyMap m_out;
    UnitTestView* ut = dynamic_cast<UnitTestView*>(product_view.get());
    ut->Output2Map(m_out.data);
    MyMap m_ref{
    {"avocado", std::vector<float>{ 4.1f, 20.1f, 6.2f }},
    {"eier", std::vector<float>{12.7f, 11.5f, 0.7f}},
    };
    EXPECT_EQ(m_out, m_ref);
}

TEST(IVProductCtrl, Save) {
    std::string data_path_new(data_path);
    data_path_new.replace(data_path_new.find("data"), 4, "data_new");

    std::ifstream ifs(data_path);
    std::ofstream ofs(data_path_new);
    ofs << ifs.rdbuf();
    ifs.close();
    ofs.close();

    std::unique_ptr<IVProductCtrl> product_ctrl =
        std::make_unique<ProductCtrl>(std::move(std::make_unique<StorageText>(data_path_new)));
    std::unique_ptr<IProductView> product_view = std::make_unique<UnitTestView>();
    product_ctrl->SetView(product_view.get());

    EXPECT_TRUE(product_ctrl->DeleteProduct("mandel"));
    EXPECT_TRUE(product_ctrl->UpdateProduct("eier", IVProductCtrl::Parameter::carbohydrate, "0.5"));
    EXPECT_TRUE(product_ctrl->AddProduct("pizza", "10.1", "20,5", "16"));
    EXPECT_TRUE(product_ctrl->UpdateProduct("pizza", IVProductCtrl::Parameter::carbohydrate, "16,6"));

    product_ctrl->Save();
    IVProductCtrl* p = product_ctrl.release();
    delete p;

    ifs.open(data_path_new);
    std::ostringstream oss;
    oss << ifs.rdbuf();
    ifs.close();
    std::string x_str = oss.str();

    MyMap m_out;
    UnitTestView* ut = dynamic_cast<UnitTestView*>(product_view.get());
    ut->Output2Map(m_out.data, x_str);

    MyMap m_ref{
    {"avocado", std::vector<float>{ 4.1f, 20.1f, 6.2f }},
    {"eier", std::vector<float>{12.7f, 11.5f, 0.5f}},
    {"pizza", std::vector<float>{10.1f, 20.5f, 16.6f}},
    };

    EXPECT_EQ(m_out, m_ref);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}
