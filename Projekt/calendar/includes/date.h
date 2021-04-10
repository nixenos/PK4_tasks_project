#pragma once
#include <map>
#include <stdio.h>
#include <time.h>
#include <string>

namespace calendar{

	/**
	 * @brief typ wyliczeniowy obsługujący dzień tygodnia
	 *
	*/
	typedef enum weekDayModel {Mon, Tue, Wed, Thu, Fri, Sat, Sun} weekDayModel;

	/**
	 * @brief typ wyliczeniowy obługujący miesiące
	 */
	typedef enum monthModel {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec} monthModel;

	/**
	 * @brief klasa obsługująca datę
	 */
	class date{
	private:
		unsigned short day; /**< dzień miesiąca */
		weekDayModel weekDay; /**< dzień tygodnia */
		monthModel month; /**< miesiąc */
		unsigned long int year; /**< rok */

		/**
		 * @brief oblicza dzień tygodnia na podstawie dnia, miesiąca i roku, korzystając z reguły Zellera
		 *
		 * @param qDay dzień miesiąca
		 * @param qMonth miesiąc
		 * @param qYear rok
		 *
		 * @return obliczony dzień tygodnia
		 */
		weekDayModel calculateWeekDay(const unsigned short &qDay, const monthModel &qMonth, const unsigned long int &qYear) const;

	public:

		/**
		 * @brief konstruktor bezargumentowy, przypisuje obiektowi aktualną datę
		 */
		date();

		/**
		 * @brief konstruktor trójargumentowy, przypisuje obiektowi podaną datę
		 */
		date(const unsigned short &day, const monthModel &month, const unsigned long int &year);

		/**
		 * @brief pobiera dzień miesiąca
		 *
		 * @return dzień miesiąca
		 */
		const unsigned short getDay() const;

		/**
		 * @brief ustawia dzień miesiąca
		 *
		 * @param newDay nowy dzień miesiąca
		 */
		void setDay(const unsigned short &newDay);

		/**
		 * @brief pobiera dzień tygodnia
		 *
		 * @return dzień tygodnia
		 */
		const weekDayModel getWeekDay() const;

		/**
		 * @brief pobiera miesiąc
		 *
		 * @return miesiąc
		 */
		const monthModel getMonth() const;

		/**
		 * @brief ustawia miesiąc
		 *
		 * @param newMonth nowy miesiąc do ustawienia
		 */
		void setMonth(const monthModel &newMonth);

		/**
		 * @brief pobiera rok
		 *
		 * @return rok
		 */
		const unsigned long int getYear() const;

		/**
		 * @brief ustawia rok
		 *
		 * @param newYear nowy rok
		 */
		void setYear(unsigned long int &newYear);

		/**
		 * @brief ustawia bieżącą datę
		 */
		void setCurrentDate();
	};
}
