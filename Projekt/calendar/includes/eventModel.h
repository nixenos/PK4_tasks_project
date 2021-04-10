#pragma once
#include <string>
#include "date.h"

namespace calendar{

typedef enum repeatCycle {Daily, Weekly, Monthly, Annually} repeatCycle;

	class event{
	private:
		date evDate;
		std::string evName;
		repeatCycle evRepeat;

	};
}
