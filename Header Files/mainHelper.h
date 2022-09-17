#ifndef MAINHELPER_H
#define MAINHELPER_H
#include<iostream>
#include<string>
#include<iomanip>
#include"OrderStack.h"

using namespace std;
using std::string;
enum { DEFAULT_OPTION, DETAILS_ON_HAND, DETAILS_OUTSTANDING_ORDERS, ACCEPT_DELIVERY, TAKE_ORDER, QUIT };


struct Shipment {
	float tempWidgetPrice = 0;
	int tempBatchNum = 0;
	int quanTityShppped = 0;
};

void OptionMenu(int& optionNum);
void acceptDelivery(InventoryStack& inventoryStackObj, OrderStack& orderStackObj);
void takeAnOrder(InventoryStack& obj, OrderStack& orderObj);
void processOrder(InventoryStack& inventoryStackObj, OrderStack& orderStackObj, float widgetPrice, int numWidgetsOrdered, int &shipmentArrayIndex,Shipment shipmentArray[STACK_SIZE]);
void displayOrderDetails(InventoryStack inventoryStackObj, OrderStack orderStackObj, int shipmentArrayIndex, Shipment shipmentArray[]);
float calculateTotalCostToWarhouse(int shipmentArrayIndex, Shipment ShipmentArray[]);
int calculateQuantityShippedThisShppment(int shipmentArrayIndex, Shipment ShipmentArray[]);
#endif MAINHELPER_H