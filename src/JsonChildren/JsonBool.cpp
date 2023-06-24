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
String JsonBool::get_as_str() const
{
    return (val ? "true" : "false");
}

bool JsonBool::contains_recursive(const String &_value, const String &_curr_key, Vector<String> &keys) const
{
    if (_value == "true" && this->val == true)
    {
        keys.push_back(_curr_key);
        return true;
    }
    if (_value == "false" && this->val == false)
    {
        keys.push_back(_curr_key);
        return true;
    }
    return false;
}