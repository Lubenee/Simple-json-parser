#include "JsonFloat.hpp"

JsonFloat::JsonFloat() : val(0) {}
JsonFloat::JsonFloat(const float _val) : val(_val) {}
JsonFloat::JsonFloat(const JsonFloat &rhs) : Json(rhs), val(rhs.val) {}
JsonFloat &JsonFloat::operator=(const JsonFloat &rhs)
{
    if (this == &rhs)
        return *this;
    val = rhs.val;
    return *this;
}

Json *JsonFloat::clone() const
{
    return new JsonFloat(val);
}

const JsonType JsonFloat::get_type() const { return JsonType::Floating; }

bool JsonFloat::contains(const float &_value) const
{
    return (_value == val ? true : false);
}

void JsonFloat::log() const
{
    std::cout << val;
}