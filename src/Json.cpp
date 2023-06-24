#include "Json.hpp"
size_t Json::format_spaces = 0;

const bool Json::search(const String &key) const
{
    return false;
}

Vector<String> Json::contains(const String &_value) const
{
    Vector<String> keys;
    contains_recursive(_value, "", keys);
    return keys;
}