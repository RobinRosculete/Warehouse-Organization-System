#include "InventoryStack.h"
using namespace std;

//Pre:Stack has been initialized 
//Post:If stack is full print error message, else add a new element at the top of the stack(pirce and quantity of widgets)
void InventoryStack::push(float widgetPrice,int widgetQuantity) {

	if (isFull()) cout << "Inventory is full, can't accept anymore deliveries: " << endl;
	else { 
		++top;
		++batchCounter;
		setInventoryObject(top, widgetPrice, widgetQuantity);
		countNumWidgetsInStock+=widgetQuantity;
	}
}//end push()

//Pre:Stack has been initialized
//Post:If stack is empty print error message, else remove the top element from the stack
void InventoryStack::pop(){

	if (isEmpty()) {
		cout << "Inventory is empty, nothing available for order" << endl;
	}
	else {
	countNumWidgetsShipped += InventoryStackArray[top].getWidgetBatchQuantity();
	countNumWidgetsInStock -= InventoryStackArray[top].getWidgetBatchQuantity();
  	--top;
	}
}//end pop()

//Pre:Stack has been initialized
//Post:If stack is empty error message is printed, else a pointer to the top element of the stack will be returned
WidgetBatch* InventoryStack::editInventoryStackTop() { 
	if (isEmpty()) {
		cout << "Inventory is empty, nothing to edit " << endl;
		return nullptr;
	}
	else {
		return &InventoryStackArray[top];
	}
}//end editInventoryStackTop()

//Pre:Stack has been initialized
//Post:If stack is empty error message will be printed, else function displays all emlements in the inventory stack
void InventoryStack::displayinventoryStackDetails() {
	int tempTop = top;
	if (isEmpty()) cout << " The Inventory is empty, nothing to display" << endl;
	else {
		cout<< setw(WIDTH_SIZE + 1) << "Batch#"
			<< setw(WIDTH_SIZE + 1) << "Quantity on hand:"
			<< setw(WIDTH_SIZE + 1) << "Price Per widget: "<<endl;
		for (tempTop; tempTop >= 0; --tempTop)	
			cout << setw(WIDTH_SIZE+1)<< InventoryStackArray[tempTop].getBatchTrakingNum()
			     << setw(WIDTH_SIZE) << InventoryStackArray[tempTop].getWidgetBatchQuantity()
			     << setw(WIDTH_SIZE) << InventoryStackArray[tempTop].getWidgetPrice() <<"\n" << endl;	
	}

}//end display InventoryStack();

//Pre:Stack has been initialized
//Post:function will set an object in the array of inventoryobjects
void InventoryStack::setInventoryObject(int index, float widgetPrice, int widgetQuantity) {
	InventoryStackArray[index].setWidgetPrice(widgetPrice);
	InventoryStackArray[index].setWidgetBatchQuantity(widgetQuantity);
	InventoryStackArray[index].setBatchTrakingNum(batchCounter);
}//end setInventoryObject()