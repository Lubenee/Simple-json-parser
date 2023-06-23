#ifndef NULL_CREATOR_H
#define NULL_CREATOR_H

#include "JsonCreator.hpp"
#include "JsonNull.hpp"

class NullCreator : public JsonCreator
{
public:
    /**
     * @brief Construct a new Null Creator object.
     *          This constructor initializes the JsonCreator's
     *           constructor with "Null" name.
     */
    NullCreator();
    /**
     * @brief Create a json object
     *
     * @param val
     * @return Json*
     */
    Json *create_json(const String &val) const override;
    /**
     * @brief Get the val object
     *  Returns true if _obj is "null".
     *
     * @param _obj
     */
    bool get_val(const String &_obj) const override;
    ~NullCreator() = default;
};

#endif //! NULL_CREATOR_H