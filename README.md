# 🧱 Brick Breaker Game (C++ / OpenGL / OOP)

A fully functional **Brick Breaker game** implemented in **C++ using OpenGL (FreeGLUT)**, designed with **Object-Oriented Programming (OOP)** principles such as encapsulation, inheritance, and modular design.

---

## 📁 Project Structure

```id="r8k2zt"
.
├── game.cpp              # Main game logic (Game loop, classes, mechanics)
├── paddle.cpp            # Paddle implementation
├── util.cpp              # Rendering utilities (drawing, colors, helpers)
├── util.h                # Shared declarations
├── CImg.h                # Image handling library (if used)
├── Makefile              # Build automation
├── install-libraries.sh  # Dependency installation (Linux)
├── highScore.txt         # Stores persistent high score
```

---

## 🎮 Features

* 🧱 Multiple brick types with different durability
* 🎯 Ball physics with collision detection
* 🕹️ Paddle controlled via mouse movement
* ⚡ Power-up system:

  * 🟢 Increase paddle size
  * 🌸 Decrease paddle size
  * 🔵 Slow ball speed
  * 🔴 Increase ball speed
  * 🟡 Multi-ball feature
* ❤️ Life system
* 📊 Score tracking system
* 💾 Persistent high score using file handling
* 🎨 Color-coded bricks and power-ups
* 🔁 Continuous gameplay loop

---

## 🧠 OOP Concepts Used

* **Classes & Objects** → Paddle, Ball, Brick, Game
* **Inheritance** → Power-up base class with derived types
* **Encapsulation** → Private attributes with getters/setters
* **Polymorphism** → Virtual functions for power-up behavior
* **Modular Design** → Separation of utilities and gameplay

---

## ⚙️ Installation & Setup

### 🐧 Linux

```bash id="n3mjg9"
chmod +x install-libraries.sh
./install-libraries.sh
make
./game
```

---

### 🪟 Windows (MSYS2 MinGW64)

Install dependencies:

```bash id="h1t7xk"
pacman -S mingw-w64-x86_64-freeglut
```

Build:

```bash id="3wd7vt"
make
```

Or manually:

```bash id="5k1v4c"
x86_64-w64-mingw32-gcc game.cpp paddle.cpp util.cpp -o game.exe -lfreeglut -lopengl32 -lglu32
```

Run:

```bash id="x9c2kp"
./game.exe
```

---

## 🎯 Controls

| Input      | Action         |
| ---------- | -------------- |
| Mouse Move | Control paddle |
| ESC        | Exit game      |

---

## 🧩 Game Mechanics

* The ball bounces across the screen and destroys bricks
* Bricks require multiple hits depending on durability
* Destroyed bricks may spawn **power-ups**
* Power-ups fall downward and activate on paddle collision
* Player loses a life if the ball falls below the paddle
* Game ends when lives reach zero

---

## 💾 High Score System

* High score is stored in:

  ```id="0o6x5k"
  highScore.txt
  ```
* Automatically updates when a new high score is achieved

---

## 🚧 Known Issues

* Memory management for dynamic power-ups can be improved
* Collision response can be refined for edge cases
* Limited level variety

---

## 🚀 Future Improvements

* 🎮 Multiple levels and increasing difficulty
* 🔊 Sound effects and background music
* 🧠 Smarter collision physics
* 🖥️ Start menu and restart option
* 💡 Better memory management (smart pointers)
* 🎨 UI enhancements and animations

---

## 👨‍💻 Author

**Muhammad Saif Murtaza**
FAST-NUCES

---

## 📜 License

This project is open-source and available under the MIT License.
