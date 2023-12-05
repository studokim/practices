﻿// Validator.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_set>

class Validator
{
protected:
    virtual bool digitsCheck(const std::string &input) const;
    virtual std::string removeSpaces(const std::string &input) const;

public:
    virtual int validate(const std::string &input) const = 0;
};

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

// 0 - Корректный номер паспорта
// -2 - Недопустимые символы
// -3 - Некорректная длинна
class RussianPassportValidator : public Validator
{
public:
    int validate(const std::string &input) const override
    {
        std::string clean_passport = removeSpaces(input);

        if (!digitsCheck(clean_passport))
            return -2; // Недопустимые символы

        if (clean_passport.size() != 10)
            return -3; // Неверная длинна

        return 0; // Корректный номер паспорта
    }
};

// 0 - Корректный номер
// -1 - Некорректный номер телефона
// -2 - Недопустимые символы
// -3 - Некорректная длинна
class PhoneNumberValidator : public Validator
{
public:
    int validate(const std::string &input) const override
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
};

// 0 - Корректный номер
// -1 - Некорректный номер карты
// -2 - Недопустимые символы
class CreditCardNumberValidator : public Validator
{
    std::unordered_set<std::string> validPrefixes = {"1800", "2", "3", "4", "51", "52",
                                                     "53", "54", "55", "6011"};

    bool hasAnyPrefix(const std::string &input, const std::unordered_set<std::string> &validPrefixes) const
    {
        for (const std::string &prefix : validPrefixes)
        {
            if (input.find(prefix) == 0)
                return true;
        }
        return false;
    }

public:
    int validate(const std::string &input) const override
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
};