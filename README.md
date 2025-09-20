# GravitationReflex

A physics-based game simulation featuring gravitational mechanics, collision detection, and interactive gameplay modes. This project demonstrates real-time physics simulation using C++ and the Imagine++ graphics library.

## Overview

GravitationReflex is a school project that implements three different gravitational physics simulations:

1. **Gravitation1** - Single planet orbiting around a sun
2. **Gravitation2** - Multi-body simulation with multiple suns
3. **Duel** - Two-player competitive game with gravity-affected projectiles

## Features

- **Real-time Physics Simulation**: Accurate gravitational forces, collision detection, and elastic collisions
- **Interactive Graphics**: Visual representation using the Imagine++ graphics library
- **Multiple Game Modes**: Three distinct simulation/game experiences
- **Vector Mathematics**: Custom 2D vector implementation for physics calculations
- **Collision System**: Comprehensive collision detection and response mechanics

## Game Modes

### Gravitation1
A simple orbital simulation where a red planet orbits around a yellow sun. The simulation demonstrates:
- Gravitational attraction
- Orbital mechanics
- Collision detection with boundaries
- Bounce mechanics (limited to 5 bounces)

**Controls**: Click to restart the simulation

### Gravitation2
An advanced multi-body simulation featuring:
- Multiple yellow suns with random positions
- Complex gravitational interactions between all bodies
- Real-time physics with sun-to-sun collisions
- Interactive restart mechanism

**Controls**: Click to reset and start a new simulation

### Duel (Two-Player Game)
A competitive game where two players take turns shooting projectiles affected by gravity:
- **Player 1** (Green): Click to aim and shoot
- **Player 2** (Blue): Click to aim and shoot
- Projectiles are affected by gravitational fields from multiple suns
- Win condition: Hit your opponent with a projectile
- Strategy involves using gravity wells to curve shots

**Controls**: 
- Click and drag to aim
- Release to fire projectile
- Players alternate turns

## Technical Architecture

### Core Components

- **Vector Class** (`vector.h`/`vector.cpp`): 2D vector mathematics with operators
- **Ball Class** (`ball.h`/`ball.cpp`): Physics objects representing planets, suns, and projectiles
- **Physics Engine** (`tools.h`/`tools.cpp`): Collision detection and response algorithms
- **Game Logic**: Individual game implementations in respective `.cpp` files

### Physics Implementation

- **Gravitational Forces**: Realistic N-body gravitational simulation
- **Collision Detection**: Continuous collision detection with predictive algorithms
- **Elastic Collisions**: Momentum and energy conservation in collisions
- **Integration**: Real-time physics stepping with configurable time steps

## Requirements

### Dependencies
- **Imagine++**: Graphics and input library
- **CMake**: Build system (version 3.4 or higher)
- **C++ Compiler**: Supporting C++11 or later

### Platform Support
- macOS (with Framework support)
- Linux (with appropriate Imagine++ installation)
- Windows (with Imagine++ for Windows)

## Building and Installation

### Prerequisites
1. Install the Imagine++ graphics library:
   - **macOS**: Install from `/Library/Frameworks`
   - **Linux**: Follow Imagine++ installation guide
   - **Windows**: Install Imagine++ Windows package

### Build Instructions
```bash
# Clone the repository
git clone https://github.com/anwarden/GravitationReflex.git
cd GravitationReflex

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
make

# Run the games
./Gravitation1      # Single planet simulation
./Gravitation2      # Multi-body simulation  
./Duel             # Two-player game
```

### CMake Targets
- `Gravitation1`: Basic orbital simulation
- `Gravitation2`: Advanced multi-body simulation
- `Duel`: Two-player competitive game
- `Gravitation`: Shared library with physics and graphics utilities

## Code Structure

```
├── CMakeLists.txt          # Build configuration
├── LICENSE                 # Apache 2.0 License
├── README.md              # This file
├── vector.h/cpp           # 2D vector mathematics
├── ball.h/cpp             # Physics object implementation
├── tools.h/cpp            # Physics engine (collisions, forces)
├── gravitation1.cpp       # Single planet simulation
├── gravitation2.cpp       # Multi-body simulation
└── duel.cpp              # Two-player game
```

## Physics Concepts Demonstrated

- **Newton's Law of Universal Gravitation**: F = G × (m1 × m2) / r²
- **Conservation of Momentum**: Elastic collision mechanics
- **Numerical Integration**: Real-time physics simulation
- **Collision Prediction**: Continuous collision detection
- **N-body Problem**: Multiple gravitational bodies interaction

## Screenshots

*Screenshots would be added here showing the three different game modes in action*

## Academic Context

This project was developed as part of "Tp4_Initial" coursework, demonstrating:
- Object-oriented programming in C++
- Real-time graphics programming
- Physics simulation implementation
- Interactive application development
- Mathematical modeling in software

## Author

**Anwar Kardid** - Student implementation

## License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## Contributing

This is a school project, but suggestions and improvements are welcome through issues and pull requests.

## Acknowledgments

- Imagine++ graphics library developers
- Physics simulation algorithms and references
- Educational resources on game physics and mathematics