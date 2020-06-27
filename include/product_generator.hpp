/*!
\file
\brief Declaration of class which keeps information on product generator
\author Anastacia Volkova
*/

#ifndef PRODUCT_GENERATOR_HPP_
#define PRODUCT_GENERATOR_HPP_
#include <memory>
#include <string>
#include <vector>
#include "product.hpp"
class ProductGenerator{
public:
  ProductGenerator(std::string name):name_(name){};
protected:
  virtual std::vector<std::unique_ptr<Product>> GetProducts() = 0;
private:
  std::string name_;
};

class ProductGeneratorText : public ProductGenerator{
public:
  ProductGeneratorText(std::string name);
protected:
  virtual std::vector<std::unique_ptr<Product>> GetProducts() override;
private:
  std::vector<std::string> record_; // Records with products.
};

#endif
