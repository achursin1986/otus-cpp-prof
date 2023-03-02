#pragma once

#include <map>

template <typename T, T def>
class backend {
	using coordinates = std::pair<int, int>;

    public:
	backend(){};

	auto size() const { return matrix.size(); }
	auto& operator[](const int& pos) {
		curr.second = pos;
		return *this;
	}

	void set_line(const int& line) { curr.first = line; }

	auto get() const {
		auto it = matrix.find(curr);
		if (it != matrix.end()) return it->second;
		return def;
	}

	auto& operator=(const T& other) {
		if (other != def) {
			matrix[curr] = other;
		} else {
			auto it = matrix.find(curr);
			if (it != matrix.end()) matrix.erase(it->first);
		}
		return *this;
	}

	auto begin() { return matrix.begin(); };
	auto end() { return matrix.end(); }

	//       std::map<coordinates, T>::iterator

	operator auto() { return get(); }

    private:
	std::map<coordinates, T> matrix;
	coordinates curr;
};

