#pragma once

#include <iostream>
#include <memory>

#include "container.hpp"
/*
#define USE_PRETTY
*/

template <typename T, size_t N>
struct MyAllocator {
	using value_type = T;

	MyAllocator();

	template <typename U>
	MyAllocator(const MyAllocator<U, N>& other);

	template <typename U>
	struct rebind {
		using other = MyAllocator<U, N>;
	};

	T* allocate(std::size_t n);

	void deallocate(T* p, std::size_t n);

    private:
	T *start, *curr, *prev;
	std::size_t size, free;
};

template <typename T, size_t N>
MyAllocator<T, N>::MyAllocator() {
	size = N;
	free = N;
	auto p = std::malloc(N * sizeof(T));
	if (!p) throw std::bad_alloc();
	start = reinterpret_cast<T*>(p);
	curr = start;
#ifndef USE_PRETTY
	// std::cout << "Allocated: " << N * sizeof(T) << " bytes" << std::endl;
#else
	std::cout << __PRETTY_FUNCTION__ << "objects = " << N << std::endl;
#endif
}

template <typename T, size_t N>
template <typename U>
MyAllocator<T, N>::MyAllocator(const MyAllocator<U, N>&) {}

template <typename T, size_t N>
T* MyAllocator<T, N>::allocate(std::size_t n) {
#ifndef USE_PRETTY
	// std::cout << "allocate: " << n << " objects" << std::endl;
#else
	std::cout << __PRETTY_FUNCTION__ << "objects = " << N << std::endl;
#endif
	// auto p = std::malloc(n * sizeof(T));
	// if (!p) throw std::bad_alloc();
	// std::cout << n * sizeof(T) << std::endl;
	free -= n * sizeof(T);
	prev = curr;
	curr += n;
	if (free < 0) {
		throw std::bad_alloc();
	}
	return prev;
}

template <typename T, size_t N>
void MyAllocator<T, N>::deallocate(T* p, std::size_t n) {
#ifndef USE_PRETTY
	// std::cout << "deallocate: " << n << " objects" << std::endl;
#else
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	free += n * sizeof(T);
	if (free == size) {
		std::free(p);
		free = N;
                curr = start;
	}
}

