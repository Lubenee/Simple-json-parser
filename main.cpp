#include "Interface.hpp"
int main(int argc, char *argv[])
{
    String file = INVALID_FILENAME;
    if (argc > 1)
        file = argv[1];

    file = "../j.json"; // TODO - REMOVE THAT
    Interface i(file);
    i.run();

    // Json *curr = i.get_current();
    // curr->search("Name");

    // delete curr;

    std::cout << std::endl;
    return 0;
}
