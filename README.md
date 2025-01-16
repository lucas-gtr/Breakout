# Breakout Game

## Overview
Breakout is a classic 2D arcade game developed with a modern and maintainable codebase. The game consists of **four levels**, upon launching the game, players can select their desired level by entering a number between 1 and 4.

This project is structured to support future enhancements, including adding new rendering backends like Metal, Vulkan, or DirectX, without requiring changes to the core game logic.

## Features
- **Four unique levels**: Players can choose their starting level when launching the game
- **Graphics abstraction**: Currently implemented with **OpenGL**, but designed to support multiple APIs such as Metal, Vulkan, and DirectX without modifying the core logic
- **Modular input handling**: Input management is isolated for flexibility and future expansion

## Project Structure
The project is organized into distinct modules to ensure clarity and maintainability:

- **Core/**
  - Contains the game logic, rules, and core mechanics
  - Fully independent of rendering or input specifics

- **Graphics/**
  - Handles all aspects of rendering the game
  - Designed with an abstraction layer, allowing seamless integration of different rendering APIs. Currently implemented with OpenGL

- **Input/**
  - Manages user input
  - Decoupled from both game logic and rendering
 
- **Custom Vector and Matrix management**
  - Developed a custom library for my own vector and matrix management.
  - The library provides essential mathematical operations for 2D transformations, such as scaling, rotation, and translation, necessary for handling game object movements and physics.

## Prerequisites
- **C++17 or later**
- **OpenGL development environment**

## Build and Run Instructions
*To be completed*

## Future Improvements
- Impelemnt bonus and malus that randomly spawn for the player
- Implement sound effects and music
- Add a graphical user interface for selecting levels and game settings
- Add support for additional graphics APIs (Metal, Vulkan, DirectX)

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.
