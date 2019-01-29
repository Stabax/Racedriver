
## RaceDriver ##

### Dependencies ###

	- Nlhomann's json
	- Pugixml
	- libCurl
	- Lua
	- Sol2
	- PicoSha2
	- OmniUnit
	- XCurses (PDCurses / NCurses)

### Contributors ###

	- Stabax
	- Baxlan
	- Stalker2106

### How to Build ###

You need to grab and build dependencies if they are not installed on your machine (which is probably the case),
you can do so with the following command-lines:

    git submodule init
		git submodule update
    make deps

Then, running standard

    make

should auto-generate the game based on your platform.
Tested on C++17 compliant MinGW, GCC, and MSBuild.
Enjoy! Racedriver binary will be built inside ./bin folder!