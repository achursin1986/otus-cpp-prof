#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cassert> 
#include <mnist/tf_classifier.h>
#include <helpers.h>


using namespace mnist;

const size_t width = 28;
const size_t height = 28;


int main(int argc, char* argv[]) {

    int metric{},total{};

    if (argc != 3) { 
                std::cout << "Usage: fashio_mnist <*.csv> <model>" << std::endl;
                return 1;
    }
    

    /* loading saved model */ 
    auto clf = TfClassifier{std::string(argv[2]), width, height};

    auto features = TfClassifier::features_t{};


    /* read csv and extract answers and data */        
    std::ifstream test_data{std::string(argv[1])};



    for (;;) {
        // read first column and save it for compare
        int val;
        test_data >> val;
        if (!read_features(test_data, features)) {
            break;
        }
        auto proba_pred = clf.predict_proba(features);
        int val_pred = std::distance(std::begin(proba_pred), std::max_element(std::begin(proba_pred), std::end(proba_pred)));
        if ( val == val_pred ) metric++;
        #ifdef DEBUG
        std::cout << "val = " << val << "val_pred = " << val_pred << std::endl;
        for ( auto k: proba_pred ) std::cout << k << " ";
        std::cout << std::endl;
        #endif
        total++;

    } 
      std::cout << std::setprecision(3) << float(metric)/float(total) << std::endl;



      return 0;

}
