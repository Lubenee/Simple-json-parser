#ifndef INTERFACE_H
#define INTERFACE_H

#include "JsonParser.hpp"
#include <fstream>

#define INVALID_FILENAME "Null"

class Interface
{
public:
    Interface();
    Interface(const String &_filename);
    void run();
    Json *get_current() const;

    ~Interface();

private:
    bool open_file(const String &_filename);
    void saveas(const String &_path, const String &_name);
    void save() const;

    void update_interface();
    void log_main_menu() const;

    // contains
    // set -path -string
    // create -path -string
    // delete -path
    // move -from -to

private:
    bool is_running;
    Json *current;
    String filename;
    bool loaded_file;
};

#endif //! INTERFACE_H