# 🎮 YoRutris - A Modern Tetris Clone

## 🌟 Core Components

### 1. 🎲 Game Class (`Game.h`, `Game.cpp`)

- Manages core game mechanics and state
- Controls block movement, rotation, and placement
- Handles scoring system and level progression
- Manages audio (music and sound effects)
- Controls game speed based on score
- Implements random block generation
- Score increases based on lines cleared
- Supports multiple block types unlocked by score

### 2. 🎯 Grid Class (`Grid.h`, `Grid.cpp`)

- Implements 30x30 game grid
- Handles row clearing mechanics
- Manages cell states and colors
- Features gradient cell rendering
- Provides collision detection
- Includes grid glow effects
- Tracks cleared row count

### 3. 🧊 Block Class (`Block.h`, `Block.cpp`, `blocks.cpp`)

- Implements various block shapes (L, J, I, O, T, S, Z, C, V, II)
- Handles block rotation and movement
- Manages block positioning
- Provides collision checking
- Supports preview landing position
- Features color-based rendering
- Implements block validation

### 4. 📊 LeaderBoard Class (`LeaderBoard.h`, `LeaderBoard.cpp`)

- Manages high score system
- Stores player names, scores, and levels
- Saves/loads scores to/from file
- Displays top 5 scores
- Implements score sorting
- Prevents duplicate entries
- Maximum 10 entries storage

### 5. 🎨 Animation System

#### Animation Class (`Anim.h`, `Anim.cpp`)

- Handles GIF animations
- Controls frame timing
- Supports looping animations
- Manages texture loading/unloading
- Scales animations to screen size

#### SplashScreen Class (`YoRuSplScr.h`, `YoRuSplScr.cpp`)

- Implements game intro animation
- Controls splash screen timing
- Handles screen transitions
- Manages animation frames
- Supports screen scaling

### 6. 🎨 Colors System (`Colors.h`, `Colors.cpp`)

- Defines game color palette
- Provides 16 unique colors
- Includes various blue shades
- Supports color management
- Used for block and UI rendering

### 7. 📍 Position System (`Position.h`, `Position.cpp`)

- Manages grid coordinates
- Handles block positioning
- Supports movement calculations

## 🎮 Controls

| Key   | Action          |
| ----- | --------------- |
| ←/→   | Move Left/Right |
| ↑     | Rotate Block    |
| ↓     | Move Down       |
| ENTER | Start Game      |
| ESC   | Exit Game       |

## 🛠️ Technical Requirements

- RayLib Graphics Library
- C++ Compiler
- Audio Support
- Minimum 30x30 display resolution

## 🎵 Audio Features

- Background music
- Rotation sound effects
- Line clear sounds
- Game over sound

Made with 🎮 by YoRu
