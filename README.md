Matrix shooter game
===================

This is a two player game designed to be run on the Schonherz Matrix. 

## Short specification

There are two players: one on the top and one on the bottom side of the dormitory. They can fire each other, the asteroides and the powerups. If a player is hit by a missile of the other or an asteroide, it will harm him. The harm is visualized on the edge of the scene. Powerups give special abilities to the players for a short time.

## Compilation

### SFML
#### Debian
On Debian system, you can easily install the required libs and headers with the libsfml-dev package. You don't even need to clone the SFML submodule
#### Windows
**TODO** check
Clone the SFML submodule, then create a folder in it called *build*, then run cmake and create GNU Makefile in the build folder from CMakeList.txt of the original SFML folder. Install the necessary dependencies to the build, than run GNU Make. If everything is all right, than you are good to go and build Matrix-shooter

### GA Input

Build the module with cmake to lib/gainput/build directory.

### Matrix-shooter and Matrix-Emu

You will need at least QT 5.12 to compile this program. (For eg. there is no gamepad support below this version.)

The simplest way to setup your environment is to install Qt Creator. (from qt website)

After cloning this repository with its submodule, compile Emu with Qt Creator, then the Matrix-shooter project.

## Running the emulator

You have to add a Matrix network interface to your computer. In this case a loopback interface is enough. 
Commands on linux
```bash
    sudo ip a a 10.6.23.45/16 dev lo
```
Then run the Emulator from matrix-simple/Emu
