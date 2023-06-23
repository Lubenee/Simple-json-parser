#if !defined(LIST_CREATOR_H)
#define LIST_CREATOR_H

#include "JsonCreator.hpp"
#include "JsonList.hpp"

class ListCreator : public JsonCreator
{
public:
    /**
     * @brief Construct a new List Creator object.
     *          This constructor initializes the JsonCreator's
     *           constructor with "List" name.
     */
    ListCreator();
    /**
     * @brief Create a json object
     *
     * @param val
     * @return Json*
     */
    Json *create_json(const String &val) const override;
    /**
     * @brief Get the val object
     *  Returns true if the _obj String starts with a '[' symbol.
     *
     * @param _obj
     * @return true
     * @return false
     */
    bool get_val(const String &_obj) const override;

    ~ListCreator() = default;

private:
    /**
     * @brief
     * Removes the square brackets from the passed string value.
     */
    String remove_square_braces(const String &val) const;

    Json *parse_list(const String &val) const;
};

#endif // LIST_CREATOR_H
