# Escape the labyrinth

This is a console-based maze game implemented in C++ using ASCII characters. The objective of the game is to navigate through the maze and reach the exit while avoiding obstacles.

## Prerequisites

- C++ compiler
- Windows operating system (for Windows.h library usage)

## Getting Started

1. Clone the repository:
   ```shell
   git clone https://github.com/your-username/console-maze-game.git
   ```

2. Compile the source code:
   ```shell
   g++ main.cpp -o escape_the_labyrinth
   ```

3. Run the game:
   ```shell
   ./escape_the_labyrinth
   ```

## Gameplay

 - Use the arrow keys (up, down, left, right) to move the player character (¤) in the maze.
 - Reach the exit (╬) while avoiding the walls (█).
 - Your score will increase as you progress through the maze.
 - Colliding with a wall will decrease your lives. If your lives reach zero, the game ends.

## Customization

 - Maze size: In the main.cpp file, adjust the mazeWidth and mazeHeight parameters when creating the Game object to change the size of the maze.
 - ASCII characters: Modify the character representations for walls, paths, start, exit, and the player character in the respective classes (Maze, Player, Screen) in the source code.

## License

This project is licensed under the MIT License.

Feel free to modify the contents as needed to provide additional information about your specific implementation or any other details you would like to include in your README file.

