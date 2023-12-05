import libvalidator

def handle_code(code):
    if code == 0:
        return "Корректный номер!"
    elif code == -1:
        return "Ошибка 1: Такой номер не существует."
    elif code == -2:
        return "Ошибка 2: В номере присутствуют недопустимые символы."
    elif code == -3:
        return "Ошибка 3: Недопустимая длина номера."
    else:
        return "Неизвестная ошибка."

passport_validator = libvalidator.RussianPassportValidator()
number = input("Введите номер паспорта:")
result = passport_validator.validate(number)
print(handle_code(result))

phone_validator = libvalidator.PhoneNumberValidator()
number = input("Введите номер телефона:")
result = phone_validator.validate(number)
print(handle_code(result))

card_validator = libvalidator.CreditCardNumberValidator()
number = input("Введите номер кредитной карты:")
result = card_validator.validate(number)
print(handle_code(result))
