
# RaceDriver

## About

RaceDriver is a console based (XCurses) strategy racing game, with real world physics.

### Contributors

	- Stabax
	- Baxlan
	- Stalker2106

## Modding ###

This game is especially developed to be hacked, modded, or customized ! Feel free to take a look at the [Modding section!](./documentation/Modding.md)

## How to Build ###

### Dependencies ###

	- Nlhomann's json
	- Pugixml
	- libhttp-cpp (works with winsock)
	- Lua
	- Sol2
	- PicoSha2
	- OmniUnit
	- XCurses (PDCurses / NCurses)
	- (libreadline-dev on linux)

NOTE: If you are on linux, you might need to install lua subdependency "libreadline-dev", and "libcurl".
			They should be available within your package manager:

    sudo apt-get install libreadline-dev
    sudo apt-get install libcurl4-gnutls-dev

You need to grab and build dependencies if they are not installed on your machine (which is probably the case),
you can do so with the following command-lines:

    git submodule init
    git submodule update
    make deps

Then, running standard

    make

should auto-generate the game based on your platform.
Tested on *C++17* compliant *MinGW, GCC, and MSBuild*.
Enjoy! Racedriver binary will be built inside ./bin folder!