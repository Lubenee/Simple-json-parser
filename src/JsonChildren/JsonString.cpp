#include "JsonString.hpp"

JsonString::JsonString() : val("") {}
JsonString::JsonString(const String _val) : val(_val) {}
JsonString::JsonString(const JsonString &rhs) : Json(rhs), val(rhs.val) {}
JsonString &JsonString::operator=(const JsonString &rhs)
{
    if (this == &rhs)
        return *this;
    val = rhs.val;
    return *this;
}

Json *JsonString::clone() const
{
    return new JsonString(val);
}

bool JsonString::contains_recursive(const String &_value, const String &_curr_key, Vector<String> &keys) const
{
    if (val.includes(_value))
    {
        keys.push_back(_curr_key);
        return true;
    }
    return false;
}

void JsonString::log() const
{
    std::cout << this->get_as_str();
}

String JsonString::get_as_str() const
{
    String temp;
    temp += "\"";
    temp += val;
    temp += "\"";
    return temp;
}
