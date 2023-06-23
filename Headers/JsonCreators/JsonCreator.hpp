#ifndef JSON_CREATOR_H
#define JSON_CREATOR_H

#include "Json.hpp"

class JsonCreator
{
public:
    /**
     * @brief Construct a new Json Creator object
     *
     * @param _val The creator's "identifier".
     */
    JsonCreator(const String &_val);

    /**
     * @brief Get the val object. The child creators attempt to
     * recognize what command is in the _obj string.
     *
     * @param _obj
     * @return true     They recognized a command.
     * @return false    They did not recognize a command.
     */
    virtual bool get_val(const String &_obj) const = 0;

    /**
     * @brief Attempt to create a new json object
     *
     * @param val       The value that's to be parsed.
     * @return Json*    The Value returned as a Json pointer.
     */
    virtual Json *create_json(const String &val) const = 0;
    virtual ~JsonCreator() = default;

protected:
    String val;
};

namespace JsonParse
{
    /**
     * @brief
     * Parses the passed Json value in the specified string, and modifies the
     * index to tell us where this particular value ends, or whether the value
     * was valid or not.
     *
     * EXAMPLE:
     * value = "key1": "value1"#, \n
     *         "key2": "value2",
     *
     * The returned string will be a new json element with string value: "value1".
     * The index will be set at the '#' symbol.
     *
     * \param[in]     value      Splits the passed value into a new Json element, until a comma delimiter is found.If the value contains a new list or object, it gets parsed later. If the list/object's brackets are missing, the index is set to npos.
     * \param[in]     index      The current index where we're located in the val string reference. When a new Json element is created, the index is set to that character's location.
     */
    String parse_value(const String &value, size_t &index);
} //! JsonParse

#endif //! JSON_CREATOR_H