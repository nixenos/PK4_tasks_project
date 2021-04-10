#include "../includes/todo.h"

todo::todoElement::todoElement(const unsigned long int &position, const std::string &dataRecord){
	this->position = position;
	this->dataRecord = dataRecord;
}

todo::todoElement::todoElement(){
	this->position = 0;
	this->dataRecord = "NULL";
}

void todo::todoElement::setPosition(const unsigned long& newPosition){
	this->position = newPosition;
}

void todo::todoElement::setDataRecord(const std::string& newDataRecord){
	this->dataRecord = newDataRecord;
}

void todo::todoElement::incrementPosition(){
	this->position++;
}

void todo::todoElement::decrementPosition(){
	if(this->position > 1){
		this->position--;
	}
}

const unsigned long & todo::todoElement::getPosition() const{
	return this->position;
}

const std::string & todo::todoElement::getDataRecord() const{
	return this->dataRecord;
}





