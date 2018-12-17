/*
// OOP345 - milestone 3
// Bokyung Moon (136103165)
// orderManager.cpp
*/
#include "orderManager.h"
#include "util.h"
#include <algorithm>

OrderManager::OrderManager(string& file, char delim) {
	readCSV(file, delim);
}

void OrderManager::readCSV(string& file, char delim) {
	std::ifstream is;
	std::vector<std::string> fields;

	try {
		is.open(file);

		if (is.good()) {

			std::string line;
			std::vector<std::string> fields;

			int count = 0;

			while (std::getline(is, line)) {

				auto cr = line.find('\r');
				if (cr != std::string::npos) {
					line.erase(cr, 1);
				}

				std::string field;

				for (size_t i = 0; i < line.size(); i++) {
					if (line[i] == ' ') {
						field += line[i];
					}
					else {
						if (line[i] != delim) {
							field += line[i];
						}
						else {
							trim(field);
							fields.push_back(move(field));
							count++;
						}
					}
				}
				trim(field);
				fields.push_back(field);
				addOrder(fields, count);
				fields.clear();
			}
			is.close();
		}
		else
			throw "Failed to open file: " + std::string(file);
	}
	catch (std::string err) {
		std::cout << err << std::endl;
	}
}

void OrderManager::addOrder(vector<string> fields, int line) {
	int count = fields.size();
	string custName = "", prodName = "";
	vector<string> itemList;

	if (count < 3)
		cerr << "Line " << line << ": expected 3 or more fields for an order, found " << count << endl;
	else {
		custName = fields[0];
		prodName = fields[1];

		for (int i = 2; i < count; i++)
			itemList.push_back(fields[i]);
	}

	if (!custName.empty())
		orders.push_back(Order(custName, prodName, itemList));
}

void OrderManager::display(ostream& os) {
	for (auto order : orders)
		order.display(os);
}

void OrderManager::graph(std::string file) {
	std::ofstream os;
	std::string gvFile = file + ".gv";
	std::string pngFile = gvFile + ".png";
	os.open(gvFile);

	os << "digraph task" << " {" << std::endl;

	for (auto order : orders)
		order.graph(os);

	os << "}";
	os.close();

	std::string cmd = "dot -Tpng " + gvFile + " -o " + pngFile;
	std::cout << "> " << cmd << std::endl;
	system(cmd.c_str());
	std::cout << "> " << pngFile << std::endl;
	system(pngFile.c_str());
}