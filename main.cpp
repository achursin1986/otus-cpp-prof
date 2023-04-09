#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <exception>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

#include "utils.hpp"

namespace bpo = boost::program_options;
namespace bfs = boost::filesystem;

int main(int argc, char* argv[]) {
	std::vector<bfs::path> paths{}, epaths{};
	std::vector<std::string> masks{};
	bool recursive;
	std::size_t fsize, S;
	std::string H;
	std::vector<boost::regex> R;
	std::multimap<std::size_t, bfs::path> files{};

	try {
		bpo::options_description desc("options");

		desc.add_options()
                    ("help", "produce help message")
                    ("include", bpo::value<std::vector<bfs::path>>(&paths)->required()->multitoken(), "dirs to scan")
                    ("exclude", bpo::value<std::vector<bfs::path>>(&epaths)->multitoken(), "dirs to exclude from scan")
                    ("recursive", bpo::bool_switch(&recursive)->default_value(false),"default - only top dir, if set - recursive search in subdirs")
                    ("size", bpo::value<std::size_t>(&fsize)->default_value(1), "minimal size of file")
                    ("masks", bpo::value<std::vector<std::string>>(&masks)->multitoken(), "masks to match files")
                    ("S", bpo::value<std::size_t>(&S)->required(), "block size")
                    ("H", bpo::value<std::string>(&H)->required(),"hash algo md5|sha1")
                ;

		bpo::variables_map vm;
		bpo::store(bpo::parse_command_line(argc, argv, desc), vm);

		if (vm.count("help")) {
			std::cout << desc << std::endl;
			return 1;
		}

		if (!vm.count("include") || !vm.count("S")) {
			std::cout << "Need to set at least \"include\" & \"S\" options, run --help for more info" << std::endl;
			return 1;
		}

		bpo::notify(vm);

		if (vm.count("H") && H != "md5" && H != "sha1") {
			std::cout << "Only md5 or sha1 hashing supported, run --help for more info" << std::endl;
			return 1;
		}

		if (vm.count("masks")) {
			for (auto i : masks) {
				R.push_back(boost::regex(i, boost::regex::icase));
			}
		}
                // stage 1 - smart pre search  
		PrepareList(files, paths, epaths, R, fsize, recursive);
                // stage 2 - brute compare with printing results
		GetDuplicates(files, H, S);

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
