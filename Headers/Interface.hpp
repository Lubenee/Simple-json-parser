#ifndef INTERFACE_H
#define INTERFACE_H

#include "JsonParser.hpp"
#include <fstream>

#define INVALID_FILENAME "Null"

class Interface
{
public:
    /**
     * @brief Construct a new Interface object
     *  Initializes the interface with an empty json object and an invalid filename.
     */
    Interface();
    /**
     * @brief Construct a new Interface object
     *  Initializes the interface with a filename, and if the file is found, tries to parse it.
     * @param _filename Which file to be parsed.
     */
    Interface(const String &_filename);
    /**
     * @brief Runs the interface
     */
    void run();

    ~Interface();

private:
    /**
     * @brief This method attempts to load a file into the interface,
     * and tries to parse it.
     *
     * @param _filename Filename
     * @return true     The file has been successfully opened or parsed.
     * @return false    The file has either not been found, or not parsed successfully.
     */
    bool open_file(const String &_filename);

    /**
     * @brief Saves made changes in a file, and gives the user the ability
     *  to specify the path where the file can be saved.
     * @param _path     Path where the file can be saved.
     * @param _name     File name.
     */
    void saveas(const String &_path, const String &_name);

    /**
     * @brief Saves made changes in the same file from which the original
     *  data has been read.
     */
    void save() const;

    /**
     * @brief Updates the command interface.
     */
    void update_interface();
    /**
     * @brief Logs all availible commands.
     */
    void log_main_menu() const;

private:
    bool is_running;
    Json *current;
    String filename;
    bool loaded_file;
};

#endif //! INTERFACE_H