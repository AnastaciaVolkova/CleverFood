/*!
\file Declaration of Nutrition class 
\author Anastacia Volkova
*/
#ifndef NUTRITION_
#define NUTRITION_
class Nutrition{
private:
  static constexpr float kc4g_fat = 9.0f;
  static constexpr float kc4g_protein = 4.0f;
  static constexpr float kc4g_carbohydrate = 4.0f;
public:
  static float GetKCProtein(float grams);
  static float GetKCFat(float grams);
  static float GetKCCarb(float grams);

  static float GetGrProtein(float kcal);
  static float GetGrFat(float kcal);
  static float GetGrCarb(float kcal);
};
#endif
