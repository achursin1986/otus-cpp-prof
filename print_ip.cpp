#include <iostream>
#include <list>
#include <tuple>
#include <vector>
#include "utils.hpp"

template <typename T>
struct is_container : std::false_type {};

template <typename... Ts>
struct is_container<std::vector<Ts...>> : std::true_type {};
template <typename... Ts>
struct is_container<std::list<Ts...>> : std::true_type {};
template <typename... Ts>
struct is_container<std::tuple<Ts...>> : std::false_type {};

template <typename T>
struct is_tuple : std::false_type {};

template <typename... Ts>
struct is_tuple<std::tuple<Ts...>> : std::true_type {};

template <typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
void print_ip(T num) {
	for (int i = 0; i < sizeof(num); ++i) {
		std::cout << ((num >> (8 * (sizeof(num) - i - 1)) & 0xff));
		if (i == sizeof(num) - 1) {
			std::cout << std::endl;
		} else {
			std::cout << ".";
		}
	}
}

// sfinae check for string
template <typename T, std::enable_if_t<std::is_same<T, std::string>::value, bool> = true>
void print_ip(T num) {
	std::cout << num << std::endl;
}

// containers

template <typename T, std::enable_if_t<is_container<T>::value, bool> = true>
void print_ip(T num) {
	int j{};
	for (auto const& i : num) {
		std::cout << i;
		j++;
		if (j == num.size()) {
			std::cout << std::endl;
		} else {
			std::cout << ".";
		}
	}
}

// tuple

template <typename T, std::enable_if_t<is_tuple<T>::value, bool> = true>
void print_ip(T num) {

            printTuple(num);

}

int main() {
	print_ip(int8_t{-1});
	print_ip(int16_t{0});
	print_ip(int32_t{2130706433});
	print_ip(int64_t{8875824491850138409});
	print_ip(std::string{"Hello, World!"});
	print_ip(std::vector<int>{100, 200, 300, 400});
	print_ip(std::list<short>{400, 300, 200, 100});
	print_ip(std::make_tuple(123, 456, 789, 0));
}
