#include "OrderStack.h"
using namespace std;

//Pre:Stack has been initialized
//Post:if stack is full error message will be printed, else a new elemtn will be added at the top of the stack
void OrderStack::push(float widgetPrice, int numOrder) {
	
	if (isFull()) cout << "There are currently to many pending orders, and we are not able to process your order, sorry. " << endl;
	else {
		++top;
		++OrderCounter;
		setOrderObject(top, widgetPrice, numOrder);
	}
}//end push()

//Pre:Stack has been initialized
//Post:If stack is empty error message will be printed, else the top element will be poped from the stack
void OrderStack::pop() {
	if (isEmpty()) cout << "Order Stack Underflow" << endl;
	else {
		cout << "Your order was fully proccesesed, and shipped!" << endl;
		--top;
	}
	
}//end pop()

//Pre:Stack has been initialized
//Post:If stack is empty error message will be printed, else a pointer to  the top object is returned
Order* OrderStack::editOrderStackTop() {
	if (isEmpty()) {
		cout << "Order Stack is empty, nothing to peek" << endl;
		return nullptr;
	}
	else {
		return &orderStackArray[top];
	}
}//end editOrderStackTop()


//Pre:Stack has been initialized
//Post:function will set an object in the array of OrderStack objects
void OrderStack::setOrderObject(int index, float widgetPrice, int numOrder) {

	orderStackArray[index].setNumWidgetsOrdered(numOrder);
	orderStackArray[index].setNumOrdersLeft(numOrder);
	orderStackArray[index].setOrderTrakingNum(OrderCounter);
}//end setOrderObject()


//Pre:Order stack has been initialized
//Post:If orderStack is empty message will be printed, els details of outstanding orders in the stack will be printed
void OrderStack::displayOutstandingOrders(){
	int tempTop = top;
	if (isEmpty()) cout << " There are no outstanding orders, nothing to display" << endl;
	else {
		cout << setw(WIDTH_SIZE)<< "Order#"
			<< setw(WIDTH_SIZE) << "\tQuantity for shipment" << endl;
		for (tempTop; tempTop >= 0; --tempTop)
			cout << setw(WIDTH_SIZE) << orderStackArray[tempTop].getOrderTrakingNum()
			      << setw(WIDTH_SIZE+5) << orderStackArray[tempTop].getNumOrdersLeft()<< "\n" << endl;
	}
}//end displayOutstandingOrders()

