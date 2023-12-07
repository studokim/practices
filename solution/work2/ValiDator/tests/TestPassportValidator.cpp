#include "../src/ValiDator.h"
#include <cassert>

int main()
{
    RussianPassportValidator passportValidator;

    // Пример валидного номера паспорта
    std::string validPassport = "12 34 567890";

    int validationResult = passportValidator.validate(validPassport);

    assert(validationResult == 0 && "Тест не прошел для валидного паспорта");

    // Пример номера паспорта с нецифровыми символами
    std::string nonNumericPassport = "A2 34 567890";

    validationResult = passportValidator.validate(nonNumericPassport);

    assert(validationResult == -2 && "Тест не прошел для номера паспорта с нецифровыми символами");

    // Пример номера паспорта c неверной длиной
    std::string shortPassport = "12 34 5678";

    validationResult = passportValidator.validate(shortPassport);

    assert(validationResult == -1 && "Тест не прошел для номера паспорта c неверной длиной");

    return 0;
}
