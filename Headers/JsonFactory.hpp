#ifndef JSON_FACTORY_H
#define JSON_FACTORY_H
#include <fstream>

#include "JsonCreator.hpp"

class Json;
class JsonFactory
{
public:
    static JsonFactory &get();
    Json *parse_value(const char *value) const;
    Json *parse_file(const char *_filename) const;

    void register_valid_json(const JsonCreator *rhs);

    const JsonCreator *get_creator(const String &_val) const;

    JsonFactory(JsonFactory const &) = delete;
    void operator=(JsonFactory const &) = delete;

private:
    /*Reads the entire file into a string, then returns the other parse_value method.
        THIS METHOD CLOSES THE FILE AFTER RECEIVING IT.
    */
    Json *parse_value(std::ifstream &ifs) const;

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