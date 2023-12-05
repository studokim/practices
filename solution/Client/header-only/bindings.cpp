#include <pybind11/pybind11.h>
#include "Validator.h"

namespace py = pybind11;

PYBIND11_MODULE(libvalidator, m) {
    py::class_<Validator>(m, "Validator");
    py::class_<RussianPassportValidator, Validator>(m, "RussianPassportValidator")
        .def(py::init<>())
        .def("validate", &RussianPassportValidator::validate);
    py::class_<PhoneNumberValidator, Validator>(m, "PhoneNumberValidator")
        .def(py::init<>())
        .def("validate", &PhoneNumberValidator::validate);
    py::class_<CreditCardNumberValidator, Validator>(m, "CreditCardNumberValidator")
        .def(py::init<>())
        .def("validate", &CreditCardNumberValidator::validate);
}

