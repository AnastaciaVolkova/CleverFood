/*!
\file
\brief Definition of class which keeps information on product
\author Anastacia Volkova
*/

#include "product.hpp"
#include "nutrition.hpp"

using std::string;

Product::Product(string name, float p, float f, float c): name_(name), fat_gr_(p), protein_gr_(f), carbohydrate_gr_(c){};

float Product::GetKCalories(){
  return 
  Nutrition::GetKCFat(fat_gr_) +
  Nutrition::GetKCProtein(protein_gr_) +
  Nutrition::GetKCCarb(carbohydrate_gr_);};

int Product::GetProteinGr(){return protein_gr_;};

int Product::GetFatGr(){return fat_gr_;};

int Product::GetCarbGr(){return carbohydrate_gr_;};
