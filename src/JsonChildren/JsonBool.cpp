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

bool JsonBool::contains(const bool &_value) const
{
    return (_value == val);
}

Json *JsonBool::clone() const { return new JsonBool(val); }
const JsonType JsonBool::get_type() const { return JsonType::Boolean; }
void JsonBool::log() const
{
    std::cout << std::boolalpha << val;
}