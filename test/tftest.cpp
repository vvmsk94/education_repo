#include <fstream>

#include <gtest/gtest.h>

#include "tfclassifier.h"
#include "helpers.h"

const size_t width = 28;
const size_t height = 28;
const size_t output_dim = 10;

TEST(TfClassifier, predict_proba)
{
    auto clf = TfClassifier{"../saved_model", width, height};

    float class_true;
    auto features = TfClassifier::features_t{};

    std::ifstream test_data{"../data/test_data_cnn.txt"};
    ASSERT_TRUE(test_data.is_open());
    for(;;)
    {
        test_data >> class_true;
        if(!read_features(test_data, features))
        {
            break;
        }
        auto proba_pred = clf.predict_proba(features);
        ASSERT_EQ(proba_pred.size(), 10);
        auto class_pred = clf.predict(features);
        ASSERT_EQ(class_pred, class_true);
    }

    if(test_data.is_open()) test_data.close();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}