#include "JsonNull.hpp"

JsonNull::JsonNull() {}
JsonNull &JsonNull::operator=(const JsonNull &rhs)
{
    if (this == &rhs)
        return *this;
    return *this;
}

bool JsonNull::contains_recursive(const String &_value, const String &_curr_key, Vector<String> &keys) const
{
    if (_value == "null")
    {
        keys.push_back(_curr_key);
        return true;
    }
    return false;
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
