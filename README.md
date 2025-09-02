# Build Dependencies
- a **POSIX**-compliant system (**macOS**, **Linux**, **BSD**, etc.)
    > **Windows users**, [install WSL](https://learn.microsoft.com/en-us/windows/wsl/install).
- `git`
- `make`
- `g++` (supports C++17)
    > **macOS users**, note that `g++` is a symbolic link to `clang++`. This is **not an issue** as long as `clang++` supports C++17.
# Installation Guide
**In a terminal emulator**, run
```sh
git clone --depth 1 https://github.com/Jeff1n03/jef.git && \
cd jef/ && make && sudo make install && cd ../ && \
rm -rf jef/
```
# Uninstallation Guide
**In a terminal emulator**, run
```sh
sudo rm -f /usr/local/bin/jef /usr/local/share/man/man1/jef.1
```
# Resources
**In a terminal emulator**, run `man 1 jef`.
