#include "ValiDator.h"
#include <iostream>

int main()
{

    PhoneNumberValidator phoneValidator;

    std::string phoneNumber = "+7-999-523-86-50";

    if (phoneValidator.validate(phoneNumber) == -1)
    {
        return -1;
    }
    else if (phoneValidator.validate(phoneNumber) == -2)
    {
        return -2;
    }
    else if (phoneValidator.validate(phoneNumber) == -3)
    {
        return -3;
    }
    else
    {
        return 0;
    }
}