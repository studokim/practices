// ValiDator.h
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
    // Метод валидации для Российского паспорта.
    // Очищает входные данные от пробелов и проверяет их размер.
    // Возвращает:
    // -1, если длина серии-номера не равен 10,
    // -2, если встречены нецифровые символы,
    //  0, если паспорт валиден.
    int validate(const std::string &data) const override
    {
        // Очищаем данные от пробелов
        std::string cleanedData = data;
        cleanedData.erase(std::remove_if(cleanedData.begin(), cleanedData.end(), ::isspace), cleanedData.end());

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
};

class PhoneNumberValidator : public Validator
{
public:
    // Метод валидации для номера телефона.
    // Очищает входные данные от пробелов и знаков "-" и проверяет их размер.
    // Также проверяет, что первый символ - "+" и общее количество цифр в допустимом диапазоне.
    // Возвращает:
    // -1, если данные не соответствуют требованиям по размеру или формату,
    // -2, если встречены нецифровые символы после первого символа "+",
    // -3, если количество цифр не соответствует диапазону,
    //  0, если номер телефона валиден.
    int validate(const std::string &data) const override
    {
        // Очищаем данные от пробелов
        std::string cleanedData = data;
        cleanedData.erase(std::remove_if(cleanedData.begin(), cleanedData.end(), ::isspace), cleanedData.end());

        // Удаляем знаки "-"
        cleanedData.erase(std::remove(cleanedData.begin(), cleanedData.end(), '-'), cleanedData.end());

        // Проверяем размер очищенных данных и наличие первого символа "+"
        if (cleanedData.size() < 7 || cleanedData.size() > 15 || cleanedData[0] != '+')
        {
            return -1;
        }

        int digitCount = 0;

        // Подсчитываем количество цифр, игнорируя пробелы и знаки "-"
        for (size_t i = 1; i < cleanedData.size(); ++i)
        {
            if (isdigit(cleanedData[i]))
            {
                digitCount++;
            }
            else if ((cleanedData[i] == ' ' || cleanedData[i] == '-') && (i + 1 < cleanedData.size()) && isdigit(cleanedData[i + 1]))
            {
                digitCount++;
                i++;
            }
            else
            {
                return -2;
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
};

class CreditCardNumberValidator : public Validator
{
public:
    // Метод валидации для номера кредитной карты.
    // Очищает входные данные от пробелов и проверяет, что все символы - цифры.
    // Применяет алгоритм Луна для проверки валидности номера кредитной карты.
    // Возвращает:
    // -1, если встречены нецифровые символы,
    // -2, если номер кредитной карты не проходит алгоритм Луна,
    //  0, если номер кредитной карты валиден.
    int validate(const std::string &data) const override
    {
        // Очищаем данные от пробелов
        std::string cleanedData = data;
        cleanedData.erase(std::remove_if(cleanedData.begin(), cleanedData.end(), ::isspace), cleanedData.end());

        // Проверяем, что все символы - цифры
        for (char digit : cleanedData)
        {
            if (digit < '0' || digit > '9')
            {
                return -1;
            }
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
            return -2;
        }

        // Номер кредитной карты валиден
        return 0;
    }
};

#endif // VALIDATOR_H
