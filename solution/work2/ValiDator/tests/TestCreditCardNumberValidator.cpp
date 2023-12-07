#include "../src/ValiDator.h"
#include <cassert>

int main()
{
    CreditCardNumberValidator creditCardValidator;

    // Пример валидного номера кредитной карты
    std::string validCreditCardNumber = "4624 7482 3324 9780";

    int validationResult = creditCardValidator.validate(validCreditCardNumber);

    assert(validationResult == 0 && "Тест не прошел для валидного номера кредитной карты");

    // Пример номера с нецифровыми символами
    std::string nonNumericCreditCardNumber = "4F24-7482-3324-9780";

    validationResult = creditCardValidator.validate(nonNumericCreditCardNumber);

    assert(validationResult == -2 && "Тест не прошел для номера с нецифровыми символами");

    // Пример номера, несуществующей карты
    std::string invalidCreditCardNumber = "5024 7482 3324 9781";

    validationResult = creditCardValidator.validate(invalidCreditCardNumber);

    assert(validationResult == -1 && "Тест не прошел для невалидного номера кредитной карты");

    return 0;
}
