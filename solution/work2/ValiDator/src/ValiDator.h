#pragma once
#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <algorithm>
#include <iostream>

class Validator
{
public:
    virtual int validate(const std::string &data) const = 0;
    virtual ~Validator() = default;
    // Функция очистки от лишних символов
    static std::string cleanData(const std::string &data)
    {
        std::string cleanedData = data;
        cleanedData.erase(std::remove_if(cleanedData.begin(), cleanedData.end(), ::isspace), cleanedData.end());
        return cleanedData;
    }
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
private:
    static const std::string validPrefixes[];

public:
    int validate(const std::string &data) const override;
};

const std::string CreditCardNumberValidator::validPrefixes[] = {"1800", "2", "3", "4", "51", "52", "53", "54", "55", "6011"};

#endif
