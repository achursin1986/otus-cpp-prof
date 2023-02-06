#pragma once

#include <iostream>
#include <tuple>


template <std::size_t I = 0, typename... Ts>
typename std::enable_if<I == sizeof...(Ts), void>::type printTuple(std::tuple<Ts...> tup) {
	// If iterated through all values
	// of tuple, then simply return.
	return;
}

template <std::size_t I = 0, typename... Ts>
typename std::enable_if<(I < sizeof...(Ts)), void>::type printTuple(std::tuple<Ts...> tup) {
	// Print element of tuple
	std::cout << std::get<I>(tup);
         
        if ( I == sizeof...(Ts) - 1 ) {
         std::cout << std::endl;
        } else {
         std::cout << ".";
        }

	// Go to next element
	printTuple<I + 1>(tup);
}

