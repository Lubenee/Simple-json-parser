#include "JsonNull.hpp"

JsonNull::JsonNull() {}
JsonNull::JsonNull(const String &_key) {}
JsonNull::JsonNull(const JsonNull &rhs) {}
JsonNull &JsonNull::operator=(const JsonNull &rhs)
{
    if (this == &rhs)
        return *this;
    return *this;
}

bool JsonNull::contains(const String &_value) const
{
    return (_value == "null");
}

void JsonNull::log() const
{
    std::cout << this->get_as_str();
}

String JsonNull::get_as_str() const
{
    return "null";
}

const JsonType JsonNull::get_type() const
{
    return JsonType::Null;
}

Json *JsonNull::clone() const { return new JsonNull(); }
