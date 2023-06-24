#ifndef JSON_H
#define JSON_H

#include <iostream>
#include <exception>
#include "String.hpp"
#include "Vector.hpp"

#define Quote "\""

/**
 * @brief Base class for all JSON Operations.
 */
class Json
{

public:
    /**
     * @brief Construct a new Json object
     */
    Json() = default;
    /**
     * @brief Construct a new Json object
     * Default copy constructor.
     * @param rhs
     */
    Json(const Json &rhs) = default;
    /**
        @brief
            Parses the current json element into a string and logs it.
            Pure virtual method. Each child must redefine for it's own type.
    */
    virtual void log() const = 0;

    /**
        @brief
            Returns a new string containing the element's value.
    */
    virtual String get_as_str() const = 0;

    /**
        @brief
            Clone method.
    */
    virtual Json *clone() const = 0;

    /**
        @brief
            This method logs all the elements that were found after using the search method.
            If nothing is found, it does nothing.
    */
    virtual void log_search_results() const {}
    virtual void log_contains_results() const {}

    /**
        @brief
           Allows the user to search for an element, whose key corresponds to the passed value.
           Only the List and Object children are required to predefine this method, since only
           they hold element keys.
        \retval TRUE One or more elements have been found that include the passed key.
        \retval FALSE No element includes the passed key.
    */
    virtual const bool search(const String &key) const;

    /**
     * @brief Checks if the JSON structure contains a specific value and retrieves the keys leading to that value.
     *
     * This method recursively traverses the JSON structure and searches for a specific value. It returns a vector
     * containing the keys that lead to the found value. The keys are represented as strings, where each key represents
     * a path within the JSON structure.
     *
     * @param value The value to search for within the JSON structure.
     * @return A vector of strings representing the keys leading to the found value. If the value is not found, an empty
     *         vector is returned.
     *
     */
    Vector<String> contains(const String &_value) const;
    /**
        @brief
            Creates a new Json element on the specified path, with the specified value.
            If the path is invalid, the JSON state remains unchanged. The depth parameter is not to be used.
            \param [in] PATH     Recursive path, separated by '/'. The last arg is the new element's key.
            \param [in] VALUE    Valid Json value
    */
    virtual void create(const String &_path, const String &new_value, int depth = 0) {}
    /**
        @brief
            Replaces an existing element's value with the new value passed.
            If the path is invalid, the JSON state remains unchanged. The depth parameter is not to be used.

                EXAMPLE: Key1/Key2/Key3 "new_value"
                        Key3's value will be set to a Json String with value "new_value".

            \param [in] PATH     Recursive path, separated by '/'. The last arg is the new element's key.
            \param [in] VALUE    Valid Json value
    */
    virtual void set(const String &_path, const String &new_value, int depth = 0) {}
    /**
        @brief
            Erases the last key that is given in the path variable.

                EXAMPLE: Key1/Key2
                        The Key2 element will be deleted.
        \param [in] PATH    Recursive path, separated by '/'.
    */
    virtual void erase(const String &path, int depth = 0) {}

    /**
        @brief
            Moves the element from the first path to the second one.
            The element at the first path is deleted
        \param [in] _FROM    Element that will be moved.
        \param [in] _TO      The first element's new location.


    */
    virtual void move(const String &_from, String &_to,
                      int depth = 0) {}

    virtual ~Json() = default;

    /**
        @brief
            Used for formatting elements when logging them or saving them to files.
            This method is to be redifined by all children who leave a new line when
            they are done 'logging' themselves.
        \retval FALSE   Default value.
        \retval TRUE    If overriden.
    */

    virtual bool log_space() const { return false; }

public:
    virtual bool contains_recursive(const String &_value, const String &_curr_key, Vector<String> &keys) const = 0;

protected:
    static size_t format_spaces;
};

#endif //! JSON_H