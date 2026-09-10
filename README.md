# Raygame - 2D Platformer Demo
Currently just a project for my hobby video game using raylib

# Notible features
- Physics based movement, Newton's second law makes the movement smooth
- All game assets are linked into the executable, so no asset folder in C:\Program Files
- All dependencies are included in the repo (or installed with your OS), no need to go looking for them

# How to build
### Requirements
- `gcc` (c11)
- GNU `make` (in bash environment)
- `python` (any modern version ig)
- GNU binutils (specifically `objcopy`)
- x86 architecture

### Building and running

```bash
# Platform and build may be omitted, defaults to `windows` and `debug`
make PLATFORM=<windows|linux> BUILD=<debug|release>
./bin/raygame
```