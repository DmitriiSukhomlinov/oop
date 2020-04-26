#include "Base.h"

namespace oop {

Printable::~Printable() {}

Named::Named(const std::string& _name) 
    : name(_name) {}

Named::~Named() {}

std::string Named::getInfo() const {
    return "Name: " + name + ", Additional info: " + getAdditionaInfo();
}

std::string Named::getAdditionaInfo() const {
    return "No additional info.";
}

}