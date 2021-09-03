#ifndef INVENTORYSTACK_H
#define INVENTORYSTACK_H
#include "Order.h"
#include <iostream>
#include <iomanip>
const int STACK_SIZE = 1000;
const int WIDTH_SIZE = 20;

class InventoryStack:public WidgetBatch { 
public:
	InventoryStack():top(-1),countNumWidgetsInStock(0),countNumWidgetsShipped(0),batchCounter(0){}
	//Pre:Stack has been initialized
    //Post:Return true if stack is full or false if not full
	bool isFull()const { return top == STACK_SIZE-1;}

	//Pre:Stack has been initialized
    //Post:return true if stack is empty or false if not empty
	bool isEmpty()const { return top == -1;};

	//Pre:Stack has been initialized
	//Post: return a copy of top element on stack
	WidgetBatch peek() { return InventoryStackArray[top]; }

	//Pre:Stack has been initialized
	//Post: return a copy of top index of the stack
	int getTop()const { return top; }

	//Pre:NA
	//Post:return the number of widgets in stock
	int getNumWidgetsShipped() { return this->countNumWidgetsShipped; }
	//Pre:NA
	//Post:Set a value in member variable numWidgetsShipped
	void setCountNumWidgetsshipped(int numWidgetsShipped) { this->countNumWidgetsShipped = numWidgetsShipped;}

	void push(float widgetPrice , int widgetQuantity);
	void displayinventoryStackDetails();
	void pop();
	void setcountNumWidgetsInStock(int countNumWidgetsInStock) { this->countNumWidgetsInStock = countNumWidgetsInStock; }
	WidgetBatch* editInventoryStackTop();
	
	void setInventoryObject(int index, float widgetPrice, int widgetQuantity);
	int getCountNumWidgetsInStock()const {return countNumWidgetsInStock;}
	
private:
	WidgetBatch InventoryStackArray[STACK_SIZE];
	int top;
    int countNumWidgetsInStock;
	int countNumWidgetsShipped;
	int batchCounter;
};

#endif INVENTORYSTACK_H
