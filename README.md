
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

#### Build (MinGW32 Windows) ####
    cd ./thirdparty/lpdcurses/wincon/
    mingw32-make DLL=Y
    cp lpdcurses.dll ../../../bin
    cd ../libcurl/
    mingw32-make mingw32
    cp lib/libcurl.dll ../../bin/
    cd ../lua/
    mingw32-make mingw
    cd ../../
    mingw32-make

#### Build (Linux) ####
    apt-get install libncurses-dev
    apt-get install libcurl-dev
    cd ./thirdparty/lua/
    make linux
    cd ../../
    make


Enjoy! Racedriver binary was generated inside ./bin folder!