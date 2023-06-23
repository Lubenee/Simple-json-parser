#include "JsonInt.hpp"

JsonInt::JsonInt() : val(0) {}
JsonInt::JsonInt(const int _val) : val(_val) {}
JsonInt::JsonInt(const JsonInt &rhs) : Json(rhs), val(rhs.val) {}
JsonInt &JsonInt::operator=(const JsonInt &rhs)
{
    if (this == &rhs)
        return *this;
    val = rhs.val;
    return *this;
}

Json *JsonInt::clone() const
{
    return new JsonInt(val);
}

void JsonInt::log() const
{
    std::cout << this->get_as_str();
}

bool JsonInt::contains(const String &_value) const
{
    int _val = 0;
    try
    {
        _val = std::stoi(_value.c_str());
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
    return _val == val;
}

String JsonInt::get_as_str() const
{
    std::string temp = std::to_string(val);
    return temp.c_str();
}