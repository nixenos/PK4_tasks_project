#include "../includes/eventBirthdayModel.h"

calendar::eventBirthday::eventBirthday(){

}

calendar::eventBirthday::eventBirthday(const calendar::date& newDate, const std::string& newName, const calendar::repeatCycle& newRepeat, const std::string& newFirstName, const std::string& newLastName, const calendar::date& newBirthDate){

}

calendar::date calendar::eventBirthday::getBirthDate() const noexcept{
	return this->birthDate;
}

void calendar::eventBirthday::setBirthDate(const calendar::date& newBirthDate){
	this->birthDate = newBirthDate;
}

std::pair<std::string, std::string> calendar::eventBirthday::getPersonalData() const noexcept{
	return std::make_pair(this->firstName, this->lastName);
}

void calendar::eventBirthday::setPersonalData(const std::pair<std::string, std::string>& newPersonalData){
	this->firstName = newPersonalData.first;
	this->lastName = newPersonalData.second;
}

void calendar::eventBirthday::setEvRepeat(const calendar::repeatCycle &newEvRepeat){
	if (newEvRepeat == Annually){
		event::setEvRepeat(newEvRepeat);
	}
	else{

	}

}
