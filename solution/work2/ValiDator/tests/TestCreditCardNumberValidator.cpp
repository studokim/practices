#include "ValiDator.h"
#include <iostream>

int main()
{

    CreditCardNumberValidator creditCardValidator;

    std::string creditCardNumber = "4624 7482 3324 9780";

    if (creditCardValidator.validate(creditCardNumber) == -1)
    {
        return -1;
    }
    else if (creditCardValidator.validate(creditCardNumber) == -2)
    {
        return -2;
    }
    else
    {
        return 0;
    }
}