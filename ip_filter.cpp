#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "lib.hpp"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]



int main() {
	try {
		vector_of_vectors_of_strings ip_pool;

		for (std::string line; std::getline(std::cin, line);) {
			vector_of_strings v = split(line, '\t');
			ip_pool.push_back(split(v.at(0), '.'));
		}

		// TODO reverse lexicographically sort
		// can be lambda here
		std::sort(ip_pool.begin(), ip_pool.end(), vector_compare);

		// auto
		for (vector_of_vectors_of_strings::const_iterator ip =
			 ip_pool.cbegin();
		     ip != ip_pool.cend(); ++ip) {
			for (vector_of_strings::const_iterator ip_part =
				 ip->cbegin();
			     ip_part != ip->cend(); ++ip_part) {
				if (ip_part != ip->cbegin()) {
					std::cout << ".";
				}
				std::cout << *ip_part;
			}
			std::cout << std::endl;
		}

		// 222.173.235.246
		// 222.130.177.64
		// 222.82.198.61
		// ...
		// 1.70.44.170
		// 1.29.168.152
		// 1.1.234.8

		// TODO filter by first byte and output
		// ip = filter(1)

		// 1.231.69.33
		// 1.87.203.225
		// 1.70.44.170
		// 1.29.168.152
		// 1.1.234.8
                /*
		for (auto ip : ip_pool) {
			if (std::stoi(ip[0]) != 1) {
				continue;
			}
			for (auto octet = ip.begin(); octet != ip.end();
			     ++octet) {
				if (octet != ip.begin()) {
					std::cout << ".";
				}
				std::cout << *octet;
			}
			std::cout << std::endl;
		}
                */
                

		// TODO filter by first and second bytes and output
		// ip = filter(46, 70)

		// 46.70.225.39
		// 46.70.147.26
		// 46.70.113.73
		// 46.70.29.76
                /*
		for (auto ip : ip_pool) {
			if ((std::stoi(ip[0]) == 46) &&
			    (std::stoi(ip[1]) == 70)) {
				for (auto octet = ip.begin(); octet != ip.end();
				     ++octet) {
					if (octet != ip.begin()) {
						std::cout << ".";
					}
					std::cout << *octet;
				}
				std::cout << std::endl;
			}
		} */

		// TODO filter by any byte and output
		// ip = filter_any(46)

		// 186.204.34.46
		// 186.46.222.194
		// 185.46.87.231
		// 185.46.86.132
		// 185.46.86.131
		// 185.46.86.131
		// 185.46.86.22
		// 185.46.85.204
		// 185.46.85.78
		// 68.46.218.208
		// 46.251.197.23
		// 46.223.254.56
		// 46.223.254.56
		// 46.182.19.219
		// 46.161.63.66
		// 46.161.61.51
		// 46.161.60.92
		// 46.161.60.35
		// 46.161.58.202
		// 46.161.56.241
		// 46.161.56.203
		// 46.161.56.174
		// 46.161.56.106
		// 46.161.56.106
		// 46.101.163.119
		// 46.101.127.145
		// 46.70.225.39
		// 46.70.147.26
		// 46.70.113.73
		// 46.70.29.76
		// 46.55.46.98
		// 46.49.43.85
		// 39.46.86.85
		// 5.189.203.46
            /*
		for (auto ip : ip_pool) {
			bool found = false;
			for (auto octet : ip) {
				if (std::stoi(octet) == 46) {
					found = true;
				}
			}
			if (!found) {
				continue;
			}

			for (auto octet = ip.begin(); octet != ip.end();
			     ++octet) {
				if (octet != ip.begin()) {
					std::cout << ".";
				}
				std::cout << *octet;
			}
			std::cout << std::endl;
		}
              */

        filter(ip_pool,{1});
        filter(ip_pool,{46,70});
        filter_any(ip_pool,46);

	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
