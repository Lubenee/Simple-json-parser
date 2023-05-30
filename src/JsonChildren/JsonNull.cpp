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
    std::cout << "null";
}

const JsonType JsonNull::get_type() const { return JsonType::Null; }

Json *JsonNull::clone() const { return new JsonNull(); }
