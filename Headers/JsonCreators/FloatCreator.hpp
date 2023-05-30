#if !defined(FLOAT_CREATOR_H)
#define FLOAT_CREATOR_H

#include "JsonCreator.hpp"
#include "JsonFloat.hpp"

class FloatCreator : public JsonCreator
{
public:
    FloatCreator();
    Json *create_json(const String &val) const override;
    bool get_val(const String &_obj) const override;
    ~FloatCreator() = default;

private:
    /**
     * @brief
     * Checks if the passed string reference is a floating point.
     * \retval TRUE   The passed string reference can be parsed as a double.
     * \retval FALSE  The passed string reference can not be parsed as a double.
     */
    bool is_float(const String &val) const;

    /**
     * @brief
     * String to float. Makes a float from a string value.
     * \param[in]   val
     * \retval float val
     */
    float stof(const String &val) const;
};

#endif //! INT_CREATOR_H