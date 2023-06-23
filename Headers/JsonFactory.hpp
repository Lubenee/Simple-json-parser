#ifndef JSON_FACTORY_H
#define JSON_FACTORY_H
#include <fstream>

#include "JsonCreator.hpp"

class Json;
class JsonFactory
{
public:
    /**
     * @brief Polymorphic factory for json.
     * @return JsonFactory& The instance.
     */
    static JsonFactory &get();

    /**
     * @brief Attempts to parse the passed value and returns a new Json element pointer(depending on the value).
     *
     * @param value
     * @return Json*
     */
    Json *parse_value(const char *value) const;

    /**
     * @brief Attempts to parse the contents of the passed file.
     * Returns a new Json element pointer.
     *
     * @param _filename
     * @return Json*
     */
    Json *parse_file(const char *_filename) const;

    /**
     * @brief A method that allows different Json Creators to register themselves.
     */
    void register_valid_json(const JsonCreator *rhs);

    /**
     * @brief Get the creator object depending on the passed string.
     *
     * @param _val
     * @return const JsonCreator*
     */
    const JsonCreator *get_creator(const String &_val) const;

    /**
     * @brief Disallow construction of a new Json Factory object
     */
    JsonFactory(JsonFactory const &) = delete;
    /**
     * @brief Disallow copying of the Json factory.
     *
     */
    void operator=(JsonFactory const &) = delete;

private:
    /** @brief
    Reads the entire file into a string, then returns the other parse_value method.
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
    const JsonCreator *creators[8];
    size_t count;

    JsonFactory() {}
    ~JsonFactory() {}
};

#endif //! JSON_FACTORY_H