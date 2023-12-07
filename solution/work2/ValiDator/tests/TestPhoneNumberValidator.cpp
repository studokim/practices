#include "../src/ValiDator.h"
#include <cassert>

int main()
{
    PhoneNumberValidator phoneValidator;

    // Пример валидного телефонного номера
    std::string validPhoneNumber = "+7 999 523 86 50";

    int validationResult = phoneValidator.validate(validPhoneNumber);

    assert(validationResult == 0 && "Тест не прошел для валидного номера телефона");

    // Пример телефонного номера неверного формата
    std::string nonFormatPhoneNumber = "7-999-523-86-50";

    validationResult = phoneValidator.validate(nonFormatPhoneNumber);

    assert(validationResult == -1 && "Тест не прошел для номера телефона немеждународного формата");

    // Пример телефонного номера с нецифровыми символами после "+"
    std::string nonNumericAfterPlusPhoneNumber = "+7 999 52A 86 50";

    validationResult = phoneValidator.validate(nonNumericAfterPlusPhoneNumber);

    assert(validationResult == -2 && "Тест не прошел для номера с нецифровыми символами после первого символа +");

    // Пример телефонного номера с неверной длиной
    std::string shortPhoneNumber = "+7 99 52";

    validationResult = phoneValidator.validate(shortPhoneNumber);

    assert(validationResult == -3 && "Тест не прошел для телефонного номера с неверной длиной");

    return 0;
}
