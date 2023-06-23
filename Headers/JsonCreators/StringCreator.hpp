#if !defined(STRING_CREATOR_H)
#define STRING_CREATOR_H

#include "JsonCreator.hpp"
#include "JsonString.hpp"

class StringCreator : public JsonCreator
{
public:
    /**
     * @brief Construct a new String Creator object.
     *          This constructor initializes the JsonCreator's
     *           constructor with "String" name.
     */
    StringCreator();
    /**
     * @brief Create a json object
     *
     * @param val
     * @return Json*
     */
    Json *create_json(const String &val) const override;
    /**
     * @brief Get the val object
     *  Returns true if _obj is a string surrounded with quotes.
     * @param _obj
     */
    bool get_val(const String &_obj) const override;
    ~StringCreator() = default;

private:
    /**
     * @brief
     * Checks if the passed string reference is enclosed with quotes '"', and is therefore a valid key or string value.
     * \retval TRUE   The passed string reference is enclosed with quotes.
     * \retval FALSE  The passed string reference is not enclosed with quotes.
     */
    bool is_str(const String &val) const;
    /**
     * @brief
     * Removes the square brackets from the passed key/string value.
     */
    String remove_quotes(const String &val) const;
};

#endif //! STRING_CREATOR_H