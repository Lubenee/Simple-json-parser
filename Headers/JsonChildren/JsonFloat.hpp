#if !defined(JSON_FLOAT_H)
#define JSON_FLOAT_H

#include "Json.hpp"
#include <string.h>

class JsonFloat : public Json
{
public:
    /**
        @brief
            Default constructor.
    */
    JsonFloat();
    /**
        @brief
            Sets the element's float value to the passed value.
    */
    JsonFloat(const float _val);
    /**
        @brief
            Default copy constructor.
    */
    JsonFloat(const JsonFloat &rhs);
    JsonFloat &operator=(const JsonFloat &rhs);

    /**
        @brief Clone method.
    */
    Json *clone() const override;

    /**
        @brief
            Logs the current float value.
    */
    void log() const override;
    /**
        @brief
            Returns the current float value as a string.
    */
    String get_as_str() const override;
    bool contains_recursive(const String &_value, const String &_curr_key, Vector<String> &keys) const override;

    ~JsonFloat() = default;

private:
    float val;
};

#endif // JSON_FLOAT_H
