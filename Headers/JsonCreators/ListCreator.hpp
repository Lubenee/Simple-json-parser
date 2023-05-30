#if !defined(LIST_CREATOR_H)
#define LIST_CREATOR_H

#include "JsonCreator.hpp"
#include "JsonList.hpp"

class ListCreator : public JsonCreator
{
public:
    ListCreator();
    Json *create_json(const String &val) const override;
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
