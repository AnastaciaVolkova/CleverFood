/*!
\file
\brief Declaration of class which keeps information on target
\author Anastacia Volkova
*/

#ifndef TARGET_HPP_
#define TARGET_HPP_

#include "product.hpp"

/*!
\class Class implements target
*/
class Target{
public:
  //! Default constructor
  Target() = default;
  //! Constructor
  /*!
  \param [in] calories total kcalories pro day
  \param [in] protein_procent protein portion pro day (%)
  \param [in] fat_procent fat portion pro day
  \param [in] carbohydrate_procent carbohydrate portion pro day
  */
  Target(float k_calories, float protein_procent, float fat_procent, float carbohydrate_procent);

  //! Getter for protein in grams
  int GetProteinGr();

  //! Getter for fat in grams
  int GetFatGr();

  //! Getter for carbohydrates in grams
  int GetCarbGr();

  //! Getter for kilocalories
  int GetKCal();

private:
  Product product_;
};
#endif
