// Validator.h 

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

class RussianPassportValidator : public Validator
{
public:
    int validate(const std::string &input) const override;
};

class PhoneNumberValidator : public Validator
{
public:
    int validate(const std::string &input) const override;
};

class CreditCardNumberValidator : public Validator
{
private:
    std::unordered_set<std::string> validPrefixes = {"1800", "2", "3", "4", "51", "52", "53", "54",
                                                     "55", "6011"};

    bool hasAnyPrefix(const std::string &input, const std::unordered_set<std::string> &validPrefixes) const;

public:
    int validate(const std::string &input) const override;
};