#ifndef ORDER_H
#define ORDER_H
#include "WidgetBatch.h"
class Order {
public:
	Order() :numWidgetsOrdered(0),  orderTrakingNum(0), numOrdersLeft(0) {}

	void setOrderTrakingNum(int orderTrakingNum);

	//Pre:An order has been initialized
	//Post:set the number of widgets ordered
	void setNumWidgetsOrdered(int numOrder) { this->numWidgetsOrdered = numOrder; }

	//Pre:An order has been initialized
	//Post:set the number of orders left
	void setNumOrdersLeft(int numOrdersLeft) { this->numOrdersLeft = numOrdersLeft; }


	//Pre:An order has been initialized
	//Post:return number of widgets ordered
	int getNumWidgetsOrdered()const { return this->numWidgetsOrdered; }

	//Pre:An order has been initialized
	//Post:Return the order traking number
	int getOrderTrakingNum()const { return this->orderTrakingNum; }

	//Pre:An order has been initialized
	//Post:return the number of orders left
	int getNumOrdersLeft()const { return this->numOrdersLeft; }
private:
	int numWidgetsOrdered;
	int numOrdersLeft;
	int orderTrakingNum;
};
#endif ORDER_H
