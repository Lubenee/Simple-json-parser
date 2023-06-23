#if !defined(OBJECT_CREATOR_H)
#define OBJECT_CREATOR_H

#include "JsonCreator.hpp"
#include "JsonObject.hpp"

class ObjectCreator : public JsonCreator
{
public:
    /**
     * @brief Construct a new Object Creator object.
     *          This constructor initializes the JsonCreator's
     *           constructor with "Object" name.
     */
    ObjectCreator();
    /**
     * @brief Create a json object
     *
     * @param val
     * @return Json*
     */
    Json *create_json(const String &val) const override;
    /**
     * @brief Get the val object
     *  Returns true if the _obj String starts with a '{' symbol.
     *
     * @param _obj
     */
    bool get_val(const String &_obj) const override;
    ~ObjectCreator() = default;

private:
    /**
     * @brief
     * Removes the square brackets from the passed object value.
     */
    String remove_curly_braces(const String &val) const;
    String parse_obj_key(const String &value, size_t &index) const;
    Json *parse_object(const String &value) const;
};

#endif // OBJECT_CREATOR_H
