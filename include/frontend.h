#include <tuple>

#include "backend.h"

template <typename T>
class front_iterator {
	using int_iterator = typename std::map<std::pair<int, int>, T>::iterator;

    public:
	front_iterator(int_iterator iter);
	~front_iterator();
	bool operator!=(front_iterator<T> const& other) const;
	bool operator==(front_iterator<T> const& other) const;
	auto operator*() const;
	auto operator++();

    private:
	int_iterator iterator;
};

template <typename T>
front_iterator<T>::front_iterator(int_iterator iter) : iterator(iter) {}

template <typename T>
front_iterator<T>::~front_iterator() {}

template <typename T>
bool front_iterator<T>::operator!=(front_iterator<T> const& other) const {
	return iterator != other.iterator;
}

template <typename T>
bool front_iterator<T>::operator==(front_iterator<T> const& other) const {
	return iterator == other.iterator;
}

template <typename T>
auto front_iterator<T>::operator*() const {
	return std::make_tuple(iterator->first.first, iterator->first.second, iterator->second);
}

template <typename T>
auto front_iterator<T>::operator++() {
	iterator++;
	return *this;
}

template <typename T, T def = 0>
class frontend {
    public:
	frontend(){};

	auto size() const { return matrix.size(); }

	auto begin() { return front_iterator<T>(matrix.begin()); }

	auto end() { return front_iterator<T>(matrix.end()); }

	auto& operator[](const int& line) {
		matrix.set_line(line);
		return matrix;
	}

    private:
	backend<T, def> matrix;
};

