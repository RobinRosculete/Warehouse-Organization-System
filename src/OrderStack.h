#ifndef OREDERSTACK_H
#define OREDERSTACK_H
#include <iostream>
#include"InventoryStack.h"
#include"Order.h"
#include <iomanip>


class OrderStack:public Order{
public:
	OrderStack():top(-1),OrderCounter(0){}

	//Pre:Stack has been initialized
    //Post:Return true if stack is full else return false
	bool isFull() const {return top == STACK_SIZE-1;}

	//Pre:Stack has been initialized
    //Post:Return true if stack is empty else return false
	bool isEmpty() const { return top == -1; };

	//Pre:Stack has been initialized
    //Post: A copy of the object at the top of the order stack is returned
	Order peek() { return orderStackArray[top]; }
	 
	void push(float widgetPrice,int numWidgetsOrdered);
	void pop();

	Order* editOrderStackTop();

	void setOrderObject(int index, float widgetPrice, int numOrder);
	int getTop()const { return this->top;}
	void displayOutstandingOrders();

private:
	Order orderStackArray[STACK_SIZE];
	int top;
	int OrderCounter;
	
};
#endif OREDERSTACK_H
