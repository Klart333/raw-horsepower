# Wave function collapse (with a side of pacman)

The game is something in the style of pacman where you control a coin-eating circle. The map first generates, then the player is free to move around using WASD and LMB to dash through walls. When all coins are collected the game is over, conceptually. 

The project is made as a prototype to learn and experiment with different design patterns. The following were implemented:

- **Observer**
  
  A custom C++ event was made with function pointers to send callbacks for when the left mouse button is pressed. 

- **Flyweight**

  Flyweight was used to reduce the memory usage of the map generation and instantiation. A lot of identical tiles are placed with different positions, for this new textures don't need to be created for each   thus reducing memory.

- **Singleton**

  A single Dependencies class was used as a singleton and held references to all extra-state systems (systems that shouldn't be bound to state). Very useful and easy to implement but filled with pitholes,     in such a small project however most downsides aren't relevant.

- **Factory**

  Used for instantiating GameObjects. Very useful and seen in pretty much all commercial engines.

- **Dependency Inversion**

  Used to decouple the game logic from the SDL engine. The rendering such as textures and the window are abstracted with interfaces, so the game logic can use any engine with textures and a window and         switching is easy.

- **Game loop**
  
  We have this :P
  The gameobjects additionaly have an update method... so that's good.
