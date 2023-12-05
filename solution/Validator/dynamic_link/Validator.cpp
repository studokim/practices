// Validator.cpp

#include "Validator.h"

bool Validator::digitsCheck(const std::string &input) const
{
    for (char digit : input)
    {
        if (!isdigit(digit))
            return false; // Недопустимые символы
    }
    return true;
}

std::string Validator::removeSpaces(const std::string &input) const
{
    std::string result = input;
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

// 0 - Корректный номер
// -2 - Недопустимые символы
// -3 - Некорректная длинна
int RussianPassportValidator::validate(const std::string &input) const
{
    std::string clean_passport = removeSpaces(input);

    if (!digitsCheck(clean_passport))
        return -2; // Недопустимые символы

    if (clean_passport.size() != 10)
        return -3; // Неверная длинна

    return 0; // Корректный номер паспорта
}

// 0 - Корректный номер
// -1 - Некорректный номер телефона
// -2 - Недопустимые символы
// -3 - Некорректная длинна
int PhoneNumberValidator::validate(const std::string &input) const
{
    if (input[0] == '+')
    {
        std::string clean_phone_number = removeSpaces(input.substr(1));

        if (!digitsCheck(clean_phone_number))
            return -2; // Недопустимые символы

        if (clean_phone_number.size() >= 6 && clean_phone_number.size() <= 14)
            return 0; // Корректный номер телефона
        else
            return -3; // Некорректная длинна номера
    }
    else
    {
        return -1; // Некорректный номер
    }
}

bool CreditCardNumberValidator::hasAnyPrefix(const std::string &input, const std::unordered_set<std::string> &validPrefixes) const
{
    for (const std::string &prefix : validPrefixes)
    {
        if (input.find(prefix) == 0)
            return true;
    }
    return false;
}

// 0 - Корректный номер
// -1 - Некорректный номер карты
// -2 - Недопустимые символ
int CreditCardNumberValidator::validate(const std::string &input) const
{
    std::string clean_card_number = removeSpaces(input);

    if (!digitsCheck(clean_card_number))
        return -2; // Недопустимые символы

    if (!hasAnyPrefix(clean_card_number, validPrefixes))
        return -1; // Некорректный префикс карты

    int sum = 0;
    bool doubleDigit = false;

    for (int i = clean_card_number.size() - 1; i >= 0; --i)
    {
        int digit = clean_card_number[i] - '0';

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

    if (sum % 10 == 0)
        return 0; // Некорректный номер карты

    return -1; // Корректный номер карты
}