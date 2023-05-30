#include "JsonFactory.hpp"

JsonFactory &JsonFactory::get()
{
    static JsonFactory instance;
    return instance;
}

void JsonFactory::register_valid_json(const JsonCreator *rhs)
{
    creators[count++] = rhs;
}

Json *JsonFactory::parse_value(const char *value) const
{
    const char *nonWhitespaceChar = value;
    while (std::isspace(*nonWhitespaceChar))
        ++nonWhitespaceChar;
    String val(value);

    const JsonCreator *crt = get_creator(val);
    return crt->create_json(val);
}

const JsonCreator *JsonFactory::get_creator(const String &_val) const
{
    for (size_t i = 0; i < count; ++i)
        if (creators[i]->get_val(_val))
            return creators[i];
    return nullptr;
}