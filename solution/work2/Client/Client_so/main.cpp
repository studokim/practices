#include "ValiDator.h"
#include <iostream>

int main()
{
    // Пример использования библиотеки
    RussianPassportValidator passportValidator;
    PhoneNumberValidator phoneValidator;
    CreditCardNumberValidator creditCardValidator;
    std::string passport;
    std::string phoneNumber;
    std::string creditCardNumber;
    bool flag = false;
    while (flag == false)
    {

        std::cout << "введите ваш паспорт: ";
        std::getline(std::cin, passport);
        if (passportValidator.validate(passport) == -1)
        {
            std::cout << "длина серии-номера не 10 цифр" << std::endl;
        }
        else if (passportValidator.validate(passport) == -2)
        {
            std::cout << "встречены нецифровые символы" << std::endl;
        }
        else
        {
            std::cout << "паспорт валиден" << std::endl;
            flag = true;
        }
    }
    std::cout << std::endl;
    flag = false;
    while (flag == false)
    {
        std::cout << "введите ваш номер телефона: ";
        std::getline(std::cin, phoneNumber);

        if (phoneValidator.validate(phoneNumber) == -1)
        {
            std::cout << "данные не соответствуют требованиям по размеру или формату" << std::endl;
        }
        else if (phoneValidator.validate(phoneNumber) == -2)
        {
            std::cout << "встречены нецифровые символы" << std::endl;
        }
        else if (phoneValidator.validate(phoneNumber) == -3)
        {
            std::cout << "неверное количество цифр" << std::endl;
        }
        else
        {
            std::cout << "номер телефона валиден" << std::endl;
            flag = true;
        }
    }
    std::cout << std::endl;
    flag = false;
    while (flag == false)
    {
        std::cout << "введите номер кредитной карты: ";
        std::getline(std::cin, creditCardNumber);
        if (creditCardValidator.validate(creditCardNumber) == -1)
        {
            std::cout << "встречены нецифровые символы" << std::endl;
        }
        else if (creditCardValidator.validate(creditCardNumber) == -2)
        {
            std::cout << "номер кредитной карты не действителен" << std::endl;
        }
        else
        {
            std::cout << "номер кредитной карты валиден" << std::endl;
            flag = true;
        }
    }
    return 0;
}