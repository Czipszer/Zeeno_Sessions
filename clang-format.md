# clang-format

Make a clang-format work.

- Under Debian-based distros
    1. `apt install clang-format`
    1. In VSCode install `xaver.clang-format`
    1. Edit settings: `"editor.formatOnSave": true`
- Under Windows something like this, not tested
    1. Install LLVM https://github.com/llvm/llvm-project/releases/download/llvmorg-12.0.1/LLVM-12.0.1-win64.exe
    1. Install VSCode extension `xaver.clang-format`
    1. in the settings, set clang-format.executable if needed (if you did add the LLVM into your `PATH` during installation, you do not have to do this, if you did not, put full path here `C:\Program Files\LLVM\clang-format.exe`)
    1. in extension setting set parameter `clang-format.style` to `file`
    1. in extension editor setting set parameter `editor.formatOnSave` to `enabled` 
    1. in extension setting set parameter `editor.formatOnSaveMode` to `file`
    1. open some project in sessions folder
    1. press `ctrl + shift + p`
    1. write `format` and choice option `Format Document With`
    1. select `configure default formatter` and `clang-format` 


