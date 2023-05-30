#if !defined(BOOL_CREATOR_H)
#define BOOL_CREATOR_H

#include "JsonCreator.hpp"
#include "JsonBool.hpp"

class BoolCreator : public JsonCreator
{
public:
    BoolCreator();
    Json *create_json(const String &val) const override;
    bool get_val(const String &_obj) const;
    ~BoolCreator() = default;

private:
    /**
     * @brief
     * Checks if the passed string reference is a boolean.
     * \retval TRUE   The passed string reference can be parsed as a boolean.
     * \retval FALSE  The passed string reference can not be parsed as a boolean.
     */
    bool is_boolean(const String &val) const;
    /**
     * @brief
     * String to bool. Makes a bool from a string value.
     * \param[in]   val
     * \retval bool val
     */
    bool stob(const String &val) const;
};
#endif // BOOL_CREATOR_H
