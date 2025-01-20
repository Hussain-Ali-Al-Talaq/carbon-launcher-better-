#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>


struct pair
{
	std::string name;
	std::string path;
};
class HandleFile
{
public:
	HandleFile();
	~HandleFile();

	void Read();

	void deleteVersion(int index);
	std::vector<pair> getPair();
	std::string getName();

	void UpdateName(std::string NewName);

private:
	std::fstream _f;
	char* data;
	std::vector<pair> pairs;

	std::string name;

};

