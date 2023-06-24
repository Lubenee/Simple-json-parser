#if !defined(JSON_BOOL_H)
#define JSON_BOOL_H

#include "Json.hpp"

/**
    @brief
        Publicly inherits the Json class.
*/
class JsonBool : public Json
{
public:
    /**
        @brief
            Default constructor.
    */
    JsonBool();

    /**
        @brief
            Sets the object's value to the passed boolean.
    */
    JsonBool(bool _val);

    /**
        @brief
            Default copy constructor.
    */
    JsonBool(const JsonBool &rhs);

    JsonBool &operator=(const JsonBool &rhs);

    /**
        @brief
            Clone method.
    */
    Json *clone() const override;

    /**
        @brief
            Logs the current boolean value.
    */
    void log() const override;
    /**
        @brief
            Returns the boolean value as a string.
    */
    String get_as_str() const override;
    bool contains_recursive(const String &_value, const String &_curr_key, Vector<String> &keys) const override;

    ~JsonBool() = default;

private:
    bool val;
};

#endif // JSON_BOOL_H
