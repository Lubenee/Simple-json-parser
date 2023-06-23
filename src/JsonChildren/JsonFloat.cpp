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

void JsonFloat::log() const
{
    std::cout << this->get_as_str();
}

bool JsonFloat::contains(const String &_value) const
{
    float _val = 0.0f;
    try
    {
        _val = std::stof(_value.c_str());
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
    return (_val == val);
}

String JsonFloat::get_as_str() const
{
    std::string temp = std::to_string(val);
    return temp.c_str();
}