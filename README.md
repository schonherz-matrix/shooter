Matrix shooter game
===================

This is a two player game designed to be run on the Schonherz Matrix. 

h1. Short specification

There are two players: one on the top and one on the bottom side of the dormitory. They can fire each other, the asteroides and the powerups. If a player is hit by a missile of the other or an asteroide, it will harm him. The harm is visualized on the edge of the scene. Powerups give special abilities to the players for a short time.

h1. Compilation

You will need at least QT 5.12 to compile this program. (For eg. there is no gamepad support below this version.)

The simplest way to setup your environment is to install Qt Creator. (from qt website)

After cloning this repository with its submodule, compile matrix-simple/mueb with Qt Creator, then the Matrix-shooter project.

h1. Running the emulator

You have to add a Matrix network interface to your computer. In this case a loopback interface is enough. 
Commands on linux
```bash
    sudo ip a a 10.6.23.45/16 dev lo
```
Then run the Emulator from matrix-simple/Emu
