#include <gtest/gtest.h>
#include <algorithm>

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
	std::sort(test_ip_pool.begin(), test_ip_pool.end(),
		  [](vector_of_strings& v1, vector_of_strings& v2) -> bool {
			  if (v1.size() != v2.size()) {
				  throw std::invalid_argument(
				      "some ip addresses are wrong sizes");
			  }
			  for (vector_of_strings::size_type i = 0;
			       i != v1.size(); i++) {
				  if (std::stoi(v1[i]) > std::stoi(v2[i])) {
					  return true;
				  } else if (v1[i] == v2[i]) {
					  continue;
				  } else {
					  return false;
				  }
			  }
			  return false;
		  });

	EXPECT_TRUE(expected_ip_pool == test_ip_pool);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
