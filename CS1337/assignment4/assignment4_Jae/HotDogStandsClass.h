#pragma once
#ifndef HOTDOGSTANDSCLASS_H
#define HOTDOGSTANDSCLASS_H
#include <iostream>
#include <string>

using namespace std;

// Defines class HotDogStand
class HotDogStandsClass{
public:
	// Prototype of member functions
	HotDogStandsClass();
	HotDogStandsClass(string, string, string, string, int);
	void setID(string);
	void setLication(string, string, string);
	void setInventoryAmount(int);

	string getID() const;
	string getLication() const;
	int getInventoryAmount() const;
	int getTotalSold() const;
	int getSoldCount() const;

	void hotDogsBuy(int);
	void stockInventory(int);

	friend ostream& operator <<(ostream&, HotDogStandsClass&);

private:
	// Data member to store hot dog information
	string ID;
	string street, city, country;
	int totalSold;
	static int inventoryAmount;
	int soldCount;
};
int HotDogStandsClass::inventoryAmount = 0;
#endif // ! HOTDOGSTANDSCLASS_H