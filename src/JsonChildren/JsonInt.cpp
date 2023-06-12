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
const JsonType JsonInt::get_type() const { return JsonType::Integer; }

void JsonInt::log() const
{
    std::cout << this->get_as_str();
}

String JsonInt::get_as_str() const
{
    std::string temp = std::to_string(val);
    return temp.c_str();
}