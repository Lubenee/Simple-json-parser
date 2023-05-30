#ifndef JSON_H
#define JSON_H

#include <iostream>
#include <exception>
#include "String.hpp"
#include "Vector.hpp"

#define Quote '\"'

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
    virtual Json *clone() const = 0;
    virtual const JsonType get_type() const = 0;
    virtual const bool search(const String &key) const; // list

    virtual bool contains(const String &_value) const { return false; } // list
    virtual bool contains(const int &_value) const { return false; }    // list
    virtual bool contains(const float &_value) const { return false; }  // list
    virtual bool contains(const bool &_value) const { return false; }   // list

    virtual ~Json() = default;

protected:
    static size_t format_spaces;
};

#endif //! JSON_H