/*
//OOP345 - milestone3
//Bokyung Moon(136103165)
//taskManager.h
*/

#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "task.h"

class TaskManager {
	std::vector<Task> tasks;
	void addTask(std::vector<std::string> fields, int line);

public:
	TaskManager(std::string& file, char delim);
	void readCSV(std::string& file, char delim);
	void display(std::ostream& os);
	void graph(std::string file);
};

#endif
