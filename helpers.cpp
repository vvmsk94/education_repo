#include "helpers.h"

#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>

bool read_features(std::istream& stream, TfClassifier::features_t& features)
{
    std::string line;
    std::getline(stream, line);

    features.clear();
    std::istringstream linestream{line};
    double value;
    while(linestream >> value)
    {
        features.push_back(value);
    }
    return stream.good();
}