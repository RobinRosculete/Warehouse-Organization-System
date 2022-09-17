#include"Order.h"

//Pre:An order exists
//Post: Set an order traking, base traking number is 1000
void Order::setOrderTrakingNum(int orderTrakingNum)
{ 
    const int baseTrakingNum = 1000;
	this->orderTrakingNum = orderTrakingNum+baseTrakingNum;

}//End setOrderTrakingNum()