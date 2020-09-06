//HotDogStandsClass.cpp

#include "HotDogStandsClass.h"
using namespace std;

// Default constructor to assign default values to data member
HotDogStandsClass::HotDogStandsClass(){
	ID = street = city = country = "";
	totalSold = inventoryAmount = soldCount = 0;
}// End of default constructor

// Parameterized constructor to assign parameter values to data member
HotDogStandsClass::HotDogStandsClass(string id, string st, string ci, string co, int amt){
	ID = id;
	street = st;
	city = ci;
	country = co;
	// Calls the function to validate and assigns the parameter amount
	setInventoryAmount(amt);
	totalSold = soldCount = 0;
}// End of parameterized constructor

// Function to set id
void HotDogStandsClass::setID(string id){
	ID = id;
}// End of function

// Function to set location
void HotDogStandsClass::setLication(string st, string ci, string co){
	street = st;
	city = ci;
	country = co;
}// End of function

// Function to set inventory amount
void HotDogStandsClass::setInventoryAmount(int amt){
	// Checks if amount is less then 0 then set it to 0 after displaying error message
	if (amt < 0)
	{
		cout << "\n Invalid amount.";
		inventoryAmount = 0;
	}// End of if condition

	// Otherwise assigns the parameter amount
	else
		inventoryAmount = amt;
}// End of function

// Function to return id
string HotDogStandsClass::getID() const{
	return ID;
}// End of function

// Function to return location0
string HotDogStandsClass::getLication() const{
	return street + ", " + city + ", " + country;
}// End of function

// Function to return inventory amount
int HotDogStandsClass::getInventoryAmount() const{
	return inventoryAmount;
}// End of function

// Function to return total sold
int HotDogStandsClass::getTotalSold() const{
	return totalSold;
}// End of function

// Function to return sold count
int HotDogStandsClass::getSoldCount() const{
	return soldCount;
}// End of function

// Function to bub dog
void HotDogStandsClass::hotDogsBuy(int n){
	// Checks if inventory amount is 0 then display error message
	if (inventoryAmount == 0)
		cout << "\n Insufficient inventory amount to purchase.";

	// Otherwise checks if inventory amount is less than the parameter amount
	// display error message
	else if (inventoryAmount < n)
		cout << "\n Insufficient inventory amount " << inventoryAmount
		<< "\n Your request is more than the available. Try later.";

	// Otherwise update data
	else{
		inventoryAmount -= n;
		totalSold += n;
		soldCount++;
	}// End of else
}// End of function

// Function to increase the inventory amount by the parameter amount
void HotDogStandsClass::stockInventory(int n){
	inventoryAmount += n;
}// End of function

// Overrides << operator to return hot dog information
ostream& operator <<(ostream& out, HotDogStandsClass& hd){
	out << "\n\n ID: " << hd.getID() << "\n Location: " << hd.getLication()
		<< "\n Inventory Amount: " << hd.getInventoryAmount()
		<< "\n Total Sold: " << hd.getTotalSold()
		<< "\n Sold Count: " << hd.getSoldCount();
	return out;
}// End of function

int main(){
	// Creates two object of class HotDogStand using parameterized constructor
	HotDogStandsClass* hd1 = new HotDogStandsClass("111", "12 Deepika", "Bangalore", "India", 900);
	HotDogStandsClass* hd2 = new HotDogStandsClass("222", "11 Rukmini", "Mumbai", "India", 400);

	// Calls the function to test
	cout << "\n Initial Status for HD1\n";
	cout << *hd1;
	cout << "\n After buying 50 for HD1 status\n";
	hd1->stockInventory(50);
	cout << *hd1;

	cout << "\n After selling 10 for HD1 status\n";
	hd1->hotDogsBuy(10);
	cout << *hd1;

	cout << "\n After selling 90 for HD1 status\n";
	hd1->hotDogsBuy(90);
	cout << *hd1;

	cout << "\n Initial Status for HD2\n";
	cout << *hd2;
	cout << "\n After buying 50 for HD2 status\n";
	hd2->stockInventory(50);
	cout << *hd2;

	cout << "\n After selling 10 for HD2 status\n";
	hd2->hotDogsBuy(10);
	cout << *hd2;

	cout << "\n After selling 90 for HD2 status\n";
	hd2->hotDogsBuy(90);
	cout << *hd2;
	return 0;
}// End of main function