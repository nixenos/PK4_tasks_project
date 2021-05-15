#pragma once
#include <map>
#include <stdio.h>
#include <string>
#include <time.h>

namespace calendar {

#define MAX_YEAR_CAP 5000

/**
 * @brief typ wyliczeniowy obsługujący dzień tygodnia
 *
 */
typedef enum weekDayModel {
    Mon = 0,
    Tue = 1,
    Wed = 2,
    Thu = 3,
    Fri = 4,
    Sat = 5,
    Sun = 6
} weekDayModel;

/**
 * @brief typ wyliczeniowy obługujący miesiące
 */
typedef enum monthModel {
    Jan = 0,
    Feb = 1,
    Mar = 2,
    Apr = 3,
    May = 4,
    Jun = 5,
    Jul = 6,
    Aug = 7,
    Sep = 8,
    Oct = 9,
    Nov = 10,
    Dec = 11
} monthModel;

/**
 * @brief klasa obsługująca datę
 */
class date {
  private:
    unsigned short day;     /**< dzień miesiąca */
    weekDayModel weekDay;   /**< dzień tygodnia */
    monthModel month;       /**< miesiąc */
    unsigned long int year; /**< rok */

    /**
     * @brief oblicza dzień tygodnia na podstawie dnia, miesiąca i roku,
     * korzystając z reguły Zellera
     *
     * @param qDay dzień miesiąca
     * @param qMonth miesiąc
     * @param qYear rok
     *
     * @return obliczony dzień tygodnia
     */
    weekDayModel calculateWeekDay(const unsigned short &qDay,
                                  const monthModel &qMonth,
                                  const unsigned long int &qYear) const;

  public:
    /**
     * @brief konstruktor bezargumentowy, przypisuje obiektowi aktualną datę
     */
    date();

    /**
     * @brief konstruktor trójargumentowy, przypisuje obiektowi podaną datę
     */
    date(const unsigned short &day, const monthModel &month,
         const unsigned long int &year);

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
    void setYear(const unsigned long int &newYear);

    /**
     * @brief ustawia bieżącą datę
     */
    void setCurrentDate();

    void incrementMonth();

    void decrementMonth();

    bool operator==(const date &right);

    bool operator!=(const date &right);

    std::string stringify();

    bool operator>(const date &right);

    bool operator<(const date &right);

    bool operator>=(const date &right);

    bool operator<=(const date &right);
};
} // namespace calendar
