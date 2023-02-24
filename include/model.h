#pragma once
#include "figures.h"
#include "common.h"

class Model: public Callback {
    public:
	Model() {}
	Model(const std::string &path) { this->LoadData(path); }
	Model *Get() { return this; }
	void LoadData(const std::string &path){/* logic to get data from a file , and update View this->event->callback();*/};
	void SaveData(const std::string &path){/* logic to save data to a file */};
	void NewData() {
		document = std::make_shared<Document>(Document());
		this->event->callback();
	};

	void AddLine(int x1, int y1, int x2, int y2) {
		document.get()->Add_Line(x1, y1, x2, y2);
		this->event->callback();
	};
	void RemoveLast() {
		document.get()->Remove_Last();
		this->event->callback();
	}
	void RegisterDataChangeHandlers(Callback* handler) { this->event = handler; }

    private:
	std::shared_ptr<Document> document;
	Callback* event = nullptr;
        
};
