#include "../../include/product/nutrition.hpp"

float Nutrition::GetKCProtein(float grams){return grams * kc4g_protein;};
float Nutrition::GetKCFat(float grams){return grams * kc4g_fat;};
float Nutrition::GetKCCarb(float grams){return grams * kc4g_carbohydrate;};

float Nutrition::GetGrProtein(float kcal){return kcal / kc4g_protein;};
float Nutrition::GetGrFat(float kcal){return kcal / kc4g_fat;};
float Nutrition::GetGrCarb(float kcal){return kcal / kc4g_carbohydrate;};
