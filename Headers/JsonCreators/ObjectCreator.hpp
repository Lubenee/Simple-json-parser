#if !defined(OBJECT_CREATOR_H)
#define OBJECT_CREATOR_H

#include "JsonCreator.hpp"
#include "JsonObject.hpp"

class ObjectCreator : public JsonCreator
{
public:
    ObjectCreator();
    Json *create_json(const String &val) const override;
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
