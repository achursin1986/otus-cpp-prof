#include "object.hpp"

#include <dlib/clustering.h>
#include <dlib/svm/kkmeans.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/*
*   1st stage
*   prepare data and train model
*   save to files
*/


typedef dlib::matrix<double, 7, 1> sample_type;
typedef dlib::radial_basis_kernel<sample_type> kernel_type;



int main(int argc, char* argv[]) {

        if (argc != 3) { 
                std::cout << "Usage: rclst <num> <file_name_template>" << std::endl;
                return 1;
        }


        dlib::kcentroid<kernel_type> kc(kernel_type(0.1), 0.01, 8);
        dlib::kkmeans<kernel_type> model(kc);

        /* get data */
        std::pair<std::vector<M_Object>,std::vector<Object>> Data = get_objects(std::cin);
        

        std::vector<sample_type> samples = Data.first; 
                 
        /* train model */
        std::vector<sample_type> initial_centers;
        model.set_number_of_centers(std::stoul(argv[1]));
        pick_initial_centers(std::stoul(argv[1]), initial_centers, samples, model.get_kernel()); 
        model.train(samples, initial_centers);

        /* save model, data, labels */
        std::ofstream model_file(std::string(argv[2]) + ".model", std::ios::out | std::ios::binary);
        serialize(model, model_file);
    
        std::ofstream data_file(std::string(argv[2]) + ".data", std::ios::out);
        for (const Object& obj : Data.second)
            save_object(data_file, obj);

        std::ofstream labels_file(std::string(argv[2]) + ".labels", std::ios::out);
        for (const sample_type& sample : samples)
            labels_file << model(sample) << '\n';

         return 0;

}
