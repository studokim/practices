#pragma once

#include <regex>
#include <array>
using namespace std;

class Validator
{
protected:
    void removeSpaces(string& str);
public:
    virtual bool validate(string str) = 0;
};

void Validator::removeSpaces(string& str)
{
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}


class RussianPassportValidator : Validator
{
public:
    bool validate(string passport) override;
};

bool RussianPassportValidator::validate(string passport) 
{
    regex pattern("^(\\d{4})\\-?(\\d{6})$");
    removeSpaces(passport);
    return regex_match(passport, pattern);
}


class PhoneNumberValidator : Validator
{
public:
    bool validate(string phone) override;
};

bool PhoneNumberValidator::validate(string phone)
{
    removeSpaces(phone);
    regex pattern("^\\+(?:[0-9]){6,14}[0-9]$");
    return regex_match(phone, pattern);
}


class CreditCardNumberValidator: Validator
{
    array<string, 10> cardPrefixes = {"1800", "2", "3", "4", "51", "52", "53", "54", "55", "6011"};

    bool isValidPrefix(string card);
public:
    bool validate(string card) override;
};

bool CreditCardNumberValidator::validate(string card)
{
    removeSpaces(card);
    regex pattern("^\\d{13,16}$");
    if(!regex_match(card, pattern)) return false;
    if(!isValidPrefix(card)) return false;

    int sum=0;
    for(int i = card.length() - 1; i>=0; i--)
    {
        int digit = card[i] - '0';
        if((card.length()-i)%2==0)
        {
            digit *=2;
            if(digit > 9) digit-=9;
        }        
        sum += digit;
    }
    return sum %10==0;
}

bool CreditCardNumberValidator::isValidPrefix(string card)
{
    for(string prefix : cardPrefixes)
        if(card.find(prefix) == 0) return true;
    
    return false;
}