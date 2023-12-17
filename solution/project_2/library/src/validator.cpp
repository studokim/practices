#include "validator.h"

void Validator::removeSpaces(string& str)
{
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}

bool RussianPassportValidator::validate(string passport) 
{
    regex pattern("^(\\d{4})\\-?(\\d{6})$");
    removeSpaces(passport);
    return regex_match(passport, pattern);
}

bool PhoneNumberValidator::validate(string phone)
{
    removeSpaces(phone);
    regex pattern("^\\+(?:[0-9]){6,14}[0-9]$");
    return regex_match(phone, pattern);
}

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