#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ValiDator.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::checkInputs);
    connect(ui->textEdit_2, &QTextEdit::textChanged, this, &MainWindow::checkInputs);
    connect(ui->textEdit_3, &QTextEdit::textChanged, this, &MainWindow::checkInputs);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::validatePassport(const QString& qData) {
    RussianPassportValidator passportValidator;
    std::string data = qData.toStdString();
    int validateResult = passportValidator.validate(data);

    if (validateResult == -1) {
        ui->textEdit->setStyleSheet("background-color: lightcoral;");
        ui->label_4->setText(ui->label_4->text()+"Ошибка в валидации паспорта:\n");
        ui->label_4->setText(ui->label_4->text()+"количество цифр в паспорте не равно 10\n");
        ui->label_4->setText(ui->label_4->text()+"пример: 12 34 567890\n\n");
        return false;
    } else if (validateResult == -2) {
        ui->textEdit->setStyleSheet("background-color: lightcoral;");
        ui->label_4->setText(ui->label_4->text()+"Ошибка в валидации паспорта:\n");
        ui->label_4->setText(ui->label_4->text()+"встречены нецифровые символы\n");
        ui->label_4->setText(ui->label_4->text()+"пример: 12 34 567890\n\n");
        return false;
    } else {
        ui->textEdit->setStyleSheet("");
        return true;
    }
}

bool MainWindow::validatePhoneNumber(const QString& qData) {
    PhoneNumberValidator phoneValidator;
    std::string data = qData.toStdString();
    int validateResult = phoneValidator.validate(data);

    if (validateResult == -1) {
        ui->textEdit_2->setStyleSheet("background-color: lightcoral;");
        ui->label_4->setText(ui->label_4->text()+"Ошибка в валидации номера телефона:\n");
        ui->label_4->setText(ui->label_4->text()+"номер телефона не соответствует требованию международного формата\n");
        ui->label_4->setText(ui->label_4->text()+"пример: +7 800 555 35 35\n\n");
        return false;
    } else if (validateResult == -2) {
        ui->textEdit_2->setStyleSheet("background-color: lightcoral;");
        ui->label_4->setText(ui->label_4->text()+"Ошибка в валидации номера телефона:\n");
        ui->label_4->setText(ui->label_4->text()+"встречены нецифровые символы после первого символа +\n");
        ui->label_4->setText(ui->label_4->text()+"пример: +7 800 555 35 35\n\n");
        return false;
    } else if (validateResult == -3) {
        ui->textEdit_2->setStyleSheet("background-color: lightcoral;");
        ui->label_4->setText(ui->label_4->text()+"Ошибка в валидации номера телефона:\n");
        ui->label_4->setText(ui->label_4->text()+"количество цифр неверное\n\n");
        ui->label_4->setText(ui->label_4->text()+"пример: +7 800 555 35 35\n\n");
        return false;
    } else {
        ui->textEdit_2->setStyleSheet("");
        return true;
    }
}

bool MainWindow::validateCreditCardNumber(const QString& qData) {
    CreditCardNumberValidator cardValidator;
    std::string data = qData.toStdString();
    int validateResult = cardValidator.validate(data);

    if (validateResult == -1) {
        ui->textEdit_3->setStyleSheet("background-color: lightcoral;");
        ui->label_4->setText(ui->label_4->text()+"Ошибка в валидации кредитной карты:\n");
        ui->label_4->setText(ui->label_4->text()+"номер кредитной карты не существует\n");
        ui->label_4->setText(ui->label_4->text()+"пример: 4624 7482 3324 9780\n\n");
        return false;
    } else if (validateResult == -2) {
        ui->textEdit_3->setStyleSheet("background-color: lightcoral;");
        ui->label_4->setText(ui->label_4->text()+"Ошибка в валидации кредитной карты:\n");
        ui->label_4->setText(ui->label_4->text()+"встречены нецифровые символы\n");
        ui->label_4->setText(ui->label_4->text()+"пример: 4624 7482 3324 9780\n\n");
        return false;
    } else {
        ui->textEdit_3->setStyleSheet("");
        return true;
    }
}
void MainWindow::checkInputs()
{
    bool input_1 = !ui->textEdit->toPlainText().isEmpty();
    bool input_2 = !ui->textEdit_2->toPlainText().isEmpty();
    bool input_3 = !ui->textEdit_3->toPlainText().isEmpty();
    bool allInputsFilled = input_1 && input_2 && input_3;
    ui->pushButton->setEnabled(allInputsFilled);
}

//4624 7482 3324 9780
void MainWindow::on_pushButton_clicked()
{
    ui->label_4->setText(NULL);
    QString passportData = ui->textEdit->toPlainText();
    QString phoneData = ui->textEdit_2->toPlainText();
    QString cardData = ui->textEdit_3->toPlainText();

    bool passportValid = validatePassport(passportData);
    bool phoneValid = validatePhoneNumber(phoneData);
    bool cardValid = validateCreditCardNumber(cardData);

    if (passportValid && phoneValid && cardValid)
        ui->label_4->setText("Проверка прошла успешно");


}
