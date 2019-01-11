
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

You need to grab dependencies if they are not installed on your machine,
you can do so with the following command-lines:
    git submodule init
		git submodule update
Then, running make should auto-generate the game based on your platform.
Enjoy! Racedriver binary will be built inside ./bin folder!