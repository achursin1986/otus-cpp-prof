#pragma once

#include <dlib/matrix.h>

#include <iostream>
#include <vector>
#include <string>
#include <utility>



constexpr double MAX_LONGITUDE = 180;
constexpr double MAX_LATITUDE = 90;
constexpr double MAX_ROOMS_NUM = 10;
constexpr double MAX_PRICE = 15'000'000;
constexpr double MAX_FULL_AREA = 150;
constexpr double MAX_KITCHEN_AREA = 15;



typedef dlib::matrix<double, 7, 1> M_Object;

struct Object {

        Object(std::vector<double>& obj_vector) {
              longetude = obj_vector[0];
              latitude = obj_vector[1];
              roomnum =  obj_vector[2];
              price =  obj_vector[3];
              full_area =  obj_vector[4];
              kitchen_area =  obj_vector[5];
              floor =  obj_vector[6];
              floor_num =  obj_vector[7];   
        } 


        void normalize() { 
           longetude /= MAX_LONGITUDE;
           latitude /= MAX_LATITUDE;
           roomnum /= MAX_ROOMS_NUM;
           price /= MAX_PRICE;
           full_area /= MAX_FULL_AREA;
           kitchen_area /= MAX_KITCHEN_AREA;
       }


	double longetude;
	double latitude;
	int roomnum;
	int price;
	double full_area;
	double kitchen_area;
	int floor;
	int floor_num;
};

double Distance(const Object& lhs, const Object& rhs) {
	return std::sqrt((lhs.longetude - rhs.longetude) * (lhs.longetude - rhs.longetude) +
			 (lhs.latitude - rhs.latitude) * (lhs.latitude - rhs.latitude));
}



M_Object convert_floor(const Object& data) {
	M_Object converted;
	converted(0) = data.longetude;
	converted(1) = data.latitude;
	converted(2) = data.roomnum;
	converted(3) = data.price;
	converted(4) = data.full_area;
	converted(5) = data.kitchen_area;
	converted(6) = data.floor == 1 || data.floor == data.floor_num;
	return converted;
}

std::pair<std::vector<M_Object>,std::vector<Object>> get_objects(std::istream& stream) {
        std::pair<std::vector<M_Object>,std::vector<Object>> result;
        std::vector<M_Object> mobjects;
        std::vector<Object> objects;
        std::vector<double> obj_vector;
        std::string line;

         obj_vector.reserve(8);
 
        while(std::getline(stream,line)) {
              std::stringstream linestream(line);
              std::string elem;
              while(std::getline(linestream,elem, ';')) {
                       if ( elem.empty() ) continue;
                       obj_vector.push_back(std::stod(elem));                            
              }
              /* if something empty ignore the line */
              if ( obj_vector.size() < 8 ) continue;
              Object obj(obj_vector);
              obj_vector.clear();
              objects.emplace_back(obj);
              obj.normalize();
              mobjects.emplace_back(convert_floor(obj));
        } 
        return std::make_pair(mobjects,objects);

}

Object get_object(std::istream& stream) {
             std::vector<double> obj_vector;
             obj_vector.reserve(8);
             std::string line;
             std::stringstream linestream(line);
             std::string elem;
             std::getline(stream,line);
             while(std::getline(linestream,elem, ';')) {
                       if ( elem.empty() ) continue;
                       obj_vector.push_back(std::stod(elem));
            }
            Object obj(obj_vector);
            return obj;

}




void save_object(std::ostream& stream, const Object& obj) {
    stream << obj.longetude << ';'
           << obj.latitude << ';'
           << obj.roomnum << ';'
           << obj.price << ';'
           << obj.full_area << ';'
           << obj.kitchen_area << ';'
           << obj.floor << ';'
           << obj.floor_num << '\n';
}

