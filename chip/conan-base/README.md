# Conan
Conan is a package manager for C++. It means that when you need some external library, you do not have to download it a build it by yourself, but you simply specify the library name and version and Conan will do the rest. CMakeLists.txt is adjusted in a way, that you do not have to do anything else in order to use it. However, there is some initial settings.

## Installation
The best way how to install conan is by `pip` package manager, but if you do not have Python installed, you can download binaries here https://conan.io/downloads.html .

NOTE: Unix terminal. When there are commands starting with `#`, it is a root terminal. When starting with `$`, it is a user terminal. If you want to run root commands in a user terminal, you can (on most systems) prepend the command with `sudo`

Under debian you simply run
```lang=console, name=Terminal
[root]# apt install python3-pip
[root]# pip3 install conan
```
and that is all.

# Ninja
Ninja is a good 'build assembler'. It will manage running individual commands like compiling individual files and then linking. We will use Ninja, because it can compile bigger projects in a very efficient way using all the power of your computer.

 - Arch: `pacman -S ninja`
 - Debian/Ubuntu: `apt install ninja-build`
 - Fedora: `dnf install ninja-build`
 - Gentoo: `emerge dev-util/ninja`
 - Opensuse: `zypper in ninja`
 - Alpine: `apk add ninja`

Under Windows, if you use package manager, you can install it according to instructions found on https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages or if you choose to install it manually, you need to download https://github.com/ninja-build/ninja/releases and place the binary somewhere into the PATH variable. I suggest to place the binary into the `C:\ninja\` directory and to add this path to the PATH variable (https://www.wikihow.com/Change-the-PATH-Environment-Variable-on-Windows)

# Setting up VSCode
In order to reasonably unify workflow, we will modify settings of the CMakeTools plugin in the Visual Studio Code. You can modify the setting directly by modifying `settings.json`, just add
```lang=json, name=settings.json
"cmake.buildDirectory": "${workspaceFolder}/build/${buildType}",
"cmake.preferredGenerators": [
	"Ninja"
],
```
or you can use GUI for that, so you will have to search for corresponding items.

# Installing dependencies
Once you have everything in place, you simply edit `conanfile.txt` to add all the dependencies you need (depends on your project).
After that, run `conan_install.sh` (Unix) or `conan_install.bat` (Windows) file. It will take a while for the first time, but it caches everything, so it will much faster in the following runs.

This script wil generate directory `build`, and for each configuration a directory inside.

# Setting it up
Because we will use some cutting-edge settings, we will want all our external libraries to be compiled with the same cutting-edge settings.

Under linux
```lang=console, name=Terminal
[user]$ conan profile update settings.compiler.libcxx=libstdc++11 default
[user]$ conan profile update settings.compiler.cppstd=20 default
```

Under Windows 
```lang=batch, name=Command line
conan profile update settings.compiler.cppstd=20 default
```

Now run [[#installing-dependencies]] again. It can take some time, since most of the dependencies will need to be recompiled.

# Compiling
Once we have all the dependendencies running, we can start compiling. In VS code we select desired configuration e.g. `CMake: [Debug]` and this will generate additional configuration files into our `build` directory. Now we can Build and Run our software.