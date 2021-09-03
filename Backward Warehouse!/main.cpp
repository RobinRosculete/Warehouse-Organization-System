#include "mainHelper.h"
const float MARKUP = 1; //100%

int main() {
	int optionNum = 0;
	float widgetPrice = 0;
	int batchQuantity=0;
	int numOrders = 0;
	int shipmentArrayIndex = -1;
	Shipment shipmentArray[STACK_SIZE];
	InventoryStack inventoryStackObj;
	OrderStack orderStackObj;

	cout << setprecision(2) << fixed;
	while (optionNum != QUIT)
	{
		OptionMenu(optionNum);
		switch (optionNum)
		{
		case DETAILS_ON_HAND: inventoryStackObj.displayinventoryStackDetails();
			break;

		case DETAILS_OUTSTANDING_ORDERS: orderStackObj.displayOutstandingOrders();
			break; 

		case ACCEPT_DELIVERY: acceptDelivery(inventoryStackObj, orderStackObj);

			if (orderStackObj.peek().getNumOrdersLeft() > 0) {
				processOrder(inventoryStackObj, orderStackObj,inventoryStackObj.peek().getWidgetPrice(),orderStackObj.peek().getNumOrdersLeft(),shipmentArrayIndex, shipmentArray);
			}
			break;

		case TAKE_ORDER: takeAnOrder(inventoryStackObj,orderStackObj);
            shipmentArrayIndex = -1;
			processOrder(inventoryStackObj, orderStackObj, widgetPrice, orderStackObj.peek().getNumWidgetsOrdered(),shipmentArrayIndex, shipmentArray);
			break;
		case QUIT:break;
		default:
			cout << "Error! Please enter an option below!" << endl;
			break;
		}
    
	}
	return 0;
}
//Pre:NA
//Post:Print an option menu an eturn the users option number 
void OptionMenu(int& optionNum) {
	cout << "\n\t\t***Waerehouse***"
	 "\n\nPlease enter an option below\n\t"
	    << DETAILS_ON_HAND << ".Inventory\n\t"
        << DETAILS_OUTSTANDING_ORDERS << ".Outstanding orders\n\t"
		<< ACCEPT_DELIVERY << ".Accept a delivery\n\t"
		<< TAKE_ORDER << ".Take an order\n\t"
		<< QUIT << ".Quit!" << endl;
	if (!(cin >> optionNum)) {
		cin.clear();
		cin.ignore(2000, '\n');
	}

}//End OptionMenu


//Pre:inventory stack has been initilized
/*Post:
*Ask user for information to be accepted for delivery
*If input error, error message will be printed and user wil be able to renter values
*If input is correct, the data is pushed on the inventory stack, and available for order
*/
void acceptDelivery(InventoryStack& inventoryStackObj, OrderStack& orderStackObj) {
	float widgetPrice =0;
	
	int  widgetQuantity =0;
	cout << "What size would you like the batch of widgets to be?(Positive integers only greater than 1) " << endl;
	while (!(cin >> widgetQuantity) || widgetQuantity < 1)
	{
		cout << "Error, please enter a positive integer greater than 1! " << endl;
		cin.clear();
		cin.ignore(2000, '\n');
	}
	cout << "What is the price per widget? " << endl;
	while (!(cin >> widgetPrice) || widgetPrice < 1) {
		cout << "Error, please enter a positive integer greater than 1!" << endl;
		cin.clear();
		cin.ignore(2000, '\n');

	}
	inventoryStackObj.push(widgetPrice, widgetQuantity);
    inventoryStackObj.displayinventoryStackDetails();
}// end acceptDelivery()


//Pre:order and inventory stack have been initialized
//Post: Take information from user for order, if valid, push order on to the stack, if not valid input let user renter data
void  takeAnOrder(InventoryStack& inventoryStackObj, OrderStack& orderStackObj) {
	int numWidgetsOrdered = 0;
	float widgetPrice = 0; 
	if (inventoryStackObj.isEmpty()) {
		cout << "How many widgets would you like to order?" << endl;
		while (!(cin >> numWidgetsOrdered) || numWidgetsOrdered < 0) {
			cout << "Error! Please renter the number of widgets you would like to order!(positive numbers greater than 1)" << endl;
			cin.clear();
			cin.ignore(2000, '\n');
		}
		cout << "Inventory is out of stock, your order was saved and will be shipped as soon as possible" << endl;
	   orderStackObj.push(widgetPrice, numWidgetsOrdered);
       cout << setw(WIDTH_SIZE) << "Order#"
            << setw(WIDTH_SIZE) << "\tQuantity for shipment\n" 
            << setw(WIDTH_SIZE) << orderStackObj.peek().getOrderTrakingNum()
            << setw(WIDTH_SIZE + 5) << orderStackObj.peek().getNumWidgetsOrdered() << "\n" << endl;
	}else {
		widgetPrice = inventoryStackObj.peek().getWidgetPrice();

		cout << "How many widgets would you like to order" << endl;
		while (!(cin >> numWidgetsOrdered) || numWidgetsOrdered < 0) {
			cout << "Error! Please renter the number of widgets you would like to order!(positive numbers greater than 1)" << endl;
			cin.clear();
			cin.ignore(2000, '\n');
		}

		orderStackObj.push(widgetPrice, numWidgetsOrdered);
	}
}//end tankeAnOrder()

//Pre:order and inventory stack have been initialized
//Post: All order in order stack will be processed as long as there are available widgets in inventory stack
void processOrder(InventoryStack& inventoryStackObj, OrderStack& orderStackObj,float widgetPrice ,int numWidgetsOrdered, int& shipmentArrayIndex, Shipment shipmentArray[STACK_SIZE]) {
	
	while (!(orderStackObj.isEmpty()) && !(inventoryStackObj.isEmpty())) {
		
		if (inventoryStackObj.getCountNumWidgetsInStock() >= orderStackObj.peek().getNumOrdersLeft()) {

			while (orderStackObj.peek().getNumOrdersLeft() != 0 && !(inventoryStackObj.isEmpty())) {

				if (inventoryStackObj.peek().getWidgetBatchQuantity() < orderStackObj.peek().getNumOrdersLeft())
				{
					orderStackObj.editOrderStackTop()->setNumOrdersLeft(orderStackObj.peek().getNumOrdersLeft() - inventoryStackObj.peek().getWidgetBatchQuantity());
					shipmentArray[++shipmentArrayIndex].quanTityShppped = inventoryStackObj.peek().getWidgetBatchQuantity();
					shipmentArray[shipmentArrayIndex].tempBatchNum = inventoryStackObj.peek().getBatchTrakingNum();
					shipmentArray[shipmentArrayIndex].tempWidgetPrice = inventoryStackObj.peek().getWidgetPrice();

					inventoryStackObj.pop();		
				}
				else if (inventoryStackObj.peek().getWidgetBatchQuantity() == orderStackObj.peek().getNumOrdersLeft()) {
				
					orderStackObj.editOrderStackTop()->setNumOrdersLeft(0);	
					shipmentArray[++shipmentArrayIndex].quanTityShppped = inventoryStackObj.peek().getWidgetBatchQuantity();
					shipmentArray[shipmentArrayIndex].tempBatchNum = inventoryStackObj.peek().getBatchTrakingNum();
					shipmentArray[shipmentArrayIndex].tempWidgetPrice = inventoryStackObj.peek().getWidgetPrice();
					inventoryStackObj.pop();
				}
				else {
					
					inventoryStackObj.editInventoryStackTop()->setWidgetBatchQuantity(inventoryStackObj.peek().getWidgetBatchQuantity() - orderStackObj.peek().getNumOrdersLeft());
					shipmentArray[++shipmentArrayIndex].quanTityShppped = orderStackObj.peek().getNumOrdersLeft();
					shipmentArray[shipmentArrayIndex].tempBatchNum = inventoryStackObj.peek().getBatchTrakingNum();
					shipmentArray[shipmentArrayIndex].tempWidgetPrice = inventoryStackObj.peek().getWidgetPrice();

					inventoryStackObj.setCountNumWidgetsshipped(inventoryStackObj.getNumWidgetsShipped() + orderStackObj.peek().getNumOrdersLeft());
					inventoryStackObj.setcountNumWidgetsInStock(inventoryStackObj.getCountNumWidgetsInStock() - orderStackObj.peek().getNumOrdersLeft());
					orderStackObj.editOrderStackTop()->setNumOrdersLeft(0);
				}
			}//end while loop

		}//End if(inventoryStackObj.getCountNumWidgetsInStock() >= numWidgetsOrdered)!
		else if (inventoryStackObj.getCountNumWidgetsInStock() < orderStackObj.peek().getNumWidgetsOrdered()) {

			while (inventoryStackObj.getCountNumWidgetsInStock() != 0) {
				if (inventoryStackObj.peek().getWidgetBatchQuantity() != 0) {
				
					shipmentArray[++shipmentArrayIndex].quanTityShppped = inventoryStackObj.peek().getWidgetBatchQuantity();
					shipmentArray[shipmentArrayIndex].tempBatchNum = inventoryStackObj.peek().getBatchTrakingNum();
					shipmentArray[shipmentArrayIndex].tempWidgetPrice = inventoryStackObj.peek().getWidgetPrice();
                    
					orderStackObj.editOrderStackTop()->setNumOrdersLeft(orderStackObj.peek().getNumOrdersLeft() - inventoryStackObj.peek().getWidgetBatchQuantity());
					inventoryStackObj.pop();
				}
			}
		}
		//Displaying order details after order has been proccesed
		if (orderStackObj.peek().getNumOrdersLeft() == 0) {
			displayOrderDetails(inventoryStackObj, orderStackObj,shipmentArrayIndex,shipmentArray);
			orderStackObj.pop();
			shipmentArrayIndex = -1;
		}
		else

		{
            cout << "\n***Backorder Message: Your order was partially filled, backorder Details***" << endl;
			displayOrderDetails( inventoryStackObj, orderStackObj,shipmentArrayIndex,shipmentArray);	   
            shipmentArrayIndex=-1;
		}
	}//end while (!(orderStackObj.isEmpty()) && !(inventoryStackObj.isEmpty()))
}//End process order()

//Pre:An order has been processed
//Post:All ditails regarding the order and shipment will be printed to the screen
void displayOrderDetails(InventoryStack inventoryStackObj, OrderStack orderStackObj, int shipmentArrayIndex ,Shipment shipmentArray[]) {
	
	float costToCustomer = calculateTotalCostToWarhouse(shipmentArrayIndex, shipmentArray)* (1+ MARKUP);

	   cout << setw(WIDTH_SIZE) << "\nOrder Traking num: " << setw(WIDTH_SIZE) << orderStackObj.peek().getOrderTrakingNum()
			<< setw(WIDTH_SIZE) << "\nQuantity Ordered: " << setw(WIDTH_SIZE+1) << orderStackObj.peek().getNumWidgetsOrdered()
			<< setw(WIDTH_SIZE) << "\nQuantity Shipped this Shipment:" << setw(WIDTH_SIZE-12) << calculateQuantityShippedThisShppment(shipmentArrayIndex, shipmentArray)
			<< setw(WIDTH_SIZE) << "\nQuantity to be Filled: " << setw(WIDTH_SIZE-4) << orderStackObj.peek().getNumOrdersLeft()
			<< setw(WIDTH_SIZE) << "\nTotal Cost to Warehouse is: " << setw(WIDTH_SIZE-9) << calculateTotalCostToWarhouse(shipmentArrayIndex, shipmentArray)	
			 << setw(WIDTH_SIZE) << "\nProfit this shipment: " << setw(WIDTH_SIZE-3) << costToCustomer-calculateTotalCostToWarhouse(shipmentArrayIndex, shipmentArray) 
             << setw(WIDTH_SIZE) << "\nTotal Cost to the Customer: " << setw(WIDTH_SIZE - 9) << costToCustomer << endl;

	  cout << "\n\nShipment details\n" 
           << setw(WIDTH_SIZE + 1) << "Delivery#"
		   << setw(WIDTH_SIZE + 1) << "Qty Shipped"
		   << setw(WIDTH_SIZE + 1) << "Unit Price"
		   << setw(WIDTH_SIZE + 1) << "Cost to Warehouse"
		   << setw(WIDTH_SIZE + 1) << "Cost to Customer" << endl;
		   for (int i = 0; i <= shipmentArrayIndex; ++i) {
			  cout << setw(WIDTH_SIZE+1) << shipmentArray[i].tempBatchNum
				   << setw(WIDTH_SIZE+1) << shipmentArray[i].quanTityShppped
				   << setw(WIDTH_SIZE+1) << shipmentArray[i].tempWidgetPrice
				   << setw(WIDTH_SIZE+1) << shipmentArray[i].tempWidgetPrice * shipmentArray[i].quanTityShppped
				   << setw(WIDTH_SIZE+1) << shipmentArray[i].tempWidgetPrice * shipmentArray[i].quanTityShppped * (1 + MARKUP) << endl;
		   }
}//End displayOrderStack()

//Pre:An order has been processed
//Post:return the total cost to the Warhouse
float calculateTotalCostToWarhouse(int shipmentArrayIndex, Shipment ShipmentArray[]) {
	float totalCost = 0;
	for (int x = 0; x <= shipmentArrayIndex; ++x) {
		totalCost += ShipmentArray[x].tempWidgetPrice*ShipmentArray[x].quanTityShppped;
	}return totalCost;
}//End calculateTotalCostToWarhouse()

//Pre:An order has been processed
//Post:Return the total quantity shipped this order
int calculateQuantityShippedThisShppment(int shipmentArrayIndex, Shipment ShipmentArray[]){
     int quantityShipped = 0;
     for (int x = 0; x <= shipmentArrayIndex; ++x) {
         quantityShipped += ShipmentArray[x].quanTityShppped;
     } return quantityShipped;
 }//end  calculateQuantityShippedThisShppment

//Test Data:
//1.Testing menu option 1.Details of inventory on hand: Function void displayinventoryStackDetails():
/*
    
                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
1
 The Inventory is empty, nothing to display

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
10
What is the price per widget?
2
               Batch#    Quantity on hand:   Price Per widget:
                  101                  10                2.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
10
What is the price per widget?
4
               Batch#    Quantity on hand:   Price Per widget:
                  102                  10                4.00

                  101                  10                2.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
100
What is the price per widget?
6
               Batch#    Quantity on hand:   Price Per widget:
                  103                 100                6.00

                  102                  10                4.00

                  101                  10                2.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
1
               Batch#    Quantity on hand:   Price Per widget:
                  103                 100                6.00

                  102                  10                4.00

                  101                  10                2.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order
110

Order Traking num:                 1001
Quantity Ordered:                   110
Quantity Shipped this Shipment:     110
Quantity to be Filled:                0
Total Cost to Warehouse is:      640.00
Total Cost to the Customer:     1280.00
Profit this shipment:            640.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  103                  100                 6.00               600.00              1200.00
                  102                   10                 4.00                40.00                80.00
Your order was fully proccesesed, and shipped!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
1
               Batch#    Quantity on hand:   Price Per widget:
                  101                  10                2.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order
20

Backorder Message: Your order was partially filled, backorder Details:

Order Traking num:                 1002
Quantity Ordered:                    20
Quantity Shipped this Shipment:      10
Quantity to be Filled:               10
Total Cost to Warehouse is:       20.00
Total Cost to the Customer:       40.00
Profit this shipment:             20.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  101                   10                 2.00                20.00                40.00

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
1
 The Inventory is empty, nothing to display

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!

*/





//2.Testing menu option 2.Details of outstanding deliveries: Function void displayOutstandingOrders():
/*
    
     
                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
10
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1001                       10


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
20
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1002                       20


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
30
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1003                       30


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
2
              Order#    Quantity for shipment
                1003                       30

                1002                       20

                1001                       10


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
50
What is the price per widget?
2
               Batch#    Quantity on hand:   Price Per widget:
                  101                  50                2.00


Order Traking num:                 1003
Quantity Ordered:                    30
Quantity Shipped this Shipment:      30
Quantity to be Filled:                0
Total Cost to Warehouse is:       60.00
Total Cost to the Customer:      120.00
Profit this shipment:             60.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  101                   30                 2.00                60.00               120.00
Your order was fully proccesesed, and shipped!

Order Traking num:                 1002
Quantity Ordered:                    20
Quantity Shipped this Shipment:      20
Quantity to be Filled:                0
Total Cost to Warehouse is:       40.00
Total Cost to the Customer:       80.00
Profit this shipment:             40.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  101                   20                 2.00                40.00                80.00
Your order was fully proccesesed, and shipped!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
2
              Order#    Quantity for shipment
                1001                       10


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
20
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1004                       20


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
30
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1005                       30


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
2
              Order#    Quantity for shipment
                1005                       30

                1004                       20

                1001                       10


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
60
What is the price per widget?
2
               Batch#    Quantity on hand:   Price Per widget:
                  102                  60                2.00


Order Traking num:                 1005
Quantity Ordered:                    30
Quantity Shipped this Shipment:      30
Quantity to be Filled:                0
Total Cost to Warehouse is:       60.00
Total Cost to the Customer:      120.00
Profit this shipment:             60.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  102                   30                 2.00                60.00               120.00
Your order was fully proccesesed, and shipped!

Order Traking num:                 1004
Quantity Ordered:                    20
Quantity Shipped this Shipment:      20
Quantity to be Filled:                0
Total Cost to Warehouse is:       40.00
Total Cost to the Customer:       80.00
Profit this shipment:             40.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  102                   20                 2.00                40.00                80.00
Your order was fully proccesesed, and shipped!

Order Traking num:                 1001
Quantity Ordered:                    10
Quantity Shipped this Shipment:      10
Quantity to be Filled:                0
Total Cost to Warehouse is:       20.00
Total Cost to the Customer:       40.00
Profit this shipment:             20.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  102                   10                 2.00                20.00                40.00
Your order was fully proccesesed, and shipped!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
2
 There are no outstanding orders, nothing to display

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!


*/

//3.Testing menu option 3.Accept a delivery : Functions acceptDelivery(InventoryStack & inventoryStackObj, OrderStack & orderStackObj)
/*
  
                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
10
What is the price per widget?
3
               Batch#    Quantity on hand:   Price Per widget:
                  101                  10                3.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
20
What is the price per widget?
3
               Batch#    Quantity on hand:   Price Per widget:
                  102                  20                3.00

                  101                  10                3.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
30
What is the price per widget?
4
               Batch#    Quantity on hand:   Price Per widget:
                  103                  30                4.00

                  102                  20                3.00

                  101                  10                3.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order
60

Order Traking num:                 1001
Quantity Ordered:                    60
Quantity Shipped this Shipment:      60
Quantity to be Filled:                0
Total Cost to Warehouse is:      210.00
Total Cost to the Customer:      420.00
Profit this shipment:            210.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  103                   30                 4.00               120.00               240.00
                  102                   20                 3.00                60.00               120.00
                  101                   10                 3.00                30.00                60.00
Your order was fully proccesesed, and shipped!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
10
What is the price per widget?
4
               Batch#    Quantity on hand:   Price Per widget:
                  104                  10                4.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
20
What is the price per widget?
5
               Batch#    Quantity on hand:   Price Per widget:
                  105                  20                5.00

                  104                  10                4.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
21
What is the price per widget?
3
               Batch#    Quantity on hand:   Price Per widget:
                  106                  21                3.00

                  105                  20                5.00

                  104                  10                4.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order
60

Backorder Message: Your order was partially filled, backorder Details:

Order Traking num:                 1002
Quantity Ordered:                    60
Quantity Shipped this Shipment:      51
Quantity to be Filled:                9
Total Cost to Warehouse is:      203.00
Total Cost to the Customer:      406.00
Profit this shipment:            203.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  106                   21                 3.00                63.00               126.00
                  105                   20                 5.00               100.00               200.00
                  104                   10                 4.00                40.00                80.00

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
20
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1003                       20


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
30
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1004                       30


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
50
What is the price per widget?
3
               Batch#    Quantity on hand:   Price Per widget:
                  107                  50                3.00


Order Traking num:                 1004
Quantity Ordered:                    30
Quantity Shipped this Shipment:      30
Quantity to be Filled:                0
Total Cost to Warehouse is:       90.00
Total Cost to the Customer:      180.00
Profit this shipment:             90.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  107                   30                 3.00                90.00               180.00
Your order was fully proccesesed, and shipped!

Order Traking num:                 1003
Quantity Ordered:                    20
Quantity Shipped this Shipment:      20
Quantity to be Filled:                0
Total Cost to Warehouse is:       60.00
Total Cost to the Customer:      120.00
Profit this shipment:             60.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  107                   20                 3.00                60.00               120.00
Your order was fully proccesesed, and shipped!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!

*/



//4.Testing menu option 4.Take an order, Functions: 

/*
                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
20
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1001                       20


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
30
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1002                       30


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
50
What is the price per widget?
3
               Batch#    Quantity on hand:   Price Per widget:
                  101                  50                3.00


Order Traking num:                 1002
Quantity Ordered:                    30
Quantity Shipped this Shipment:      30
Quantity to be Filled:                0
Total Cost to Warehouse is:       90.00
Total Cost to the Customer:      180.00
Profit this shipment:             90.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  101                   30                 3.00                90.00               180.00
Your order was fully proccesesed, and shipped!

Order Traking num:                 1001
Quantity Ordered:                    20
Quantity Shipped this Shipment:      20
Quantity to be Filled:                0
Total Cost to Warehouse is:       60.00
Total Cost to the Customer:      120.00
Profit this shipment:             60.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  101                   20                 3.00                60.00               120.00
Your order was fully proccesesed, and shipped!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
20
What is the price per widget?
3
               Batch#    Quantity on hand:   Price Per widget:
                  102                  20                3.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
40
What is the price per widget?
2
               Batch#    Quantity on hand:   Price Per widget:
                  103                  40                2.00

                  102                  20                3.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order
32

Order Traking num:                 1003
Quantity Ordered:                    32
Quantity Shipped this Shipment:      32
Quantity to be Filled:                0
Total Cost to Warehouse is:       64.00
Total Cost to the Customer:      128.00
Profit this shipment:             64.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  103                   32                 2.00                64.00               128.00
Your order was fully proccesesed, and shipped!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order
60

Backorder Message: Your order was partially filled, backorder Details:

Order Traking num:                 1004
Quantity Ordered:                    60
Quantity Shipped this Shipment:      28
Quantity to be Filled:               32
Total Cost to Warehouse is:       76.00
Total Cost to the Customer:      152.00
Profit this shipment:             76.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  103                    8                 2.00                16.00                32.00
                  102                   20                 3.00                60.00               120.00

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
30
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1005                       30


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
40
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1006                       40


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
2
              Order#    Quantity for shipment
                1006                       40

                1005                       30

                1004                       32


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
60
What is the price per widget?
3
               Batch#    Quantity on hand:   Price Per widget:
                  104                  60                3.00


Order Traking num:                 1006
Quantity Ordered:                    40
Quantity Shipped this Shipment:      40
Quantity to be Filled:                0
Total Cost to Warehouse is:      120.00
Total Cost to the Customer:      240.00
Profit this shipment:            120.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  104                   40                 3.00               120.00               240.00
Your order was fully proccesesed, and shipped!

Backorder Message: Your order was partially filled, backorder Details:

Order Traking num:                 1005
Quantity Ordered:                    30
Quantity Shipped this Shipment:      20
Quantity to be Filled:               10
Total Cost to Warehouse is:       60.00
Total Cost to the Customer:      120.00
Profit this shipment:             60.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  104                   20                 3.00                60.00               120.00

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
10
What is the price per widget?
2
               Batch#    Quantity on hand:   Price Per widget:
                  105                  10                2.00


Order Traking num:                 1005
Quantity Ordered:                    30
Quantity Shipped this Shipment:      10
Quantity to be Filled:                0
Total Cost to Warehouse is:       20.00
Total Cost to the Customer:       40.00
Profit this shipment:             20.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  105                   10                 2.00                20.00                40.00
Your order was fully proccesesed, and shipped!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!

*/


//5.5. Testing function void processOrder() as an individual.
/*
*A)Testing function with widgets in stock to fulfill or partly fulfill order

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
20
What is the price per widget?
3
               Batch#    Quantity on hand:   Price Per widget:
                  101                  20                3.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
40
What is the price per widget?
2
               Batch#    Quantity on hand:   Price Per widget:
                  102                  40                2.00

                  101                  20                3.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
5
What is the price per widget?
1
               Batch#    Quantity on hand:   Price Per widget:
                  103                   5                1.00

                  102                  40                2.00

                  101                  20                3.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order
50

Order Traking num:                 1001
Quantity Ordered:                    50
Quantity Shipped this Shipment:      50
Quantity to be Filled:                0
Total Cost to Warehouse is:      100.00
Total Cost to the Customer:      200.00
Profit this shipment:            100.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  103                    5                 1.00                 5.00                10.00
                  102                   40                 2.00                80.00               160.00
                  101                    5                 3.00                15.00                30.00
Your order was fully proccesesed, and shipped!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
1
               Batch#    Quantity on hand:   Price Per widget:
                  101                  15                3.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order
13

Order Traking num:                 1002
Quantity Ordered:                    13
Quantity Shipped this Shipment:      13
Quantity to be Filled:                0
Total Cost to Warehouse is:       39.00
Total Cost to the Customer:       78.00
Profit this shipment:             39.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  101                   13                 3.00                39.00                78.00
Your order was fully proccesesed, and shipped!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order
3

Backorder Message: Your order was partially filled, backorder Details:

Order Traking num:                 1003
Quantity Ordered:                     3
Quantity Shipped this Shipment:       2
Quantity to be Filled:                1
Total Cost to Warehouse is:        6.00
Total Cost to the Customer:       12.00
Profit this shipment:              6.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  101                    2                 3.00                 6.00                12.00

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!




 *B)Testing function with an order bigger than number of widgets in stock 
 * 
   
                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
20
What is the price per widget?
3
               Batch#    Quantity on hand:   Price Per widget:
                  101                  20                3.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
25
What is the price per widget?
4
               Batch#    Quantity on hand:   Price Per widget:
                  102                  25                4.00

                  101                  20                3.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
21
What is the price per widget?
3
               Batch#    Quantity on hand:   Price Per widget:
                  103                  21                3.00

                  102                  25                4.00

                  101                  20                3.00


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order
100

Backorder Message: Your order was partially filled, backorder Details:

Order Traking num:                 1001
Quantity Ordered:                   100
Quantity Shipped this Shipment:      66
Quantity to be Filled:               34
Total Cost to Warehouse is:      223.00
Total Cost to the Customer:      446.00
Profit this shipment:            223.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  103                   21                 3.00                63.00               126.00
                  102                   25                 4.00               100.00               200.00
                  101                   20                 3.00                60.00               120.00

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
5
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1002                        5


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
10
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1003                       10


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
300
What is the price per widget?
3
               Batch#    Quantity on hand:   Price Per widget:
                  104                 300                3.00


Order Traking num:                 1003
Quantity Ordered:                    10
Quantity Shipped this Shipment:      10
Quantity to be Filled:                0
Total Cost to Warehouse is:       30.00
Total Cost to the Customer:       60.00
Profit this shipment:             30.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  104                   10                 3.00                30.00                60.00
Your order was fully proccesesed, and shipped!

Order Traking num:                 1002
Quantity Ordered:                     5
Quantity Shipped this Shipment:       5
Quantity to be Filled:                0
Total Cost to Warehouse is:       15.00
Total Cost to the Customer:       30.00
Profit this shipment:             15.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  104                    5                 3.00                15.00                30.00
Your order was fully proccesesed, and shipped!

Order Traking num:                 1001
Quantity Ordered:                   100
Quantity Shipped this Shipment:      34
Quantity to be Filled:                0
Total Cost to Warehouse is:      102.00
Total Cost to the Customer:      204.00
Profit this shipment:            102.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  104                   34                 3.00               102.00               204.00
Your order was fully proccesesed, and shipped!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!



*C)Testing function with orders  and no available widgets

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
10
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1001                       10


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
30
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1002                       30


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
40
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1003                       40


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
50
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1004                       50


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
2
              Order#    Quantity for shipment
                1004                       50

                1003                       40

                1002                       30

                1001                       10


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!


  *D)Testing function with orders pending and inventory receiving stock
   

             
                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
30
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1001                       30


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
50
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1002                       50


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
10
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1003                       10


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
4
How many widgets would you like to order?
100
Inventory is out of stock, your order was saved and will be shipped as soon as possible
              Order#    Quantity for shipment
                1004                      100


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
2
              Order#    Quantity for shipment
                1004                      100

                1003                       10

                1002                       50

                1001                       30


                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
3
What size would you like the batch of widgets to be?(Positive integers only greater than 1)
200
What is the price per widget?
4
               Batch#    Quantity on hand:   Price Per widget:
                  101                 200                4.00


Order Traking num:                 1004
Quantity Ordered:                   100
Quantity Shipped this Shipment:     100
Quantity to be Filled:                0
Total Cost to Warehouse is:      400.00
Total Cost to the Customer:      800.00
Profit this shipment:            400.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  101                  100                 4.00               400.00               800.00
Your order was fully proccesesed, and shipped!

Order Traking num:                 1003
Quantity Ordered:                    10
Quantity Shipped this Shipment:      10
Quantity to be Filled:                0
Total Cost to Warehouse is:       40.00
Total Cost to the Customer:       80.00
Profit this shipment:             40.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  101                   10                 4.00                40.00                80.00
Your order was fully proccesesed, and shipped!

Order Traking num:                 1002
Quantity Ordered:                    50
Quantity Shipped this Shipment:      50
Quantity to be Filled:                0
Total Cost to Warehouse is:      200.00
Total Cost to the Customer:      400.00
Profit this shipment:            200.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  101                   50                 4.00               200.00               400.00
Your order was fully proccesesed, and shipped!

Order Traking num:                 1001
Quantity Ordered:                    30
Quantity Shipped this Shipment:      30
Quantity to be Filled:                0
Total Cost to Warehouse is:      120.00
Total Cost to the Customer:      240.00
Profit this shipment:            120.00


Shipment details
            Delivery#          Qty Shipped           Unit Price    Cost to Warehouse     Cost to Customer
                  101                   30                 4.00               120.00               240.00
Your order was fully proccesesed, and shipped!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!


C:\Users\Robin\Desktop\Scoala\Anul 2\SEM #2\CS 136\LABS\LAB 6\Debug\LAB 6.exe (process 29612) exited with code 0.
Press any key to close this window . . .
*/




//6.Testing option menu with wrong input
/*
                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
-1
Error! Please enter an option bellow!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
10
Error! Please enter an option bellow!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
robin
Error! Please enter an option bellow!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
%
Error! Please enter an option bellow!

                ***Waerehouse***

Please enter an option bellow
        1.Details of inventory on hand
        2.Deatails of outstanding oder
        3.Accept a delivery
        4.Take an order
        5.Quit!
*/