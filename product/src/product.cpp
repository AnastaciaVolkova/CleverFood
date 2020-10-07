/*!
\file
\brief Definition of class which keeps information on product
\author Anastacia Volkova
*/

#include "../../include/product/product.hpp"
#include "../../include/product/nutrition.hpp"

#if QT_VERSION
#include <QDebug>
#endif

using std::string;

Product::Product(string name, float p, float f, float c) : name_(name), fat_gr_(f), protein_gr_(p), carbohydrate_gr_(c) {};

bool Product::operator< (const Product& other) const { return name_ < other.name_; };

float Product::GetKCalories() const {
    return (Nutrition::GetKCProtein(protein_gr_) +
        Nutrition::GetKCFat(fat_gr_) +
        Nutrition::GetKCCarb(carbohydrate_gr_));
};

float Product::GetProteinGr() const { return protein_gr_; };

float Product::GetFatGr() const { return fat_gr_; };

float Product::GetCarbGr() const { return carbohydrate_gr_; };

std::string Product::GetName() const { return name_; };

bool Product::SetProteinGr(float p) { protein_gr_ = p; return true; };

bool Product::SetFatGr(float f) { fat_gr_ = f; return true; };

bool Product::SetCarbGr(float c) { carbohydrate_gr_ = c; return true; };
