#include "Interface.hpp"

Interface::Interface()
    : is_running(true), current(nullptr), filename(INVALID_FILENAME), file(""), loaded_file(false) {}

Interface::Interface(const String &_filename)
    : is_running(true), current(nullptr), filename(_filename), file(""), loaded_file(false)
{
    if (filename != INVALID_FILENAME)
        if (load_json_from_file(filename))
            loaded_file = true;
}

Json *Interface::get_current() const
{
    return current->clone();
}

void Interface::run()
{
    while (is_running)
        update_interface();
}

bool Interface::load_json_from_file(const String &_filename)
{
    std::ifstream ifs;
    ifs.open(_filename.c_str(), std::ios::in);
    if (!ifs.is_open())
        return false;

    ifs.seekg(0, std::ios::end);
    size_t file_size = ifs.tellg();
    char *buffer = new char[file_size];

    ifs.seekg(0, std::ios::beg);
    ifs.read(&buffer[0], file_size);

    file = buffer;
    delete[] buffer;

    ifs.close();
    return true;
}

void Interface::update_interface()
{
    String command = "";
    log_main_menu();
    std::cin >> command; // TODO

    if (command == "1")
    {
        if (current != nullptr)
            delete current;

        load_json_from_file(filename);
        current = JsonFactory::get().parse_value(file.c_str());

        current->log();
        std::cout << std::endl;
    }
    else if (command == "search")
    {
        String temp;
        std::cin >> temp;
        current->search(temp);
    }
    else if (command == "contains")
    {
        String temp;
        std::cin >> temp;
        current->contains(temp);
        }
    else if (command == "0")
        is_running = false;
    std::cout << std::endl;
}

void Interface::log_main_menu() const
{
    String temp;
    if (loaded_file)
    {
        temp = "File \"";
        temp += filename;
        temp += "\" in local directory is currently loaded.";
    }
    else
        temp = "No file is currently loaded.";

    std::cout << "--------------------------------------------------------------------------\n"
              << temp << '\n';
    if (loaded_file)
        std::cout << "0. To quit the program.\n"
                  << "1. To parse and display loaded file.\n"
                  << "---------------------------------------------------------------------\n"
                  << std::flush;
}

Interface::~Interface()
{
    delete current;
}