/*!
\file
\brief Definition of class which keeps information on product generator
\author Anastacia Volkova
*/

#include "product_generator.hpp"
#include <fstream>
#include <string>
#include <sstream>

using std::unique_ptr;
using std::unique_ptr;
using std::fstream;
using std::string;

ProductGeneratorText::ProductGeneratorText(string name):ProductGenerator(name){
  ifstream ifs(name);
  string line;
  while (getline(ifs, line))
    records_.push_back(line);
};

vector<unique_ptr> ProductGeneratorText::ProductGeneratorText(){
  vector<unique_ptr> products;
  for (auto r: records){
    istringstream iss(r);
    vector<string> tokens{iss.begin(), iss.end()};
    products.push_back(product(tokens[0], stof(tokens[1]), stof(tokens[2]), stof(tokens[3])));
  }
  return products;
}
