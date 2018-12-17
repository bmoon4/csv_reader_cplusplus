/*
//OOP345 - milestone3
//Bokyung Moon(136103165)
//Order.h
*/

#ifndef ORDER_H_
#define ORDER_H_

#include <string>
#include <vector>

using namespace std;

class Order {
	string custName, prodName;
	vector<string> itemList;
public:
	Order(string custName, string prodName, vector<string> itemList);
	void display(ostream& os);
	void graph(ostream& os);
};

#endif
