#if !defined(JSON_LIST_H)
#define JSON_LIST_H

#include "Json.hpp"

class JsonList : public Json
{
public:
    /*
        @brief
            Default constructor.
    */
    JsonList();
    /*
        @brief
        Clones the list's elements from the passed Vector.
    */
    JsonList(const Vector<Json *> &_val);
    /*
        @brief
            Copy constructor.
    */
    JsonList(const JsonList &rhs);
    JsonList &operator=(const JsonList &rhs);

    /**
        @brief
            Checks if any of the elements in the list contain the
            passed key.
            NOTE: Only JSON Objects can contain keys.
            Therefore, this method sees if it contains any JSON objects
            and searches for the key in them instead.
    */
    const bool search(const String &key) const override;
    bool contains(const String &value) const override;

    /**
     *   @brief
     *       Clone method.
     */
    Json *clone() const override;
    /**
     *   @brief
     *       Logs the list's value.
     */
    void log() const override;

    /**
     *   @brief
     *      Returns the list's value as a String.
     */
    String get_as_str() const override;

    /**
        @brief
            Creates the new element in the list, if the path is the list's key.
            Else searches deeper into the object to see if the key matches
            any of it's elements and tries to create it there.
    */
    void create(const String &_path, const String &new_val, int depth = 0) override;

    /**
     * @brief
     *      Erases the element from the list, if the path is the list's key.
     *      Else searches deeper into the object to see if the key matches
     *      any of its elements and tries to erase it.
     * @param path    The path to the key.
     */
    virtual void erase(const String &path, int depth = 0) override;

    ~JsonList();

protected:
    bool log_space() const override { return true; }

private:
    Vector<Json *> val;
};

#endif // JSON_LIST_H
