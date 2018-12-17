/*
// OOP345 - milestone 3
// Bokyung Moon (136103165)
// taskManager.cpp
*/
#include "util.h"
#include "taskManager.h"
#include <algorithm>


TaskManager::TaskManager(std::string& file, char delim) {
	readCSV(file, delim);
}

void TaskManager::readCSV(std::string& file, char delim) {
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
				addTask(fields, count);
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

void TaskManager::addTask(std::vector<std::string> fields, int line) {
	int count = fields.size();
	std::string name, slots = "0", accept = "", reject = "";

	switch (count) {
	case 4:
		reject = fields[3];
	case 3:
		accept = fields[2];
	case 2:
		slots = fields[1];
	case 1:
		name = fields[0];
		break;
	default:
		std::cerr << "Line " << line << ": expected 1-4 fields for a task, found " << count << std::endl;
		break;
	}

	if (!name.empty())
		tasks.push_back(Task(name, slots, accept, reject));
}

void TaskManager::display(std::ostream& os) {
	for (auto task : tasks)
		task.display(os);
}

void TaskManager::graph(std::string file) {
	std::ofstream os;
	std::string gvFile = file + ".gv";
	std::string pngFile = gvFile + ".png";
	os.open(gvFile);

	os << "digraph task" << " {" << std::endl;

	for (auto task : tasks)
		task.graph(os);

	os << "}";
	os.close();

	std::string cmd = "dot -Tpng " + gvFile + " -o " + pngFile;
	std::cout << "> " << cmd << std::endl;
	system(cmd.c_str());
	std::cout << "> " << pngFile << std::endl;
	system(pngFile.c_str());
}