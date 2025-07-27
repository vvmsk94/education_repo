#include <istream>
#include <string>
#include <vector>

#include "tfclassifier.h"

bool read_features(std::istream& stream, TfClassifier::features_t& features);

std::vector<float> read_vector(std::istream&);
