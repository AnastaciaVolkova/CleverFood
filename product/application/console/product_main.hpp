#ifndef VIEW_HPP
#define VIEW_HPP
#include "product_ctrl_iv.hpp"
#include "product_view_i.hpp"

#include <string>
#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class ProductView :public IProductView {
private:
    IVProductCtrl* controller_;
public:
    ProductView(IVProductCtrl* controller) :controller_(controller) {}
    void Show(std::vector<std::vector<std::string>> records) override {
        for (auto a : records) {
            for (auto t : a)
                std::cout << t << " ";
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
    void Run() override {
        char c = ' ';
        while (c != 'q') {
            cout << "Enter command to do: q - exit, a - add, d - delete, u - update, s - show" << endl;
            cin >> c;
            switch (c) {
            case 'a':
                controller_->EnterAdd();
                AddRoutine();
                break;
            case 'd':
                DeleteRoutine();
                break;
            case 'u':
                UpdateRoutine();
                break;
            case 's':
                controller_->Show();
                break;
            case 'q':
                controller_->Save();
            default:
                break;
            }
        }
    }
    ~ProductView() {};
private:
    void AddRoutine() {
        string name, p, f, c;
        bool to_continue;

        cout << "Enter name:" << endl;
        cin >> name;

        to_continue = controller_->EnterName(name);
        while (!to_continue) {
            cout << "Invalid name. Enter again. To go to upper menu enter q." << endl;
            cin >> name;
            to_continue = controller_->EnterName(name) || (name == "q");
        }
        if (name == "q")
            return;

        cout << "Enter protein: " << endl;
        cin >> p;
        to_continue = controller_->EnterProtein(p);
        while (!to_continue) {
            cout << "Invalid protein value. Enter again. To go to upper menu enter q." << endl;
            cin >> p;
            to_continue = controller_->EnterProtein(p) || (p == "q");
        }
        if (p == "q")
            return;

        cout << "Enter fat: " << endl;
        cin >> f;
        to_continue = controller_->EnterFat(f);
        while (!to_continue) {
            cout << "Invalid fat value. Enter again. To go to upper menu enter q." << endl;
            cin >> f;
            to_continue = controller_->EnterFat(f) || (f == "q");
        }
        if (f == "q")
            return;

        cout << "Enter carbohydrate: " << endl;
        cin >> c;
        to_continue = controller_->EnterCarbo(c);
        while (!to_continue) {
            cout << "Invalid name. Enter again. To go to upper menu enter q." << endl;
            cin >> c;
            to_continue = controller_->EnterCarbo(c) || (c == "q");
        }
        if (c == "q")
            return;

        if (controller_->IsReadyToAdd())
            if (!controller_->EnterProduct())
                cout << "Was not added";
    };
    void DeleteRoutine() {
        string name;
        bool to_continue;
        cout << "Enter name of the product to delete: " << endl;
        cin >> name;

        to_continue = controller_->DeleteProduct(name);
        while (!to_continue) {
            cout << "Item was not found. Try again or enter q to exit to upper menu." << endl;
            cin >> name;
            to_continue = controller_->DeleteProduct(name) || (name == "q");
        }
    };
    void ShowRoutine() {};
    void UpdateRoutine() {
        string name, meaning;
        char in_param;
        IVProductCtrl::Parameter param;
        cout << "Enter name:" << endl;
        cin >> name;
        cout << "Enter parameter: protein - p, fet - f, carbohydrate - c" << endl;
        cin >> in_param;
        switch (in_param) {
        case 'p': param = IVProductCtrl::Parameter::protein; break;
        case 'f': param = IVProductCtrl::Parameter::fet; break;
        case 'c': param = IVProductCtrl::Parameter::carbohydrate; break;
        default: return;
        }
        cout << "Enter value: " << endl;
        cin >> meaning;
        controller_->UpdateProduct(name, param, meaning);
    }
};
#endif
