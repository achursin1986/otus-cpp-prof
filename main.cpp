#include <cassert>
#include <iostream>
#include <iomanip>

#include "frontend.h"

int main() {
	frontend<int, -1> matrix;
	assert(matrix.size() == 0);
	auto a = matrix[0][0];
	assert(a == -1);
	assert(matrix.size() == 0);

        matrix[100][100] = 314;
        assert(matrix[100][100] == 314);
        assert(matrix.size() == 1);


        frontend<int, 0> matrix4;
        for (auto i = 0; i < 10; i++) {
                matrix4[i][i] = i;
                matrix4[i][9 - i] = 9 - i;
        }

	for (auto i = 1; i < 9; i++) {
		for (auto j = 1; j < 9; j++) {
			std::cout << std::setw(2) << matrix4[i][j] << " ";
		}
		std::cout << std::endl;
	}
        std::cout << "occupied = " << matrix4.size() << std::endl;

        matrix[100][100] = 314;
        assert(matrix[100][100] == 314);
        assert(matrix.size() == 1);

	frontend<int, 0> matrix2;
	for (auto i = 0; i < 10; i++) {
		matrix2[i][i] = i;
		matrix2[i][9 - i] = 9 - i;
	}
	for (auto c : matrix2) {
		int i;
		int j;
		int value;
		std::tie(i, j, value) = c;
		std::cout << "i:" << i << " j:" << j << " value=" << value << std::endl;
	}
	frontend<int, -1> matrix3;
	((matrix3[100][100] = 314) = 0) = 217;
	std::cout << matrix3[100][100] << std::endl;

	return 0;
}
