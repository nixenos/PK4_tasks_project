#pragma once
#include "date.h"
#include <string>

namespace calendar {

typedef enum repeatCycle { Daily, Weekly, Monthly, Annually, None } repeatCycle;

class event {
  private:
    date evDate;
    std::string evName;
    repeatCycle evRepeat;
    std::string evDescription;

  public:
    /**
     * @brief konstruktor bezargumentowy, tworzy obiekt z datą 1.01.2012, nazwą
     * NULL i bez powtarzania
     */
    event();

    /**
     * @brief konstruktor trójargumentowy, tworzy obiekt o podanych wartościach
     *
     * @param newDate data wydarzenia
     * @param newName nazwa wydarzenia
     * @param newRepeat powtarzanie wydarzenia
     */
    event(const date &newDate, const std::string &newName,
          const std::string &newEvDescription, const repeatCycle &newRepeat);

    /**
     * @brief pobiera datę wydarzenia
     *
     * @return data wydarzenia
     */
    date getEvDate() const noexcept;

    /**
     * @brief ustawia datę wydarzenia
     *
     * @param newDate nowa data do ustawienia
     */
    void setEvDate(const date &newDate);

    /**
     * @brief pobiera nazwę wydarzenia
     *
     * @return nazwa wydarzenia
     */
    std::string getEvName() const noexcept;

    /**
     * @brief ustawia nazwę wydarzenia
     *
     * @param newEvName nowa nazwa wydarzenia
     */
    void setEvName(const std::string &newEvName);

    /**
     * @brief pobiera cykl powtarzania
     *
     * @return cykl powtarzania
     */
    repeatCycle getEvRepeat() const noexcept;

    /**
     * @brief ustawia nowy cykl powtarzania
     *
     * @param newEvRepeat nowy cykl powtarzania
     */
    virtual void setEvRepeat(const repeatCycle &newEvRepeat);

    /**
     * pobiera opis wydarzenia
     *
     * @return opis wydarzenia
     */
    std::string getEvDescription() const noexcept;

    /**
     * @brief ustawia opis wydarzenia
     *
     * @param newEvDesription nowy opis wydarzenia
     */
    void setEvDescription(const std::string &newEvDesription);

    /**
     * @brief pobiera odpowiednie dane dla każdego z elementów i przetwarza je w
     * std::string wyświetlany w GUI aplikacji
     *
     * @return opis wydarzenia
     */
    virtual std::string stringifyEvent() const noexcept;

    virtual std::string exportData() const noexcept;
};
} // namespace calendar
