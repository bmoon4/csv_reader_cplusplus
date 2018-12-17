/*
// OOP345 - milestone 3
// Bokyung Moon (136103165)
// itemManager.cpp
*/
#include "util.h"
#include "itemManager.h"
#include <algorithm>

ItemManager::ItemManager(string& file, char delim) {
	readCSV(file, delim);
}

void ItemManager::readCSV(string& file, char delim) {
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
				addItem(fields, count);
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

void ItemManager::addItem(vector<string> fields, int line) {
	int count = fields.size();
	string name, installer, remover, code, desc = "";

	switch (count)
	{
	case 5:
		desc = fields[4];
	case 4:
		name = fields[0];
		installer = fields[1];
		remover = fields[2];
		code = fields[3];
		break;
	default:
		cerr << "Line " << line << ": expected 4 or 5 fields for an item, found " << count << endl;
		break;
	}

	if (!name.empty())
		items.push_back(Item(name, installer, remover, code, desc));
}

void ItemManager::display(ostream& os) {
	for (auto item : items)
		item.display(os);
}

void ItemManager::graph(std::string file) {
	std::ofstream os;
	std::string gvFile = file + ".gv";
	std::string pngFile = gvFile + ".png";
	os.open(gvFile);

	os << "digraph task" << " {" << std::endl;

	for (auto item : items)
		item.graph(os);

	os << "}";
	os.close();

	std::string cmd = "dot -Tpng " + gvFile + " -o " + pngFile;
	std::cout << "> " << cmd << std::endl;
	system(cmd.c_str());
	std::cout << "> " << pngFile << std::endl;
	system(pngFile.c_str());
}