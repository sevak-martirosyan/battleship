#include <signal.h>
#include <iostream>

#include "battle.hpp"

int** sea = nullptr;

void signal_handler(int sig)
{
   std::cout << "\033[1;31m CLOSE THE GAME\033[0m" << std::endl;
   remove_sea(sea);
   exit(0);
}

int main()
{
    sea = create_sea();
    signal(SIGINT, signal_handler);

    fill_sea(sea);
    shoot(sea);
    remove_sea(sea);
    return 0;
}

