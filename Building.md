### Building
CMake is the build system.
- IDE: VS-Code, Visual Studio, CLion, etc
- Manual:
	```bash
	mkdir build
	cd build
	cmake ..
	```
	Building:
	```bash
	cd ..
	cmake --build build
	```


#### Platforms:
- Windows (tested)
- MaxOs (not tested but should work)
- Linux (tested)

#### Dependencies (only for Linux)
```bash
sudo apt-get install libx11-dev libxrandr-dev libxcursor-dev libgl-dev libudev-dev libfreetype-dev
```