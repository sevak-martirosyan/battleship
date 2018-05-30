#include <iostream>
#include <cassert>

static const int size = 10;
enum direction
{
    HOR = 0,
    VERT = 1,
    NONE = 2
};

struct ship
{
    unsigned x;
    unsigned y;
    int l;
    direction d;
};

/**
 * @brief  Function creates the game field as a two-dimensional dynamic array. 
 * @return Function returns two-dimensional array initialized with zeros.
 **/
int** create_sea()
{
    int** sea = new int*[size];
    for(int i = 0; i < size; ++i){
        sea[i] = new int[size]();
    }
    return sea;
}

/**
 * @brief  Function free up allocated memory.
 * @param  sea is a two-dimensional array. 
 **/
void remove_sea(int** sea)
{
    for (int i = 0; i < size; ++i) {
        delete [] sea[i];
    }
}

/**
 * @brief   Function checks ship's position enabled or not.
 * @param   sea is a two-dimensional array.
 * @param   s   is ship-type struct.
 * @return  Function return true if ship position is enabled, false otherwise.
 **/
static bool check_ship_pos(int** sea, const ship& s)
{
    assert(sea);
    assert(s.x < size);
    assert(s.y < size);
    if (s.d == HOR) {
        if (s.y + s.l > size) {
            return false;
        }
        for (unsigned i = 0; i < s.l; ++i) {
            if (sea[s.x][s.y + i] != 0) {
                return false;
            }
        }
    } else {
        if (s.x + s.l > size) {
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
 * @brief  Function changes of a ship bottom-side values to 2.
 * @param  sea is a two-dimensional array.
 * @param  s   is a ship-type struct.
 **/
static void fill_bottom(int** sea, const ship& s, bool full = true)
{
    int i = 0;
    if (full) {
        i = -1;
    }
    for (; i <= s.l; ++i) {
        if (s.y + i < size) {
            sea[s.x + 1][s.y + i] = 2;
        }
    }
}
 /**
 * @brief  Function changes of a ship top-side values to 2.
 * @param  sea is a two-dimensional array. 
 * @param  s   is a ship-type struct.
 **/
static void fill_top(int** sea, const ship& s, bool full = true)
{
    int i = 0;
    if (full) {
        i = -1;
    }
    for (i; i <= s.l; ++i) {
        if (s.y + i < size) {
            sea[s.x - 1][s.y + i] = 2;
        }
    }
}

/**
 * @brief  Function changes of a ship left-side values to 2.
 * @param  sea is a two-dimensional array.
 * @param  s   is a ship-type struct.
 **/
static void fill_left(int** sea, const ship& s, bool full = true)
{
    int i = 0;
    if (full) {
        i = -1;
    }
    for (; i <= s.l; ++i) {
        if (s.x + i < size) {
            sea[s.x + i][s.y - 1] = 2;
        }
    }
}

/**
 * @brief  Function changes of a ship right-side values to 2.
 * @param  sea is a two-dimensional array.
 * @param  s   is a ship-type struct.
 **/
static void fill_right(int** sea, const ship& s, bool full = true)
{
    int i = 0;
    if (full) {
        i = -1;
    }
    for (; i <= s.l; ++i) {
        if (s.x + i < size) {
            sea[s.x + i][s.y + 1] = 2;
        }
    }
}

 /**                                                              
 * @brief  Function changes values around horizontally oriented ships.
 * @param  sea is a two-dimensional array.
 * @param  s   is a ship-type struct.
 **/
static void fill_horizontal(int** sea, const ship& s)
{
    if (s.x != 0 && s.y != 0 && s.x + s.l < size - 1) {
        fill_top(sea, s);
        fill_bottom(sea, s);
        sea[s.x][s.y - 1] = 2;
        sea[s.x][s.y + s.l + 1] = 2;
    } else if (s.x == 0 && s.y == 0) {
        sea[s.x][s.y + s.l + 1] = 2;
        fill_bottom(sea, s, false);
    } else if (s.x == 0 && s.y + s.l == size) {
        sea[s.x][s.y - 1] = 2;
        fill_bottom(sea, s);
    } else if (s.x == size && s.y == 0) {
        sea[s.x][s.y + s.l + 1] = 2;
        fill_top(sea, s, false);
    } else if (s.x == size && s.y + s.l == size) {
        sea[s.x][ s.y - 1] = 2;
        fill_top(sea, s, false);
    }
}

/**
 * @brief  Function changes values around vertically oriented ships.
 * @param  sea is a two-dimensional array.
 * @param  s   is a ship-type struct.
 **/
static void fill_vertical(int** sea, const ship& s)
{
    if (s.x != 0 && s.y != 0 && s.y + s.l < size - 1 && s.x < size - 1) {
        fill_left(sea, s);
        fill_right(sea, s);
        sea[s.x - 1][s.y] = 2;
        sea[s.x + s.l][s.y] = 2;
    } else if (s.x == 0 && s.y == 0) {
        fill_right(sea, s, false);
        sea[s.x + s.l][s.y] = 2;
    } else if (s.x == 0 && s.y == size - 1) {
        fill_left(sea, s, false);
        sea[s.x + s.l][s.y] = 2;
    } else if (s.x == size - 1 && s.y == 0) {
        fill_right(sea, s);
        sea[s.x - 1][s.y] = 2;
    } else if (s.x == size - 1 && s.y == size - 1) {
        fill_left(sea, s);
        sea[s.x - 1][s.y] = 2;
    } else if (s.x == 0) {
        fill_right(sea, s, false);
        fill_left(sea, s, false);
        sea[s.x + s.l][s.y] = 2;
    } else if (s.x == size - 1 && s.d == NONE) {
        fill_right(sea, s);
        fill_left(sea, s);
        sea[s.x - 1][s.y] = 2;
    }
}

 /**
 * @brief  Function fill sea around ships.
 * @param  sea is a two-dimensional array.
 * @param  s   is a ship-type struct.
 **/
static void fill_around(int** sea, const ship& s)
{
    assert(sea);
    assert(s.x < size);
    assert(s.y < size);
    if (s.d == HOR) {
        fill_horizontal(sea, s);
    } else {
        fill_vertical(sea, s);
    }
}

 /**
 * @brief  Function input coordinats and direction from command line.
 * @param  x is an integer pass by reference from command line.
 * @param  y is an integer pass by reference from command line.
 * @param  dir is a direction type enum. 
 **/
static void input_coords(int& x, int& y, direction& dir, bool shoot = false)
{
    int d = 0;
    std::cout << "Input X: ";
    std::cin >> x;
    std::cout << "Input Y: ";
    std::cin >> y;
    if (!shoot) {
        std::cout << "Input Direction: ";
        std::cin >> d;
        dir = static_cast<direction>(d);
    }
    if (x < 0 || x > 9 || y < 0 || y > 9) {
        std::cout << "INPUT VALID COORDINATES" << std::endl;
        input_coords(x, y, dir);
    }
}

/**
 * @brief  Function shows the game fild.
 * @param  sea is a two-dimensional array. 
 **/
void show_sea(int** sea)
{
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            std::cout << sea[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief  Function creates an one-dimensional ship.
 * @param  sea is a two-dimensional array.
 * @return Function returns ship-type s.
 **/
ship create_one_dim_ship(int** sea)
{
    assert(sea);
    int x= 0;
    int y = 0;
    ship s;
    s.d = NONE;
    s.l = 1;
    std::cout << "DRAW ONE-DIMENSIONAL SHIP" << std::endl;
    input_coords(x, y, s.d, true);
    s.x = x;
    s.y = y;
    while (!check_ship_pos(sea, s)) {
        input_coords(x, y, s.d, true);
    }
    sea[x][y] = 1;
    return s;
}

/**
 * @brief  Function creates a two-dimensional ship.
 * @param  sea is a two-dimensional array.
 * @return Function returns ship-type s.
 **/
ship create_two_dim_ship(int** sea)
{
    assert(sea);
    int x = 0;
    int y = 0;
    int d = 0;
    ship s;
    s.l = 2;
    std::cout << "DRAW A TWO-DIMENSIONAL SHIP" << std::endl;
    std::cout << "INPUT DIRECTION (0 -> H | 1 -> V):  ";
    std::cin >> d;
    s.d = static_cast<direction>(d);
    if (HOR == s.d) {
        input_coords(x, y, s.d, true);
        if (check_ship_pos(sea, s)) {
            sea[x][y] = 1;
            sea[x][y + 1] = 1;
        } else if (VERT == s.d) {
            input_coords(x, y, s.d, true);
            sea[x][y] = 1;
            sea[x + 1][y] = 1;
        } else {
            std::cerr << "";
        }
    }
       return s;
}

/**
 * @brief  Function creates a three-dimensional ship.
 * @param  sea is a two-dimensional array.
 * @return Function returns ship-type s.
 **/
ship create_three_dim_ship (int** sea)
{
    int x = 0;
    int y = 0;
    int d = 0;
    ship s;
    s.l = 3;
    std::cout << "DRAW A THREE-DIMENSIONAL SHIP" << std::endl;
    std::cout << "INPUT DIRECTION (0 -> H | 1 -> V):  ";
    std::cin >> d;
    s.d = static_cast<direction>(d);
    if (HOR == s.d) {
        input_coords(x, y, s.d, true);
        (sea[x][y] = 1) && (sea[x][y + 1] = 1)
            && (sea[x][y + 2] = 1);
    } else if (VERT == s.d) {
        input_coords(x, y, s.d, true);
        (sea[x][y] = 1) && (sea[x + 1][y] = 1)
            && (sea[x + 2][y] = 1);
    } else{
        std::cerr << " ";
    }
    return s;
}


/**
 * @brief  Function creates a four-dimensional ship.
 * @param  sea is a two-dimensional array.
 * @return Function returns ship-type s.
 **/
ship create_four_dim_ship (int** sea)
{
    int x = 0;
    int y = 0;
    int d = 0;
    ship s;
    s.l = 4;
    std::cout << "DRAW A FOUR-DIMENSIONAL SHIP" << std::endl;
    std::cout << "INPUT DIRECTION (0 -> H | 1 -> V):  ";
    std::cin >> d;
    s.d = static_cast<direction>(d);
    if (HOR == s.d) {
        input_coords(x, y, s.d, true);
        (sea[x][y] = 1) && (sea[x][y + 1] = 1) && (sea[x][y + 2] = 1)
            && (sea[x][y + 3] = 1);
    } else if (VERT == d) {
       input_coords(x, y, s.d, true);
       (sea[x][y] = 1) && (sea[x + 1][y] = 1) && (sea[x + 2][y] = 1)
            && (sea[x + 3][y] = 1);
      }
    return s;
}

/**
 * @brief  Function put all ships in the sea.
 * @param  sea is a two-dimensional array. 
 **/
void fill_sea (int** sea)
{
    for (int i = 0; i < 4; ++i) {
        ship s = create_one_dim_ship(sea);
        fill_around(sea, s);
        show_sea(sea);
    }
    for (int i = 0; i < 3; ++i) {
        ship s = create_two_dim_ship(sea);
        fill_around(sea, s);
        show_sea(sea);
    }
    for (int i = 0; i < 2; ++i) {
        ship s = create_three_dim_ship(sea);
        fill_around(sea, s);
        show_sea(sea);
    }
    for (int i = 0; i < 1; ++i) {
        ship s = create_four_dim_ship(sea);
        fill_around(sea, s);
        show_sea(sea);
    }
}

/**
 * @brief  Function shoots to apropriate place in the sea given by coordinates.
 * @param  sea is a two-dimensional array. 
 **/
void shoot(int** sea)
{
   int x = 0;
   int y = 0;
   direction d;
   unsigned ship_count = 20;

   while (true && ship_count != 0) {
        std::cout << "Input coords to shot a ship:" << std::endl;
        input_coords(x, y, d, true);
        if (sea[x][y] == 1) {
            sea[x][y] = 9;
            --ship_count;
            std::cout << "SHIP SHOT!";
        } else {
            std::cout << "YOU MISSED!";
        }
        show_sea(sea);
   }
   std::cout << "\033[1;31m YOU LOOSE\033[0m" << std::endl;
}
