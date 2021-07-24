# shooter

This is a two player game designed to be run on the Schönherz Mátrix.

## Short specification

There are two players: one on the top and one on the bottom side of the dormitory. They can fire each other, the asteroides and the powerups. If a player is hit by a missile of the other or an asteroide, it will harm him. The harm is visualized on the edge of the scene. Powerups give special abilities to the players for a short time.

## Prerequisites

Qt **5.12**(LTS) or above is recommended

**C++ 17** compatible compiler

**SFML**

**Gainput**(bundled as a submodule)

**libmueb**

Build tools for Qt(platform dependent):

- **MSVC**(Desktop development with C++)/MinGW on **Windows**
- **build-essential** on **Unix/Linux**

## Compilation

### SFML
#### Linux
On Debian, Ubuntu system, you can easily install the required libs and headers with the **libsfml-dev** package.
#### Windows

Build SFML using cmake.

Specify **SFML_DIR** in cmake configuration, this folder contains **SFMLConfig.cmake**.

### Gainput

Automatically builds before matrix-shooter target.

### Libmueb

Build it with cmake, then specify **libmueb_DIR** to libmueb's cmake output directory.

### Matrix-shooter

You will need at least Qt 5.12 to compile this program. (For eg. there is no gamepad support below this version.)

The simplest way to setup your environment is to install Qt Creator. (from qt website)

After cloning this repository with its submodule, compile matrix-shooter project with Qt Creator
