#include "StringCreator.hpp"

StringCreator::StringCreator() : JsonCreator("String") {}

Json *StringCreator::create_json(const String &val) const
{
    return new JsonString(remove_quotes(val));
}

bool StringCreator::get_val(const String &_obj) const
{
    return is_str(_obj);
}

String StringCreator::remove_quotes(const String &val) const
{
    size_t first_brace = val.first_index_of('"') + 1;
    size_t last_brace = val.last_index_of('"');
    String temp = val.substr(first_brace, last_brace - first_brace);
    return temp;
}

bool StringCreator::is_str(const String &val) const
{
    if (val[0] == '"' && val[val.length() - 1] == '"')
        return true;
    return false;
}

static StringCreator __;