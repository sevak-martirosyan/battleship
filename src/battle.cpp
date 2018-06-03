#include <iostream>
#include <cassert>

static const int SHOT = 9;
static const int SIZE = 10;
static const int SHIP_CELL = 1;
static const int SHIP_FENCE = 2;
static const int SHIP_MAX_SIZE = 4;
static const int ASCII_OFFSET = 48;
static const int TOTAL_COUNT_OF_SHIPS = 20;

enum direction
{
    HOR = 0,
    VERT = 1,
    NONE = 2
};

struct ship
{
    int l;
    unsigned x;
    unsigned y;
    direction d;
};

/**
 * @brief  Function creates the game field as a two-dimensional dynamic array
 * @return Function returns two-dimensional array initialized with zeros
 **/
int** create_sea()
{
    try {
        int** sea = new int*[SIZE];
        for(int i = 0; i < SIZE; ++i){
            sea[i] = new int[SIZE]();
        }
        return sea;
    } catch (std::bad_alloc& bad) {
        std::cerr << "bad_alloc caught: " << bad.what() << std::endl;
    }
}

/**
 * @brief  Function free up allocated memory
 * @param  sea is a two-dimensional array
 **/
void remove_sea(int** sea)
{
    for (int i = 0; i < SIZE; ++i) {
        delete [] sea[i];
    }
}

/**
 * @brief   Function checks ship's position enabled or not
 * @param   sea is a two-dimensional array
 * @param   s   is ship-type struct
 * @return  Function return true if ship position is enabled, false otherwise
 **/
static bool check_ship_pos(int** sea, const ship& s)
{
    assert(nullptr != sea);
    assert(SIZE > s.x);
    assert(0 <= s.x);
    assert(SIZE > s.y);
    assert(0 <= s.y);
    if (HOR == s.d) {
        if (s.y + s.l > SIZE) {
            return false;
        }
        for (unsigned i = 0; i < s.l; ++i) {
            if (sea[s.x][s.y + i] != 0) {
                return false;
            }
        }
    } else {
        if (s.x + s.l > SIZE) {
            return false;
        }
        for (unsigned i = 0; i < s.l; ++i) {
            if (sea[s.x + i][s.y] != 0) {
                return false;
            }
        }
    }
    return true;
}

 /**
 * @brief  Function changes of a ship's bottom-side values to SHIP_FENCE
 * @param  sea is a two-dimensional array
 * @param  s   is a ship-type struct
 **/
static void fill_bottom(int** sea, const ship& s, bool full = true)
{
    assert(nullptr != sea);
    assert(SIZE > s.x);
    assert(0 <= s.x);
    assert(SIZE > s.y);
    assert(0 <= s.y);
    int i = 0;
    if (full) {
        i = -1;
    }
    for (; i <= s.l; ++i) {
        if (s.y + i < SIZE) {
            sea[s.x + 1][s.y + i] = SHIP_FENCE;
        }
    }
}

/**
 * @brief  Function changes of a ship's top-side values to SHIP_FENCE
 * @param  sea is a two-dimensional array
 * @param  s   is a ship-type struct
 **/
static void fill_top(int** sea, const ship& s, bool full = true)
{
    assert(nullptr != sea);
    assert(SIZE > s.x);
    assert(0 <= s.x);
    assert(SIZE > s.y);
    assert(0 <= s.y);
    int i = 0;
    if (full) {
        i = -1;
    }
    for (i; i <= s.l; ++i) {
        if (s.y + i < SIZE) {
            sea[s.x - 1][s.y + i] = SHIP_FENCE;
        }
    }
}

/**
 * @brief  Function changes of a ship's left-side values to SHIP_FENCE
 * @param  sea is a two-dimensional array
 * @param  s   is a ship-type struct
 **/
static void fill_left(int** sea, const ship& s, bool full = true)
{
    assert(nullptr != sea);
    assert(SIZE > s.x);
    assert(0 <= s.x);
    assert(SIZE > s.y);
    assert(0 <= s.y);
    int i = 0;
    if (full) {
        i = -1;
    }
    for (; i <= s.l; ++i) {
        if (s.x + i < SIZE) {
            sea[s.x + i][s.y - 1] = SHIP_FENCE;
        }
    }
}

/**
 * @brief  Function changes of a ship's right-side values to SHIP_FENCE
 * @param  sea is a two-dimensional array
 * @param  s   is a ship-type struct
 **/
static void fill_right(int** sea, const ship& s, bool full = true)
{
    assert(nullptr != sea);
    assert(SIZE > s.x);
    assert(0 <= s.x);
    assert(SIZE > s.y);
    assert(0 <= s.y);
    int i = 0;
    if (full) {
        i = -1;
    }
    for (; i <= s.l; ++i) {
        if (s.x + i < SIZE) {
            sea[s.x + i][s.y + 1] = SHIP_FENCE;
        }
    }
}

/**
 * @brief  Function changes of a horizontal ship's left-side values to SHIP_FENCE
 * @param  sea is a two-dimensional array
 * @param  s   is a ship-type struct
 **/
void fill_horizontal_left(int** sea, const ship& s)
{
    assert(nullptr != sea);
    assert(SIZE > s.x);
    assert(0 <= s.x);
    assert(0 == s.y);
    if (0 == s.x) {
        sea[s.x][s.y + s.l] = SHIP_FENCE;
        fill_bottom(sea, s, false);
    } else if (SIZE - 1 == s.x) {
        sea[s.x][s.y + s.l] = SHIP_FENCE;
        fill_top(sea, s, false);
    } else {
        fill_bottom(sea, s, false);
        fill_top(sea, s, false);
        sea[s.x][s.y + s.l] = SHIP_FENCE;
    }
}

/**
 * @brief  Function changes of a horizontal ship's right-side values to SHIP_FENCE
 * @param  sea is a two-dimensional array
 * @param  s   is a ship-type struct
 **/
void fill_horizontal_right(int** sea, const ship& s)
{
    assert(nullptr != sea);
    assert(SIZE > s.x);
    assert(0 <= s.x);
    assert((SIZE - 1 == s.y) || (SIZE == s.y + s.l));
    if (0 == s.x) {
        sea[s.x][s.y - 1] = SHIP_FENCE;
        fill_bottom(sea, s);
    } else if (SIZE - 1 == s.x && SIZE == s.y + s.l) {
        sea[s.x][s.y - 1] = SHIP_FENCE;
        fill_top(sea, s);
    } else {
        fill_bottom(sea, s, true);
        fill_top(sea, s, true);
        sea[s.x][s.y - 1] = SHIP_FENCE;
    }
}

 /**                                                              
 * @brief  Function changes values around horizontally oriented ships
 * @param  sea is a two-dimensional array
 * @param  s   is a ship-type struct
 **/
static void fill_horizontal(int** sea, const ship& s)
{
    assert(nullptr != sea);
    assert(SIZE > s.x);
    assert(0 <= s.x);
    assert(SIZE > s.y);
    assert(0 <= s.x);
    if (0 != s.x && 0 != s.y && SIZE > s.y + s.l && SIZE >s.x) {
        fill_top(sea, s);
        fill_bottom(sea, s);
        sea[s.x][s.y - 1] = SHIP_FENCE;
        sea[s.x][s.y + s.l] = SHIP_FENCE;
    } else if (0 == s.y) {
        fill_horizontal_left(sea, s);
    } else if (SIZE - 1 == s.y || SIZE == s.y + s.l) {
        fill_horizontal_right(sea, s);
    } else if (0 == s.x) {
        fill_bottom(sea, s);
        sea[s.x][s.y - 1] = SHIP_FENCE;
        sea[s.x][s.y + s.l] = SHIP_FENCE;
    } else if (SIZE - 1 == s.x) {
        fill_top(sea, s);
        if (!s.y == 0)
            sea[s.x][s.y - 1] = SHIP_FENCE;
        sea[s.x][s.y + s.l] = SHIP_FENCE;
    }
}

/**
 * @brief  Function changes of a vertical ship's top-side values to SHIP_FENCE
 * @param  sea is a two-dimensional array
 * @param  s   is a ship-type struct
 **/

void fill_vertical_top(int** sea, const ship& s)
{
    assert(nullptr != sea);
    assert(0 == s.x);
    assert(SIZE > s.y);
    assert(0 <= s.y);
    if (0 == s.y) {
        fill_right(sea, s, false);
        sea[s.x + s.l][s.y] = SHIP_FENCE;
    } else if (SIZE - 1 == s.y) {
        fill_left(sea, s, false);
        sea[s.x + s.l][s.y] = SHIP_FENCE;
    } else {
        fill_right(sea, s, false);
        fill_left(sea, s, false);
        sea[s.x + s.l][s.y] = SHIP_FENCE;
    }
}

/**
 * @brief  Function changes of a vertical ship's bottom-side values to SHIP_FENCE
 * @param  sea is a two-dimensional array
 * @param  s   is a ship-type struct
 **/
void fill_vertical_bottom(int** sea, const ship& s)
{
    assert(nullptr != sea);
    assert((SIZE - 1 == s.x) || (SIZE == s.x + s.l));
    assert(SIZE > s.y);
    assert(0 <= s.y);
    if (0 == s.y) {
        fill_right(sea, s);
        sea[s.x - 1][s.y] = SHIP_FENCE;
    } else if (SIZE - 1 == s.y) {
        fill_left(sea, s);
        sea[s.x - 1][s.y] = SHIP_FENCE;
    } else {
        fill_left(sea, s);
        fill_right(sea, s);
        sea[s.x - 1][s.y] = SHIP_FENCE;
    }
}

/**
 * @brief  Function changes values around vertically oriented ships
 * @param  sea is a two-dimensional array
 * @param  s   is a ship-type struct
 **/
static void fill_vertical(int** sea, const ship& s)
{
    assert(nullptr != sea);
    assert(SIZE > s.x);
    assert(0 <= s.x);
    assert(SIZE > s.y);
    assert(0 <= s.y);
    if (0 != s.x && 0 != s.y && SIZE - 1 > s.y && SIZE > s.x + s.l) {
        fill_left(sea, s);
        fill_right(sea, s);
        sea[s.x - 1][s.y] = SHIP_FENCE;
        sea[s.x + s.l][s.y] = SHIP_FENCE;
    } else if (0 == s.x) {
        fill_vertical_top(sea, s);
    } else if (SIZE - 1 == s.x || SIZE == s.x + s.l) {
        fill_vertical_bottom(sea, s);
    } else if (0 == s.y) {
        fill_right(sea, s);
        sea[s.x - 1][s.y] = SHIP_FENCE;
        sea[s.x + s.l][s.y] = SHIP_FENCE;
    } else if (SIZE - 1 == s.y) {
        fill_left(sea, s);
        sea[s.x - 1][s.y] = SHIP_FENCE;
        sea[s.x + s.l][s.y] = SHIP_FENCE;
    }
}

 /**
 * @brief  Function fill sea around ships
 * @param  sea is a two-dimensional array
 * @param  s   is a ship-type struct
 **/
static void fill_around(int** sea, const ship& s)
{
    assert(nullptr != sea);
    assert(SIZE > s.x);
    assert(0 <= s.x);
    assert(SIZE > s.y);
    assert(0 <= s.y);
    if (s.d == HOR) {
        fill_horizontal(sea, s);
    } else {
        fill_vertical(sea, s);
    }
}

/**
 * @brief  Function checks does the string value valid or not
 * @param  str string from command line
 * @return return true if string value is valid, false otherwise
 **/
static bool check_string(const std::string& str)
{
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            if (str.size() - i > 1) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief  Function extracts the number from string
 * @param  str string which should be extracted
 * @return The number which contains the string
 */
static int get_num_from_str(const std::string& str)
{
    int result = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            result = static_cast<int>(str[i]) - ASCII_OFFSET;
        }
    }
    return result;
}

/**
 * @brief  Function checks if the number which contains string is valid
 * @param  str string which should be checked
 * @return return checks result
 */
bool check_input(const std::string& str)
{
    int input = get_num_from_str(str);
    if (input < 0 || input > SIZE - 1) {
        return false;
    }
    return true;
}

 /**
 * @brief  Function input coordinats and direction from command line.
 * @param  x is an integer pass by reference from command line.
 * @param  y is an integer pass by reference from command line.
 * @param  dir is a direction type enum. 
 **/
static void input_ship_coords(int** sea, ship& sh, bool shoot = false)
{
    assert(nullptr != sea);
    std::string str_x;
    std::cout << "Input X: ";
    std::getline(std::cin, str_x);
    if (!check_string(str_x) || !check_input(str_x)) {
        std::cout << "Invalid X: " << str_x << std::endl;
        input_ship_coords(sea, sh);
        return;
    }
    sh.x = get_num_from_str(str_x);
    std::string str_y;
    std::cout << "Input Y: ";
    std::getline(std::cin, str_y);
    if (!check_string(str_y) || !check_input(str_y)) {
        std::cout << "Invalid Y: " << str_y << std::endl;
        input_ship_coords(sea, sh);
        return;
    }
    sh.y = get_num_from_str(str_y);
    if (!shoot) {
        while (!check_ship_pos(sea, sh)) {
            input_ship_coords(sea, sh);
        }
    }
}

/**
 * @brief  Function shows the game fild.
 * @param  sea is a two-dimensional array. 
 **/
void show_sea(int** sea)
{
    assert(nullptr != sea);
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            std::cout << sea[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief  Function creates a specified dimensional ship
 * @param  sea is a two-dimensional array
 * @param  dimention is the size of ship
 * @note   if the ship is one dimensional the direction input is unnacessary
 * @return Function returns created ship
 **/
ship create_ship(int** sea, unsigned dimension)
{
    assert(nullptr != sea);
    std::string d;
    ship sh;
    sh.l = dimension;
    std::cout << "DRAW A " << dimension << "-DIMENSIONAL SHIP" << std::endl;
    if (1 != dimension) {
        std::cout << "INPUT DIRECTION(0 -> Horizontal | 1 -> Vertical: ";
        std::getline(std::cin, d);
        int dir = get_num_from_str(d);
        if ((dir != 0) && (dir != 1)) {
            return create_ship(sea, dimension);
        }
        sh.d = static_cast<direction>(dir);
    } else {
        sh.d = NONE;
    }
    input_ship_coords(sea, sh);
    if (HOR == sh.d) {
        for (int i = 0; i < sh.l; ++i) {
            sea[sh.x][sh.y + i] = SHIP_CELL;
        }
    } else {
        for (int i = 0; i < sh.l; ++i) {
            sea[sh.x + i][sh.y] = SHIP_CELL;
        }
    }
    return sh;
}

/**
 * @brief  Function put all ships in the sea.
 * @param  sea is a two-dimensional array. 
 **/
void fill_sea (int** sea)
{
    for(int size = 1; size < SHIP_MAX_SIZE; ++size){
        for(int i = 0; i < SHIP_MAX_SIZE + 1 - size; ++i){
            fill_around(sea, create_ship(sea, size));
            show_sea(sea);
        }
    }
}

/**
 * @brief  Function shoots to apropriate place in the sea given by coordinates.
 * @param  sea is a two-dimensional array. 
 **/
void shoot(int** sea)
{
    assert(nullptr != sea);
    ship sh;
    sh.l = 1;
    unsigned ship_count = TOTAL_COUNT_OF_SHIPS;
    while (0 != ship_count) {
        std::cout << "Input coords to shot a ship:" << std::endl;
        input_ship_coords(sea, sh, true);
        if (SHIP_CELL == sea[sh.x][sh.y]) {
            sea[sh.x][sh.y] = SHOT;
            --ship_count;
            std::cout << "SHIP SHOT!" << std::endl;
        } else {
            std::cout << "YOU MISSED!" << std::endl;
        }
        show_sea(sea);
    }
    std::cout << "\033[1;31m YOU LOOSE\033[0m" << std::endl;
}
