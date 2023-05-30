#include "NullCreator.hpp"

NullCreator::NullCreator() : JsonCreator("Null") {}

Json *NullCreator::create_json(const String &val) const
{
    return new JsonNull();
}

bool NullCreator::get_val(const String &_obj) const
{
    return (_obj == "null");
}

static NullCreator __;