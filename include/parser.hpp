#pragma once
#include <stack>

#include "common.hpp"

class parser : public ops {
    public:
	parser(std::string _open, std::string _close, std::string _prefix, int _N, ops* _data)
	    : open(_open), close(_close), prefix(_prefix), N(_N), data(_data), lock(false) {}

	void check(std::string input) {
		if (input == open) {
			brackets.push(open);
			lock = true;
		}
		if (input == close) {
			if (!brackets.empty()) brackets.pop();
		}
		if ((input.find(prefix) != std::string::npos) && (input != open) && (input != close)) {
			if (!(S == N && brackets.empty())) {
				data->event(command(std::move(input)));
                                //data->event(command(input)); 
				if (!lock) {
					S++;
				}
			}
		} else {
			if (input != open && input != close && input != "null") std::cout << "Not a command, ignored" << std::endl;
		}

                if (S > 0 && lock) {
                        data->event(save());
                        S = 0;
                }

		if (S == N && !lock) {
			data->event(save());
			S = 0;
		}

		if (brackets.empty() && lock) {
			data->event(save());
			lock = false;
			S = 0;
		}
		if (input == "null"  && !lock && N > 1) data->event(save());
	}

	void set_data(ops* _data) { data = _data; }

    private:
	std::string open;
	std::string close;
	std::string prefix;
	int N, S{};
	bool lock;
	std::stack<std::string> brackets;
	ops* data;
};
