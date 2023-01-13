#include <gtest/gtest.h>

#include <algorithm>

#include "lib.hpp"

using vector_of_strings = std::vector<std::string>;
using vector_of_vectors_of_strings = std::vector<std::vector<std::string>>;

TEST(Tests, Sort) {
	vector_of_vectors_of_strings test_ip_pool, expected_ip_pool;
	vector_of_strings ip1, ip2, ip3;
	ip1.push_back("1");
	ip1.push_back("1");
	ip1.push_back("1");
	ip1.push_back("1");
	ip2.push_back("1");
	ip2.push_back("2");
	ip2.push_back("1");
	ip2.push_back("1");
	ip3.push_back("3");
	ip3.push_back("2");
	ip3.push_back("1");
	ip3.push_back("1");
	expected_ip_pool.push_back(ip3);
	expected_ip_pool.push_back(ip2);
	expected_ip_pool.push_back(ip1);
	test_ip_pool.push_back(ip1);
	test_ip_pool.push_back(ip2);
	test_ip_pool.push_back(ip3);
	std::sort(test_ip_pool.begin(), test_ip_pool.end(), vector_compare);

	EXPECT_TRUE(expected_ip_pool == test_ip_pool);
}

TEST(Tests, Filter_exception) {
	vector_of_vectors_of_strings ip_pool;
	vector_of_strings ip;
	ip.push_back("1");
	ip.push_back("1");
	ip.push_back("1");
	ip.push_back("1");
	try {
		filter(ip_pool, {46, 70, 70, 70, 70});
		FAIL() << "Expected std::invalid_argument";
	} catch (std::invalid_argument const& err) {
		EXPECT_EQ(err.what(), std::string("filter is too long or 0"));

	} catch (...) {
		FAIL() << "Expected std::invalid_argument";
	}
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
