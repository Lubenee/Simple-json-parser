#include "FloatCreator.hpp"

FloatCreator::FloatCreator() : JsonCreator("Float") {}

Json *FloatCreator::create_json(const String &val) const
{
    return new JsonFloat(stof(val));
}

bool FloatCreator::get_val(const String &_obj) const
{
    return is_float(_obj);
}

bool FloatCreator::is_float(const String &val) const
{
    if (!val.includes('.'))
    {
        return false;
    }
    for (size_t i = 0; i < val.length(); ++i)
        if (!isdigit(val[i]) && val[i] != '-' && val[i] != '+' && val[i] != '.')
            return false;
    return true;
}

float FloatCreator::stof(const String &val) const
{
    return (::atof(val.c_str()));
}

static FloatCreator __;