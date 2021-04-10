#include "../includes/date.h"

calendar::date::date(){
	this->setCurrentDate();
}

calendar::date::date(const unsigned short& day, const calendar::monthModel& month, const unsigned long& year){
	/**
	 * @TODO
	 */
}

calendar::weekDayModel calendar::date::calculateWeekDay(const unsigned short& qDay, const calendar::monthModel& qMonth, const unsigned long& qYear) const {
	int calcWeekDay = 0;
	unsigned int D = qYear%10000 + qYear%1000;
	unsigned int C = qYear%100 + qYear%10;
	calcWeekDay = qDay + ((13*(qMonth+2)%12)/5) + D + (D/4) + (C/4) - (2*C);
	calcWeekDay = (calcWeekDay + 1)%7;
	calendar::weekDayModel result = static_cast<calendar::weekDayModel>(calcWeekDay);
	return result;
}

void calendar::date::setCurrentDate(){
	time_t currentTime = time(0); // get current time to time_t struct
	struct tm tstruct;
	char buffer[80];
	tstruct = *localtime(&currentTime);
	strftime(buffer, sizeof(buffer), "%Y%m%d", &tstruct);
	std::string tempDateContainer(buffer);

	unsigned long int newYear = atoi(tempDateContainer.substr(0, 3).c_str());
	unsigned short int newMonth = atoi(tempDateContainer.substr(4,5).c_str());
	unsigned short int newDay = atoi(tempDateContainer.substr(6,7).c_str());

	this->year = newYear;
	this->month = static_cast<calendar::monthModel>(newMonth);
	this->day = static_cast<calendar::weekDayModel>(newDay);
	this->weekDay = this->calculateWeekDay(this->day, this->month, this->year);
}

void calendar::date::setDay(const unsigned short& newDay){
	if (newDay > 0 && newDay <= 31){
		if (this->month < 8 && this->month%2){
			this->day = newDay;
		}
		else if (this->month > 7 && !this->month%2){
			this->day = newDay;
		}
		else if (this->month == 2 && newDay <= 29){
			if (!this->year%4){
				this->day = newDay;
			}
			else{
				if (newDay < 29){
					this->day = newDay;
				}
				else {
					// error
				}
			}
		}
		else if (newDay < 31){
			this->day = newDay;
		}
		else {
			// error
		}
	}
	else{
		// error
	}
}


