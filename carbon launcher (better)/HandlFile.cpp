#include "HandleFile.h"


HandleFile::HandleFile()
{	
	_f = std::fstream("carbon.versions");

	if (!_f.good()) {
		return;
	}
	data = new char[1024];

	for (int i = 0; i < sizeof(data); i++) {
		data[i] = 0;
	}

}

HandleFile::~HandleFile()
{
	_f.close();
}

void HandleFile::Read() {
	if (_f.is_open()) {
		_f.read(reinterpret_cast<char*>(data), 1024);

		pair tmp;
		bool inpath = false;
		bool foundname = false;
		for (int i = 0; i < 1024; i++) {
			if (data[i] == '"') {
				inpath = !inpath;
				 
				if (!inpath) {
					pairs.push_back(tmp);
					tmp.name = "";
					tmp.path = "";
				}
				continue;
			}

			if (data[i] == '\n') {
				continue;
			}
			if (data[i] == '.' && !foundname) {
				foundname = true;
				continue;
			}
			if (!foundname) {
				name += data[i];
				continue;
			}
			if (!inpath) {
				tmp.name += data[i];
			}
			else {
				tmp.path += data[i];
			}
			
		}
	}
}

void HandleFile::deleteVersion(int index) {
	std::vector<pair> tmp;

	for (int i = 0; i < pairs.size();i++) {
		if (i == index) {
			continue;
		}
		tmp.push_back(pairs[i]);
	}
	pairs = tmp;
}

std::vector<pair> HandleFile::getPair() {
	return pairs;
}
std::string HandleFile::getName() {
	return name;
}

void HandleFile::UpdateName(std::string NewName) {
	name = NewName;
}

