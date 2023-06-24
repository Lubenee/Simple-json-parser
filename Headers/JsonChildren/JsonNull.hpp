#ifndef JSON_NULL_H
#define JSON_NULL_H

#include "Json.hpp"

class JsonNull : public Json
{
public:
    /**
        @brief
            Default constructor.
    */
    JsonNull();
    JsonNull &operator=(const JsonNull &rhs);

    /**
        @brief
        Logs "Null".
    */
    void log() const override;
    /**
        @brief
            returns "Null".
    */
    String get_as_str() const override;

    /**
        @brief
            Clone method.
    */
    Json *clone() const override;

    bool contains_recursive(const String &_value, const String &_curr_key, Vector<String> &keys) const override;

    ~JsonNull() = default;
};

#endif //! JSON_NULL_H