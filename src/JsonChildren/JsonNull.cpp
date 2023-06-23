#include "JsonNull.hpp"

JsonNull::JsonNull() {}
JsonNull &JsonNull::operator=(const JsonNull &rhs)
{
    if (this == &rhs)
        return *this;
    return *this;
}

bool JsonNull::contains(const String &_value) const
{
    return (_value == "null");
}

void JsonNull::log() const
{
    std::cout << this->get_as_str();
}

String JsonNull::get_as_str() const
{
    return "null";
}

Json *JsonNull::clone() const { return new JsonNull(); }
