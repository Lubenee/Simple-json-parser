#include "JsonFactory.hpp"

JsonCreator::JsonCreator(const String &_val) : val(_val)
{
    JsonFactory::get().register_valid_json(this);
}
