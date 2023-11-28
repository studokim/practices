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

#endif 