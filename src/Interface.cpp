#include "Interface.hpp"

Interface::Interface()
    : is_running(true), current(nullptr), filename(INVALID_FILENAME), loaded_file(false) {}

Interface::Interface(const String &_filename)
    : is_running(true), current(nullptr), filename(_filename), loaded_file(false)
{
    if (filename != INVALID_FILENAME)
        if (open_file(filename))
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

void Interface::update_interface()
{
    String command = "";
    log_main_menu();
    std::cout << "   >>";
    std::cin >> command;
    Vector<String> tokens;

    try
    {
        command.split(' ', tokens);
        command = tokens[0].to_lower_case();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }

    if (command == "parse")
    {
        open_file(filename);
        current->log();
    }
    else if (command == "open")
    {
        if (tokens.size() > 1)
            if (open_file(tokens[1]))
                std::cout << "Done!";
    }
    else if (command == "search")
    {
        if (tokens.size() > 1)
            if (!current->search(tokens[1]))
                std::cout << "No search results!";
    }
    else if (command == "exit")
    {
        is_running = false;
        std::cout << "Exiting.";
    }
    std::cout << std::endl;
}

bool Interface::open_file(const String &_filename)
{
    if (current)
        delete current;
    current = JsonFactory::get().parse_file(_filename.c_str());
    filename = _filename;
    loaded_file = (bool)current;
    return (current ? true : false);
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
              << temp << '\n'
              << "'Exit' To quit the program.\n"
              << "'Open' -> 'Filepath' to try a new file.\n";
    if (loaded_file)
        std::cout << "'Parse' To parse and display loaded file.\n"
                  << "'Search' -> 'Key' To display all values corresponding to that key.\n"
                  << std::flush;
    std::cout << "--------------------------------------------------------------------------\n";
}

Interface::~Interface() { delete current; }
