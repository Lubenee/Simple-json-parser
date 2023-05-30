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

bool JsonInt::contains(const int &_value) const
{
    return (val == _value ? true : false);
}

void JsonInt::log() const
{
    std::cout << val;
}