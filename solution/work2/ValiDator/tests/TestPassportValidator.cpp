#include "ValiDator.h"
#include <iostream>

int main()
{

    RussianPassportValidator passportValidator;

    std::string passport = "1234567890";

    if (passportValidator.validate(passport) == -1)
    {
        return -1;
    }
    else if (passportValidator.validate(passport) == -2)
    {
        return -2;
    }
    else
    {
        return 0;
    }
}