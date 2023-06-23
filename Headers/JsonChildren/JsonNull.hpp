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

    bool contains(const String &_value) const override;

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

    ~JsonNull() = default;
};

#endif //! JSON_NULL_H