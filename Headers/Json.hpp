#ifndef JSON_H
#define JSON_H

#include <iostream>
#include <exception>
#include "String.hpp"
#include "Vector.hpp"

#define Quote "\""

enum class JsonType
{
    Null,
    Boolean,
    Integer,
    Floating,
    String,
    List,
    Object,
};

class Json
{
public:
    Json() = default;
    Json(const Json &rhs) = default;

    virtual void log() const = 0;
    virtual String get_as_str() const = 0;

    virtual Json *clone() const = 0;
    virtual const JsonType get_type() const = 0;
    virtual void log_search_results() const {}

    virtual const bool search(const String &key) const;
    virtual bool contains(const String &_value) const { return false; }

    virtual ~Json() = default;

    virtual bool log_space() const { return false; }

protected:
    static size_t format_spaces;
};

#endif //! JSON_H