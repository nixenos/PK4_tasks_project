#pragma once
#include "eventModel.h"

namespace calendar{
	class eventHoliday : public event{
	private:
		date evBegin;
		date evEnd;

	public:

		/**
		 * @brief konstruktor bezargumentowy, tworzy pusty obiekt
		 */
		eventHoliday();

		/**
		 * @brief konstrukot wieloargumentowy, tworzący pełny obiekt klasy eventHoliday
		 */
		eventHoliday(const date &newDate, const std::string &newName, const repeatCycle &newRepeat,
					 const date &newEvBegin, const date &newEvEnd);

		/**
		 * @brief pobiera początek trwania wydarzenia
		 *
		 * @return początek trwania wydarzenia
		 */
		date getEvBegin() const noexcept;

		/**
		 * @brief ustawia początek trwania wydarzenia
		 *
		 * @param newEvBegin nowy początek
		 */
		void setEvBegin(const date &newEvBegin);

		/**
		 * @brief pobiera koniec trwania wydarzenia
		 *
		 * @return koniec trwania wydarzenia
		 */
		date getEvEnd() const noexcept;

		/**
		 * @brief ustawia koniec trwania wydarzenia
		 *
		 * @param newEvEnd nowy koniec
		 */
		void setEvEnd(const date &newEvEnd);
	};
}
