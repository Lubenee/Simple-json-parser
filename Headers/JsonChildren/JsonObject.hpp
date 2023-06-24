#if !defined(JSON_OBJECT_H)
#define JSON_OBJECT_H

#include "Json.hpp"

class JsonObject : public Json
{
public:
    /**
     * @brief
     *      This struct holds the object's values as Key-value pairs.
     *      It takes care of it's own data.
     *
     */
    struct Pair
    {
        Json *value;
        String key;

        Pair();
        Pair(const Json *_value);
        Pair(const Json *_value, const String &_key);
        Pair(const Pair &_rhs);
        Pair &operator=(const Pair &rhs);

        ~Pair();
    };

public:
    /**
     * @brief Construct a new Json Object object
     *
     */
    JsonObject();
    /**
     * @brief Construct a new Json Object object
     *
     * @param _val  A Vector, which contains the Object's elements.
     */
    JsonObject(const Vector<Pair> &_val);
    /**
     * @brief Construct a new Json Object object
     *      Default copy constructor.
     * @param rhs
     */
    JsonObject(const JsonObject &rhs);

    JsonObject &operator=(const JsonObject &rhs);

    /**
     * @brief Searches the object for the passed key, and any element that matches it
     * is stored in the search_matches Vector.
     *
     * @param key An Element's key.
     * @return true     One or more element is found.
     * @return false    No elementsare found.
     */
    const bool search(const String &key) const override;

    /**
     * @brief This method attempts to create a new JSON element located at the specified path.
     * The path's last token is the new element's key.
     * If the passed value is not valid JSON format, the object's state
     * remains unchanged.
     * @param _path         Path.
     * @param new_value     Valid JSON value.
     */
    void create(const String &_path, const String &new_value, int depth = 0) override;

    /**
     * @brief This method attempts to change an existing element's value
     *          to the passed new value.
     * If no such element exists, the object's state remains unchanged.
     * If the passed value is not valid JSON format, the object's state
     * remains unchanged.
     * An appropriate message is displayed.
     *
     * @param _path         Path.
     * @param new_value     Valid JSON value.
     */
    virtual void set(const String &_path, const String &new_value, int depth = 0) override;

    /**
     * @brief This method attempts to erase the element from the passed path.
     * If no such element is found, the object's state remains unchanged.
     * @param path  Path.
     */
    virtual void erase(const String &path, int depth = 0) override;

    /**
     * @brief This method attempts to move the element from the first path
     * to the second.
     *
     * @param _from  From Path.
     * @param _to    To Path.
     */
    virtual void move(const String &_from, String &_to,
                      int depth = 0) override;

    /**
     * @brief Clone Method.
     */
    Json *clone() const override;
    /**
     * @brief
     *      Logs the Object's elements.
     */
    void log() const override;
    /**
     * @brief
     *      Logs the elements from the last time the user searched for a key.
     */
    void log_search_results() const override;
    /**
     * @brief Get the object formatted as a string.
     */
    String get_as_str() const override;

    bool log_space() const override { return true; }

    ~JsonObject();

protected:
    bool contains_recursive(const String &_value, const String &_curr_key, Vector<String> &keys) const override;

private:
    Vector<Pair> val;
    static Vector<Pair> search_matches;
    static Vector<Json *> contains_matches;
};

#endif // JSON_OBJECT_H
