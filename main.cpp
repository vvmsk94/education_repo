#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

#include "tfclassifier.h"
#include "helpers.h"

const size_t width = 28;
const size_t height = 28;
const size_t output_dim = 10;

bool read_csv(std::istream& stream, TfClassifier::features_t& features, float &true_class)
{
    std::string line;
    std::getline(stream, line);

    features.clear();
    std::stringstream line_stream{line};
    double value;
    std::string cell;
    size_t cnt = 0;
    while(std::getline(line_stream, cell, ','))
    {
        if(cnt) features.push_back(std::stof(cell));
        else true_class = std::stof(cell);
        ++cnt;
    }
    return stream.good();
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        std::cout << "Invalid number of input parameters" << std::endl;
        return 1;
    }

    std::string test_data_path{argv[1]};
    std::string model_path{argv[2]};

    std::unique_ptr<TfClassifier> clf;
    try
    {
        clf = std::make_unique<TfClassifier>(model_path, width, height);
    }
    catch(const std::exception& e)
    {
        std::cout << "Could not create classifier. Error: " << e.what() << std::endl;
        return 1;
    }

    std::ifstream test_data{test_data_path};
    if(test_data.is_open())
    {
        std::cout << "Test file opened. Processing..." << std::endl;
        double sumTests = 0;
        double rightTests = 0;
        try
        {
            for(;;)
            {
                float class_true;
                auto features = TfClassifier::features_t{};
                if(!read_csv(test_data, features, class_true))
                {
                    break;
                }
                auto class_pred = clf->predict(features);
                if(class_pred == class_true) ++rightTests;
                ++sumTests;
            }
            double accuracy = rightTests / sumTests;
            std::cout << "Accuracy is " << accuracy << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cout << "Error during prediction: " << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "File can not be opened" << std::endl;
        return 1;
    }
    return 0;
}