#include "JsonBool.hpp"

JsonBool::JsonBool() : val(false) {}
JsonBool::JsonBool(bool _val) : val(_val) {}
JsonBool::JsonBool(const JsonBool &rhs) : Json(rhs), val(rhs.val) {}
JsonBool &JsonBool::operator=(const JsonBool &rhs)
{
    if (this == &rhs)
        return *this;
    val = rhs.val;
    return *this;
}

Json *JsonBool::clone() const { return new JsonBool(val); }
void JsonBool::log() const
{
    std::cout << this->get_as_str();
}

bool JsonBool::contains(const String &_value) const
{
    bool _val = false, valid = false;
    if (_value == "true")
    {
        _val = true;
        valid = true;
    }
    if (_value == "false")
    {
        _val = false;
        valid = true;
    }
    return (_val == val);
}

String JsonBool::get_as_str() const
{
    return (val ? "true" : "false");
}