#if !defined(INT_CREATOR_H)
#define INT_CREATOR_H

#include "JsonCreator.hpp"
#include "JsonInt.hpp"

class IntCreator : public JsonCreator
{
public:
    /**
     * @brief Construct a new Int Creator object.
     *          This constructor initializes the JsonCreator's
     *           constructor with "Integer" name.
     */
    IntCreator();
    /**
     * @brief Create a json object
     *
     * @param val
     * @return Json*
     */
    Json *create_json(const String &val) const override;
    /**
     * @brief Get the val object
     *      Returns true if _obj is a valid integer value.
     *
     * @param _obj
     */
    bool get_val(const String &_obj) const override;
    ~IntCreator() = default;

private:
    /**
     * @brief
     * String to int. Makes an int from a string value.
     * \param[in]   val
     * \retval int val
     */
    int stoi(const String &val) const;

    /**
     * @brief
     * Checks if the passed string reference is an integer.
     * \retval TRUE   The passed string reference can be parsed as an integer.
     * \retval FALSE  The passed string reference can not be parsed as an integer.
     */
    bool is_int(const String &val) const;
};

#endif //! INT_CREATOR_H