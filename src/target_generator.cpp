/*!
\file
\brief Definition of class which keeps information on product generator
\author Anastacia Volkova
*/

#include "target_generator.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>

using std::unique_ptr;
using std::make_unique;
using std::ifstream;
using std::string;
using std::istringstream;
using std::vector;
using std::istream_iterator;

TargetGeneratorText::TargetGeneratorText(string name):TargetGenerator(name){
    ifstream ifs(name_);
    getline(ifs, record_);
    ifs.close();
};

unique_ptr<Target> TargetGeneratorText::GetTarget(){
    istringstream iss(record_);
    vector<float> vec{istream_iterator<float>{iss}, istream_iterator<float>()};
    return make_unique<Target>(vec[0], vec[1], vec[2], vec[3]);
};
