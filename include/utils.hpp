#pragma once

#include <boost/algorithm/hex.hpp>
#include <boost/regex.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/uuid/detail/sha1.hpp>
#include <memory>
#include <vector>
#include <string>

namespace bfs = boost::filesystem;

typedef boost::uuids::detail::md5 md5;
typedef boost::uuids::detail::sha1 sha1;

bool isMatchedRegex(const bfs::path& p, const std::vector<boost::regex>& R) {
	if (R.empty()) return true;
	std::string Filename = p.filename().string();
	for (auto i : R) {
		if (boost::regex_match(Filename, i)) {
			return true;
		}
	}

	return false;
};

bool notExcluded(const bfs::path& p, const std::vector<bfs::path>& epaths) {
	for (auto i : epaths) {
		if (p == i) return false;
	}

	return true;
};

void PrepareList(std::multimap<std::size_t, bfs::path>& files, std::vector<bfs::path>& paths, std::vector<bfs::path>& epaths,
		 std::vector<boost::regex>& R, std::size_t fsize, bool recursion) {
	for (const auto& i : paths) {
		std::vector<bfs::path> subpaths{};
		if (bfs::is_directory(i) && notExcluded(i, epaths)) {
			for (auto& j : bfs::directory_iterator(i)) {
				if (bfs::is_regular_file(j) && bfs::file_size(j) >= fsize && isMatchedRegex(j.path(), R)) {
					files.insert(std::make_pair(bfs::file_size(j), j.path()));
				}
				if (bfs::is_directory(j) && recursion && notExcluded(j, epaths)) {
					subpaths.push_back(j);
				}
			}
			if (subpaths.size()) PrepareList(files, subpaths, epaths, R, fsize, recursion);
		}
	}
	return;
};

template <typename H>
std::string toString(const typename H::digest_type& digest) {
	const auto intDigest = reinterpret_cast<const int*>(&digest);
	std::string result;
	boost::algorithm::hex(intDigest, intDigest + (sizeof(typename H::digest_type) / sizeof(int)), std::back_inserter(result));
	return result;
}

template <typename H>
bool isDuplicate(bfs::path& left, bfs::path& right, std::size_t S) {
	std::unique_ptr<char[]> leftBuffer(new char[S]{}), rightBuffer(new char[S]{});
	bfs::ifstream leftFile(left);
	bfs::ifstream rightFile(right);
	H leftHash, rightHash;
	typename H::digest_type leftDigest, rightDigest;

	while (!rightFile.eof() || !leftFile.eof()) {
		rightFile.read(rightBuffer.get(), S);
		leftFile.read(leftBuffer.get(), S);
		rightHash.process_bytes(rightBuffer.get(), S);
		rightHash.get_digest(rightDigest);
		leftHash.process_bytes(leftBuffer.get(), S);
		leftHash.get_digest(leftDigest);
		if (toString<H>(rightDigest) != toString<H>(leftDigest)) return false;
	}

	return true;
};

void GetDuplicates(std::multimap<std::size_t, bfs::path>& files, const std::string H, std::size_t S) {
	for (auto it = files.begin(); it != files.end(); it = files.upper_bound(it->first)) {
		bool found = false;
		std::set<std::string> Duplicates{};
		auto range = files.equal_range(it->first);
		std::vector<bfs::path> temp{};
		for (auto si = range.first; si != range.second; si++) {
			temp.push_back(si->second);
		}

		if (!temp.size()) break;
		bool checked[temp.size()][temp.size()]{false};
		for (int i = 0; i < temp.size(); i++) checked[i][i] = true;
		for (int i = 0; i < temp.size(); i++) {
			for (int j = 0; j < temp.size(); j++) {
				if (!checked[i][j]) {
					if (H == "md5") {
						if (isDuplicate<md5>(temp[i], temp[j], S)) {
							Duplicates.insert(std::move(temp[i].string()));
							Duplicates.insert(std::move(temp[j].string()));
							found = true;
						}
					}

					if (H == "sha1") {
						if (isDuplicate<sha1>(temp[i], temp[j], S)) {
							Duplicates.insert(std::move(temp[i].string()));
							Duplicates.insert(std::move(temp[j].string()));
							found = true;
						}
					}

					checked[i][j] = true;
					checked[j][i] = true;
				}
			}
		}
		for (auto i : Duplicates) std::cout << i << std::endl;
		if (found) std::cout << "****************" << std::endl;
		
	}
        return;
};

