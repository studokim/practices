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

class RussianPassportValidator : Validator
{
public:
    bool validate(string passport) override;
};

class PhoneNumberValidator : Validator
{
public:
    bool validate(string phone) override;
};

class CreditCardNumberValidator: Validator
{
    array<string, 10> cardPrefixes = {"1800", "2", "3", "4", "51", "52", "53", "54", "55", "6011"};

    bool isValidPrefix(string card);
public:
    bool validate(string card) override;
};


