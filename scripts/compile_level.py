from sys import argv
import os

if len(argv) != 3:
    print("ERROR: compile_level.py <input-file> <output-dir>")
    exit()

file_path = argv[1]
filename = os.path.basename(file_path).removesuffix(".txt")
dest_dir = argv[2]

# Removes slash at the end, it causes problems
if file_path[-1] == '/':
    dir_path = file_path[:-1]
if dest_dir[-1] == '/':
    dest_dir = dest_dir[:-1]

# Read map file
with open(file_path, "r") as map_file:
    lines = map_file.read().splitlines()
    result = bytearray([0xA0, 0x43])

    # Read name line
    name = lines.pop(0) + '\0'
    result.extend(bytes(name, "ascii"))

    # Read values line
    values = lines.pop(0).split()
    for value in values:
        result.extend(int(value).to_bytes(2, "little"))

    # Read tiles line
    values = lines.pop(0).split()
    for value in values:
        result.extend(int(value).to_bytes())

    # Read tilemap
    width = 0
    height = 0
    tilemap_buffer = bytearray()
    for line in lines:
        if width == 0:
            width = len(line)
        elif len(line) != width:
            print("ERROR: All tilemap rows must have the same width!")
            exit()
        tilemap_buffer.extend([int(x) if x != ' ' else 255 for x in line])
        height += 1

    result.extend(width.to_bytes(2, "little"))
    result.extend(height.to_bytes(2, "little"))
    result.extend(tilemap_buffer)
            
    with open(f"{dest_dir}/l_{filename}", "wb") as result_file:
        result_file.write(result)