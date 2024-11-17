# So Long

This repository contains my implementation of **So Long**, a 2D game where the player navigates a map, collects items, and avoids enemies. This project was completed as part of the [42](https://www.42.fr/) curriculum. The primary goal is to build a functional game with basic mechanics like movement, item collection, enemy interactions.

![Score: 125%](https://img.shields.io/badge/Score-125%25-green?style=flat&logo=42)
![C](https://img.shields.io/badge/language-C-blue)
![Stars](https://img.shields.io/github/stars/yoyoazs/42-projects?style=social)
![Platform](https://img.shields.io/badge/Platform-Linux-blue)

## Project Description

**So Long** is a simple 2D game that combines map exploration, puzzle-solving, and avoiding enemies. The player moves a character through a grid, collects items, and tries to avoid enemies to reach an exit. The game uses **MiniLibX** for graphics rendering, and performance optimizations are implemented through **multithreading**. Additionally, if the map size exceeds the window dimensions, it automatically scrolls to ensure the player can always see their character and the surroundings.

### Key Features

- **Multithreading**: Optimized performance by using threads to handle enemy movements and map updates concurrently with player input.
- **Map Scrolling**: The map scrolls automatically when it is larger than the window, ensuring that the player can always see the player character and surrounding elements.
- **Map Navigation**: Move the player around the grid and avoid enemies.
- **Item Collection**: Collect objects scattered across the map.
- **Enemy Interaction**: Avoid enemies that patrol around the map.
- **Libft**: A custom library for basic C functions (e.g., string manipulation, memory management).
- **Get Next Line**: Custom input function for handling user input line-by-line.
- **Map Parsing**: Ability to read `.ber` map files and generate a playable level.
- **Sprite Handling**: Use `.xpm` image files for rendering sprites.

## Map Files

The game maps are stored in the `assets/maps/` directory and have the `.ber` extension. Each map file defines the layout of the level, including walls, items, enemies, and the exit. The map is represented as a grid where each character corresponds to a specific element:

- **'1'**: Wall (impassable)
- **'0'**: Empty space (passable)
- **'P'**: Player start position
- **'C'**: Collectible item
- **'E'**: Exit door
- **'B'**: Enemy (moves on the map)
- **'L'**: Ladder (passable and mountable)

The game reads these `.ber` files to generate the game environment.

### Map Example:

```plaintext
111111
1000L1
1PCEL1
111111
```
In this map:

- 'P' is the starting position of the player.
- 'B' represents enemies that move around.
- 'C' represents collectible items.
- 'E' represents the exit.
- 'L' represent ladder.

---

## Controls

You control the player with the following keys:

- **W**: Jump/Climb a ladder
- **A**: Move left
- **S**: Go down a ladder
- **D**: Move right
- **ESC**: Exit the game
- **SPACE**: Hit enemies

The player can move within the grid by pressing the respective keys. The game prevents movement into walls ('1'), but the player can move onto empty spaces ('0'), ladders ('L'), enemies ('B') and collect items ('C').

---

## Movement Mechanics

The player is allowed to move in four directions using the W, A, S, and D keys:

- **W**: Climbs up a ladder.
- **A**: Moves the player left.
- **S**: Goes down a ladder.
- **D**: Moves the player right.

The game checks for collisions with walls. If the player moves into a wall ('1'), the move is canceled. If the player moves into an enemy ('B'), the player loses a life. If the player loses all their lives, the game ends with a "Game Over" message.

The player can also attack enemies by pressing **SPACE**. When the player attacks, enemies in range will be defeated. The player can kill enemies to progress through the game.

If the player collects all the items ('C') and reaches the exit ('E'), the level is completed.

---

## Map Scrolling

When the map is larger than the window, the game will automatically scroll to ensure that the player is always visible and centered within the window. This scrolling behavior allows the player to move freely across the entire map, even if it extends beyond the visible area.

The scrolling is managed by dynamically adjusting the visible portion of the map based on the player's position relative to the window's size. This ensures that the player can always navigate the map without losing track of their location.

---

## Multithreading

In order to optimize performance, the game implements multithreading to handle the following:

- **Map Updates**: The game’s map rendering is handled in a separate thread. This ensures smooth transitions, prevents lag, and allows the map to scroll seamlessly when the player moves or collects items, especially when dealing with large maps or complex environments.

This multithreading approach helps prevent the game from freezing or experiencing slowdowns, ensuring a fluid experience when the player moves across larger areas or when the map continuously updates.

---

## Error Handling

- **Invalid Map Format**: If the map file is incorrectly formatted (e.g., missing elements, invalid characters), the game will output an error message and refuse to load the map.
- **Out of Bounds**: The player is restricted from moving outside the map boundaries. If an invalid move is attempted, the game ignores the command.
- **Enemy Collision**: If the player collides with an enemy, the player loses health. If the player runs out of health, the game ends and displays a "Game Over" message.
- **Player Attacks Enemies**: The player can defeat enemies by hitting them. If the player successfully hits an enemy, the enemy is removed from the map.

---

## Authors

- **yoyoazs** - [GitHub](https://github.com/yoyoazs)
