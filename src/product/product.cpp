/*!
\file
\brief Definition of class which keeps information on product
\author Anastacia Volkova
*/

#include "product.hpp"
#include "nutrition.hpp"
#include <QDebug>

using std::string;

Product::Product(string name, float p, float f, float c): name_(name), fat_gr_(f), protein_gr_(p), carbohydrate_gr_(c){};

float Product::GetKCalories(){
    return (Nutrition::GetKCProtein(protein_gr_)+
            Nutrition::GetKCFat(fat_gr_) +
            Nutrition::GetKCCarb(carbohydrate_gr_));
};

float Product::GetProteinGr(){return protein_gr_;};

float Product::GetFatGr(){return fat_gr_;};

float Product::GetCarbGr(){return carbohydrate_gr_;};