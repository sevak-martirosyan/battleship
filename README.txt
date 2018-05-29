Implementation of the classic board game "Battle Ship"

This game was written for 2 players and is intended to be used interactive in Linux OS.

To Play:
    $ git clone https://github.com/sevak-martirosyan/battleship
    $ cd ./battleship
    $ make
    $ ./battleship
    
    Start Screen
        The start screen has the followig options:
          
            Input X: input x coordinat (an integet between [0, 9]) to set a ship.
            Input Y: input y coordinat (an integer between [0, 9]) to set a ship.
            Input Direction: input ship direction(0 -> horizontal)
                                                 (1 -> vertical)
                                                 (2 -> NONE)                         
    Ship Placement:
        Once a game is accepted, player is entered into a ship placement screen.
     
            Note: The ship will not set if on top of another ship nor will it rotate if next to a wall.
                          
    Gameplay:
        The player1 who start the game says a couple of coordinates to player2. The opponent(player2)
        input that coordinates in his program and tell damaged any of his ships or not. If damaged player1 says 
        another coordinates else player2 start the game.
            Once all ships have been sunk, the game will end displaying the win or loss.
