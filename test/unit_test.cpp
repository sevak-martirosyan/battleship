#include <signal.h>
#include <iostream>

#define TEST(x) \
if ((x)) {\
    std::cout << "PASS    " << __FUNCTION__ << std::endl;\
} else {\
    std::cout << "FAILED  " << __FUNCTION__ << std::endl;\
}

#include "../src/battle.hpp"

int** sea = nullptr;

void signal_handler (int sig)
{
   remove_sea(sea);
   exit(0);
}

void check_ship_position (int** sea)
{
}

void check_create_sea (int** tmp_sea)
{
    tmp_sea = create_sea();
    TEST(tmp_sea != nullptr);
}

void check_remove_sea (int** tmp_sea)
{
    try {
        remove_sea(tmp_sea);
        TEST(true);
    } catch (...) {
        TEST(false);
    }
}

int main()
{
    signal (SIGINT, signal_handler);
    try {
        int** tmp_sea = nullptr;
        check_create_sea(tmp_sea);
        check_remove_sea(tmp_sea);
    } catch(...) {
        sea = create_sea();
        sea = nullptr;
        std::cout << "\033[1;31m Unexpected exception\033[0m" << std::endl;
    }
}
