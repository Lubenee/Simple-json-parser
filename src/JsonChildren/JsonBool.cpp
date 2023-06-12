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
const JsonType JsonBool::get_type() const { return JsonType::Boolean; }
void JsonBool::log() const
{
    std::cout << this->get_as_str();
}

String JsonBool::get_as_str() const
{
    return (val ? "true" : "false");
}