from sys import argv
import os

if len(argv) != 3:
    print("ERROR: compile_backdrop.py <input-file> <output-dir>")
    exit()

file_path = argv[1]
filename = os.path.basename(file_path).removesuffix(".png")
dest_dir = argv[2]
buffer = bytearray([0xA0, 0x45])

# Removes slash at the end, it causes problems
if file_path[-1] == '/':
    dir_path = file_path[:-1]
if dest_dir[-1] == '/':
    dest_dir = dest_dir[:-1]

# Read texture file
with open(file_path, "rb") as texture_file:
    texture_bytes = texture_file.read()
    buffer.extend(len(texture_bytes).to_bytes(4, "little"))
    buffer.extend(texture_bytes)

# Write results to file
with open(f"{dest_dir}/b_{filename}", "wb") as backdrop_file:
    backdrop_file.write(buffer)