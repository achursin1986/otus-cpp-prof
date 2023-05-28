#include "object.hpp"

#include <dlib/clustering.h>
#include <dlib/svm/kkmeans.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>


/*
*   2nd stage
*   find cluster macthing input
*   output sorted result 
*/




typedef dlib::matrix<double, 7, 1> sample_type;
typedef dlib::radial_basis_kernel<sample_type> kernel_type;
typedef std::map<std::size_t, std::vector<std::size_t>> clusters_type;



std::vector<std::size_t> get_close_elements(const Object& obj, const std::vector<Object>& samples,
                                            const dlib::kkmeans<kernel_type>& model,
                                            const clusters_type& clusters) {
    sample_type sample = convert_floor(obj);
    /* find cluster */
    std::size_t cluster_label = model(sample);
    std::vector<std::size_t> elements = clusters.at(cluster_label);
    std::sort(elements.begin(), elements.end(), [&](std::size_t lhs, std::size_t rhs)
                           {
                                return Distance(obj, samples[lhs]) < Distance(obj, samples[rhs]);
                            });

    return elements;
}






int main(int argc, char* argv[]) {

     if (argc != 2) {
           std::cout << "Usage: rclss <model file>";
           return 1;
      }
      /* create and load model from file */ 
      dlib::kcentroid<kernel_type> kc(kernel_type(0.1), 0.01, 8);
      dlib::kkmeans<kernel_type> model(kc);
      std::ifstream model_file(std::string(argv[1]) + ".model", std::ios::in | std::ios::binary);
      deserialize(model, model_file);

      /* get data from saved file */
      std::ifstream data_file(std::string(argv[1]) + ".data", std::ios::in);
      std::pair<std::vector<M_Object>,std::vector<Object>> Data = get_objects(data_file);
      std::vector<Object> objects = Data.second;
      
      /*for ( auto k: objects ) std::cout << k.price << " " ;
      std::cout << std::endl;*/ 

      /* load cluster labels from file */ 
      std::vector<std::size_t> cluster_labels(objects.size());
      std::ifstream labels_file(std::string(argv[1]) + ".labels", std::ios::in);
      for (std::size_t& elem : cluster_labels)
            labels_file >> elem;

      assert(objects.size() == cluster_labels.size());
      
      clusters_type clusters; 
      for (std::size_t i = 0; i < objects.size(); i++)
        clusters[cluster_labels[i]].emplace_back(i);

    

     /* result */
     while (std::cin){
            Object obj = get_object(std::cin);
            std::vector<std::size_t> close_elements = get_close_elements(obj, objects, model, clusters);
            for (auto i : close_elements)
                save_object(std::cout, objects[i]);
     }


     return 0;

}
