#include "../includes/todoElement.h"

calendar::todoElement::todoElement(const unsigned long int &position, const std::string &dataRecord){
	this->position = position;
	this->dataRecord = dataRecord;
}

calendar::todoElement::todoElement(){
	this->position = 0;
	this->dataRecord = "NULL";
}

void calendar::todoElement::setPosition(const unsigned long& newPosition){
	this->position = newPosition;
}

void calendar::todoElement::setDataRecord(const std::string& newDataRecord){
	this->dataRecord = newDataRecord;
}

void calendar::todoElement::incrementPosition(){
	this->position++;
}

void calendar::todoElement::decrementPosition(){
	if(this->position > 1){
		this->position--;
	}
}

const unsigned long & calendar::todoElement::getPosition() const{
	return this->position;
}

const std::string & calendar::todoElement::getDataRecord() const{
	return this->dataRecord;
}





