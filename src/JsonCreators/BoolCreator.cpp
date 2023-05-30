#include "BoolCreator.hpp"

BoolCreator::BoolCreator() : JsonCreator("Bool") {}

Json *BoolCreator::create_json(const String &val) const
{
    return new JsonBool(stob(val));
}

bool BoolCreator::get_val(const String &_obj) const
{
    return is_boolean(_obj);
}

bool BoolCreator::is_boolean(const String &val) const
{
    return (val == "true" || val == "false" ? true : false);
}

bool BoolCreator::stob(const String &val) const
{
    return (val == "true" ? true : false);
}

static BoolCreator __;