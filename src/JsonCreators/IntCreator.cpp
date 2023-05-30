#include "IntCreator.hpp"

IntCreator::IntCreator() : JsonCreator("Int") {}

Json *IntCreator::create_json(const String &val) const
{
    return new JsonInt(stoi(val));
}

bool IntCreator::get_val(const String &_obj) const
{
    return is_int(_obj);
}

int IntCreator::stoi(const String &val) const
{
    return ::atoi(val.c_str());
}

bool IntCreator::is_int(const String &val) const
{
    for (size_t i = 0; i < val.length(); ++i)
        if (!isdigit(val[i]) && val[i] != '-' && val[i] != '+')
            return false;
    return true;
}

static IntCreator __;