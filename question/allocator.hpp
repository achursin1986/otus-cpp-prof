#pragma once

#include <cstring>
#include <iostream>
#include <memory>
#include <stack>

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
        std::stack<T*> free_cells; 
};

template <typename T, size_t N>
MyAllocator<T, N>::MyAllocator() : size{}, free{} {
#ifndef USE_PRETTY
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
#else
	std::cout << __PRETTY_FUNCTION__ << "objects = " << n << std::endl;
#endif
        if ( ! free_cells.empty() ) {
              free -= n * sizeof(T);
              T* ptr = free_cells.top();
              free_cells.pop();
              return ptr;
        }

        if ( n > N ) {
            auto p = std::malloc(n * sizeof(T));
                size = n;
                free = n * sizeof(T)/2;  // bytes
                start = reinterpret_cast<T*>(p);
                prev = start;
                curr = start + n;
                return prev;
        }


	if (!size) {
		auto p = std::malloc(N * sizeof(T));
		size = N;
		free = N * sizeof(T);  // bytes
		start = reinterpret_cast<T*>(p);
		curr = start;
	}

	free -= n * sizeof(T);
	prev = curr;
	curr += n;
	if (free > size * sizeof(T)) {
	       free = 0;	
               //throw std::bad_alloc();
	}
	return prev;
}

template <typename T, size_t N>
void MyAllocator<T, N>::deallocate(T* p, std::size_t n) {
#ifndef USE_PRETTY
#else
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif  
	free += n * sizeof(T);

	if (free == size * sizeof(T)) {
		std::free(p);
		free = 0;
		size = 0;
	} else {
                free_cells.push(p);
	}
}

