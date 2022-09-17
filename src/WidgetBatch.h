#ifndef WIDGETBATCH_H
#define WIDGETBATCH_H

class WidgetBatch{
public: 
   WidgetBatch(): widgetPrice(0),widgetQuatninty(0),batchTrakingNum(0){}

   void setBatchTrakingNum(int batchTrakingNum);


   //Pre:A widget has been initialized 
   //Post:Set the price of the widget
   void setWidgetPrice(float widgetPrice) { this->widgetPrice = widgetPrice; }

   //Pre:A widget has been initialized 
   //Post:Set the quantity of widgets
   void setWidgetBatchQuantity(int widgetQuantity) { this->widgetQuatninty = widgetQuantity; }

   

   //Pre:A widget has been initialized 
   //Post:return the widget price
   float getWidgetPrice() const{ return this->widgetPrice; }

   //Pre:A widget has been initialized 
   //Post:return the delivery traking Number
   int getBatchTrakingNum()const { return this->batchTrakingNum; }

    //Pre:A widget has been initialized 
    //Post: return the quantity of widgets
   int getWidgetBatchQuantity()const { return this->widgetQuatninty; }
 
private: 
float widgetPrice;
int widgetQuatninty;
int batchTrakingNum;
};

#endif WIDGETBATCH_H
