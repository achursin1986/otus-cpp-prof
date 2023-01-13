#pragma once

#include <initializer_list>

using vector_of_strings = std::vector<std::string>;
using vector_of_vectors_of_strings = std::vector<std::vector<std::string>>;

vector_of_strings split(const std::string& str, char d) {
	vector_of_strings r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while (stop != std::string::npos) {
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

bool vector_compare(vector_of_strings& v1, vector_of_strings& v2) {
	if (v1.size() != v2.size()) {
		throw std::invalid_argument(
		    "some ip addresses are wrong sizes");
	}
	for (vector_of_strings::size_type i = 0; i != v1.size(); i++) {
		if (std::stoi(v1[i]) > std::stoi(v2[i])) {
			return true;
		} else if (v1[i] == v2[i]) {
			continue;
		} else {
			return false;
		}
	}
	return false;
}

void filter(vector_of_vectors_of_strings& ip_pool, const std::initializer_list<int> &il) {

        if ( il.size() == 0 || il.size() > 4 ) { 
             throw std::invalid_argument(
                    "filter is too long or 0");

        } 

	for (auto ip : ip_pool) {
                int i{}; 
                size_t found{};
                for ( auto j: il ) {
		     if (std::stoi(ip[i]) == j) {
		               found++;       	        
		     }
                     i++;
                }

                if (!(found == il.size())) {
                                continue;
                        }
		for (auto octet = ip.begin(); octet != ip.end(); ++octet) {
			if (octet != ip.begin()) {
				std::cout << ".";
			}
			std::cout << *octet;
		}
		std::cout << std::endl;
	}
}


void filter_any(vector_of_vectors_of_strings& ip_pool, int il) {
        for (auto ip : ip_pool) {
                        bool found = false;
                        for (auto octet : ip) {
                                if (std::stoi(octet) == il) {
                                        found = true;
                                }
                        }
                        if (!found) {
                                continue;
                        }
                for (auto octet = ip.begin(); octet != ip.end(); ++octet) {
                        if (octet != ip.begin()) {
                                std::cout << ".";
                        }
                        std::cout << *octet;
                }
                std::cout << std::endl;
        }
}

