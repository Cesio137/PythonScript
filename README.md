# PythonScript

This is a integration of [Python](python.org/downloads/) as a thirdparty plugin for Unreal Engine

- [x] Windows

- [ ] Linux(Help Wanted)

- [ ] Mac(Help Wanted)

# Setting Up Your Project

- Install VS 2019/2022 and Engine sources.
- Install CMake 3.20 or above.
- Clone the repository or download the latest release.
- Move `UPython` folder into your project's `Plugins` folder.
- Download [PythonLibraries](https://github.com/Cesio137/UPython/releases/tag/PythonLibraries) and open the `.zip` file and extract `folders` inside `UPython` folder. It's contain the .dll and .lib files to make project work.
- Create `build` folder inside `Source/ThirdParty/UPythonLibrary`.
- Open a terminal then type `cmake .. -G "Visual Studio 16 2019"` or `cmake .. -G "Visual Studio 17 2022"`.
- Build VS soluction in `Release` mode.