#ifndef JSON_FACTORY_H
#define JSON_FACTORY_H

#include "JsonCreator.hpp"

class Json;
class JsonFactory
{
public:
    static JsonFactory &get();
    Json *parse_value(const char *value) const;
    void register_valid_json(const JsonCreator *rhs);

    const JsonCreator *get_creator(const String &_val) const;

    JsonFactory(JsonFactory const &) = delete;
    void operator=(JsonFactory const &) = delete;

private:
    /*
    EXPECTED VALID CREATORS:
        NULL
        BOOL
        INT
        FLOAT
        STRING
        LIST
        OBJECT
    */
    const JsonCreator *creators[7];
    size_t count;

    JsonFactory() {}
    ~JsonFactory() {}
};

#endif //! JSON_FACTORY_H