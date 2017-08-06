# City Builder Engine

City Builder Engine is a game that consists in building your own city in an ancient Greek environment. This project is meant to be a fork of the game **Zeus - Master of Olympus**.

City Builder Engine is writen in C++ (C++14) and uses the Qt framework (5.6).

**/!\ WARNING:** The project is far from being playable for now. It is under development. You are welcome to participate.

## Architecture

For the moment, City Builder Engine development is focussed on the map engine and viewer. No real care are being made for the UI interface yet. This mater will come later, when the map engine will be elaborated enough.

The **Map** is the  heart of the software. It is structured as a server / client architecture. The server part, which is called the **Engine**, is the part that process the map and all the elements that are on it and make them evolve during time. The client part, which is called the **Viewer**, is the part that creates the graphical view of the map and update the graphics when it receives data from the engine.

Then, the viewer is meant to be embedded into a **UI** environment. For the moment, the UI environment will be a simple Qt widget environment. As said before, the aesthetic of the UI is not a priority for now.

The engine is constructed in a way that it should be abble to run in a different thread. For the moment, it is running in the main thread in order to make development and debugging easier. But this must not be forgotten especialy when setting up a communication between the engine and the viewer: they will both run in 2 separate thread at the end. So make sure the communication is thread-safe and non blocking.

## Dependencies

Check the wiki for help on installing and configuring the development environment.

- Qt
- yaml-cpp

## Directory structure

- `engine` - The game engine classes
    - `element` - The elements that goes on the map
        - `building` - The buiding elements (static elements)
        - `character` - The character elements (dynamic elements)
    - `map` - The map and map related classes
    - `processing` - The classes that process the game
- `exceptions` - All the custom exception classes
- `global` - Classes that can be use everywhere (engine, ui and viewer)
    - `conf` - Configuration classes
- `ui` - The UI environment classes
    - `controlPanel` - The classes for the control panel
- `viewer` - The map viewer classes
