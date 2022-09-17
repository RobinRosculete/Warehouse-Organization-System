#include "WidgetBatch.h"

//Pre:A widget has been initialized 
//Post:set the delivery traking Number, base traking number 100
void WidgetBatch:: setBatchTrakingNum(int batchTrakingNum) {
	const int baseTrakingNum = 100;
	this->batchTrakingNum = batchTrakingNum + baseTrakingNum; 
	
}//End setBatchTrakingNum()
