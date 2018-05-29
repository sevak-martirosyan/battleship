#include <signal.h>
#include <iostream>

#include "battle.hpp"

int** sea = nullptr;

void signalHandler(int sig)
{
   std::cout << "\033[1;31mCLOSE THE GAME\033[0m" << std::endl;
   remove_sea(sea);
   exit(0);
}

int main()
{
    sea = create_sea();
    signal(SIGINT, signalHandler);

    fill_sea(sea);
    shoot(sea);
    remove_sea(sea);
    return 0;
}

