
## RaceDriver ##

### Contributors ###

	-Stabax Ltd.
	-Baxlan
	-Stalker2106

### How to Build ###

#### Build Curses ####
1. Go deep down "./thirdparty/lpdcurses/wincon/"
2. Run make (with argument "DLL=Y" on windows)
3. copy lpdcurses.dll to "./bin" (from cwd, "../../../bin/")
#### Build LibCurl ####
4. Go deep down "./thirdparty/libcurl/"
5. Run make (with argument "mingw32" on windows)
6. copy lib/libcurl.dll to "./bin" (from cwd, "../../bin/")
#### Build Racedriver ####
7. Run make
8. ENJOY!