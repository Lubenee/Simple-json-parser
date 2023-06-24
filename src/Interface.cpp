#include "Interface.hpp"

Interface::Interface()
    : is_running(true), current(nullptr), filename(INVALID_FILENAME), loaded_file(false) {}

Interface::Interface(const String &_filename)
    : is_running(true), current(nullptr), filename(_filename), loaded_file(false)
{
    if (filename != INVALID_FILENAME && open_file(filename))
        loaded_file = true;
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

    if (command == "parse" && loaded_file)
    {
        if (open_file(filename))
            current->log();
    }
    else if (command == "log" && loaded_file)
    {
        if (current)
            current->log();
    }
    else if (command == "open")
    {
        if (tokens.size() > 1)
            if (open_file(tokens[1]))
                std::cout << "Done!";
    }
    else if (command == "search" && loaded_file)
    {
        if (tokens.size() > 1)
        {
            if (!current->search(tokens[1]))
                std::cout << "No search results!";
            else
                current->log_search_results();
        }
        else
            std::cout << "Invalid or missing key.";
    }
    else if (command == "contains" && loaded_file)
    {
        if (tokens.size() > 1)
        {
            Vector<String> matches = current->contains(tokens[1]);
            for (auto &i : matches)
                std::cout << i << '\n';
        }
    }
    else if (command == "create" && loaded_file)
    {
        if (tokens.size() > 2)
            current->create(tokens[1], tokens[2]);
        else
            std::cerr << "Invalid path or value.";
    }
    else if (command == "set" && loaded_file)
    {
        if (tokens.size() > 2)
            current->set(tokens[1], tokens[2]);
        else
            std::cerr << "Invalid path or value.";
    }
    else if ((command == "erase" || command == "delete") && loaded_file)
    {
        if (tokens.size() > 1)
            current->erase(tokens[1]);
        else
            std::cerr << "Invalid path.";
    }
    else if (command == "move" && loaded_file)
    {
        if (tokens.size() > 2)
            current->move(tokens[1], tokens[2]);
        else if (tokens.size() > 1)
        {
            String temp = "";
            current->move(tokens[1], temp);
        }
        else
            std::cerr << "Invalid path(s).";
    }
    else if (command == "saveas" && loaded_file)
    {
        if (tokens.size() > 2)
        {
            saveas(tokens[1], tokens[2]);
            std::cout << "Saving..";
        }
        else
        {
            std::cerr << "Invalid path or filename.";
        }
    }
    else if (command == "save" && loaded_file)
    {
        save();
        std::cout << "Saving..";
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
    try
    {
        current = JsonFactory::get().parse_file(_filename.c_str());
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << e.what();
        return false;
    }
    filename = _filename;
    loaded_file = static_cast<bool>(current);
    return loaded_file;
}

void Interface::save() const
{
    std::ofstream ofs;

    ofs.open(filename.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open())
        return;
    if (current)
        ofs << current->get_as_str();
    ofs.close();
}

void Interface::saveas(const String &_path, const String &_name)
{
    std::ofstream ofs;
    String temp(_path);
    temp += _name;

    if (!_name.includes(".json"))
        temp += ".json";

    ofs.open(temp.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open())
        return;
    if (current)
        ofs << current->get_as_str();
    ofs.close();
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
                  << "'Search' -> 'Key' To display all keys corresponding to that input.\n"
                  << "'Contains'-> 'Value' To display all keys that have input as it's value.\n"
                  << "'Create' -> 'Path' -> 'Value' To create a new element on the given path.\n"
                  << "'Set' -> 'Path' -> 'Value' To change an existing's key value.\n"
                  << "'Delete' -> 'Path' To delete the specified key.\n"
                  << "'Save' To save current document.\n"
                  << "'Move' -> 'Path From' -> 'Path To' To move key from_to.\n"
                  << "'Saveas' -> 'Path' -> 'Filename' To save current file to a new location.\n"
                  << std::flush;
    std::cout << "--------------------------------------------------------------------------\n";
}

Interface::~Interface() { delete current; }
