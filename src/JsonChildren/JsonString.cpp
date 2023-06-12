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

const JsonType JsonString::get_type() const { return JsonType::String; }

bool JsonString::contains(const String &_value) const
{
    return val.includes(_value);
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
