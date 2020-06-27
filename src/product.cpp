/*!
\file
\brief Definition of class which keeps information on product
\author Anastacia Volkova
*/

#include "product.hpp"
#include "nutrition.hpp"

using std::string;

Product::Product(string name, float p, float f, float c): name_(name), fet_(p), protein_(f), carbohydrate_(c){};

float Product::GetKCalories(){
  return 
  Nutrition::GetKCFat(fet_) +
  Nutrition::GetKCProtein(protein_) +
  Nutrition::GetKCCarb(carbohydrate_);};
