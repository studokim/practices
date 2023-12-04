#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <stdexcept>
#include <algorithm>
#include <iostream>

class Validator
{
public:
    virtual int validate(const std::string &data) const = 0;
    virtual ~Validator() = default;
};

class RussianPassportValidator : public Validator
{
public:
    int validate(const std::string &data) const override;
};

class PhoneNumberValidator : public Validator
{
public:
    int validate(const std::string &data) const override;
};

class CreditCardNumberValidator : public Validator
{
public:
    int validate(const std::string &data) const override;
};

// Функция очистки от лишних символов
std::string cleanData(const std::string &data)
{
    std::string cleanedData = data;
    cleanedData.erase(std::remove_if(cleanedData.begin(), cleanedData.end(), ::isspace), cleanedData.end());
    return cleanedData;
}
// Метод валидации для Российского паспорта.
// Проверяет валидность данных.
// Возвращает:
// -1, если размер данных не равен 10,
// -2, если встречены нецифровые символы,
//  0, если паспорт валиден.
int RussianPassportValidator::validate(const std::string &data) const
{
    // Очищаем данные
    std::string cleanedData = cleanData(data);

    // Проверяем размер очищенных данных
    if (cleanedData.size() != 10)
    {
        return -1;
    }

    // Проверяем, что все символы - цифры
    for (char digit : cleanedData)
    {
        if (!isdigit(digit))
        {
            return -2;
        }
    }

    // Паспорт валиден
    return 0;
}

// Метод валидации для номера телефона.
// Проверяет валидность данных.
// Возвращает:
// -1, если данные не соответствуют требованию международоного формата,
// -2, если встречены нецифровые символы после первого символа "+",
// -3, если количество цифр не соответствует диапазону,
//  0, если номер телефона валиден.
int PhoneNumberValidator::validate(const std::string &data) const
{
    int digitCount = 0;

    // Очищаем данные
    std::string cleanedData = cleanData(data);

    // Проверяем наличие первого символа "+"
    if (cleanedData[0] != '+')
    {
        return -1;
    }
    else
    {
        // Проверяем отсутствие нецифровых символов
        for (size_t i = 1; i < cleanedData.size(); ++i)
        {
            if (isdigit(cleanedData[i]))
            {
                digitCount++;
            }
            else
            {
                return -2;
            }
        }
    }

    // Проверяем, что количество цифр находится в допустимом диапазоне
    if (digitCount < 6 || digitCount > 14)
    {
        return -3;
    }

    // Номер телефона валиден
    return 0;
}

// Метод валидации для номера кредитной карты.
// Применяет алгоритм Луна и проверку префиксов для определения валидности номера кредитной карты.
// Возвращает:
// -1, если номер кредитной карты не проходит алгоритм Луна,
// -2, если встречены нецифровые символы,
//  0, если номер кредитной карты валиден.
int CreditCardNumberValidator::validate(const std::string &data) const
{
    // Очищаем данные
    std::string cleanedData = cleanData(data);

    // Проверяем, что все символы - цифры
    for (char digit : cleanedData)
    {
        if (!isdigit(digit))
        {
            return -2;
        }
    }

    // Проверяем префиксы
    bool hasValidPrefix = false;
    for (const std::string &prefix : {"1800", "2", "3", "4", "51", "52", "53", "54", "55", "6011"})
    {
        if (cleanedData.find(prefix) == 0)
        {
            hasValidPrefix = true;
            break;
        }
    }

    if (!hasValidPrefix)
    {
        return -1;
    }

    int sum = 0;
    bool doubleDigit = false;

    // Применяем алгоритм Луна для подсчета суммы цифр номера кредитной карты
    for (int i = cleanedData.size() - 1; i >= 0; --i)
    {
        int digit = cleanedData[i] - '0';

        if (doubleDigit)
        {
            digit *= 2;

            if (digit > 9)
            {
                digit = digit - 9;
            }
        }

        sum += digit;
        doubleDigit = !doubleDigit;
    }

    // Проверяем, что сумма делится на 10
    if (sum % 10 != 0)
    {
        return -1;
    }

    // Номер кредитной карты валиден
    return 0;
}
#endif
