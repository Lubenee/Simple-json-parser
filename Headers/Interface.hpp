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
    // void save_to_file(const String &_filename);
    // save
    // saveas

    void update_interface();
    void log_main_menu() const;

private:
    bool is_running;
    Json *current;
    String filename;
    bool loaded_file;
};

#endif //! INTERFACE_H