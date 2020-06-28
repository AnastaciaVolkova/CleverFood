#include "target.hpp"
#include "nutrition.hpp"


Target::Target(float k_calories, float protein_procent, float fat_procent, float carbohydrate_procent){
  if ((protein_procent + fat_procent + carbohydrate_procent) > 100.0f){
    protein_procent = 25;
    fat_procent = 25;
    carbohydrate_procent = 50;
  }
  product_ = Product("target",
  Nutrition::GetGrProtein((protein_procent/100.0f)*k_calories),
  Nutrition::GetGrFat((fat_procent/100.0f)*k_calories),
  Nutrition::GetGrCarb(carbohydrate_procent/100.0f));
};

int Target::GetProteinGr(){return product_.GetProteinGr();};

int Target::GetFatGr(){return product_.GetFatGr();};

int Target::GetCarbGr(){return product_.GetCarbGr();};

int Target::GetKCal(){return product_.GetKCalories();};
