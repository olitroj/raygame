from sys import argv
import os

if len(argv) != 3:
    print("ERROR: compile_tilemap.py <input-dir> <output-dir>")
    exit()

dir_path = argv[1]
out_dir = argv[2]
backdrop_name = os.path.basename(dir_path)
buffer = bytearray([0xA0, 0x45])

# Removes slash at the end, it causes problems
if dir_path[-1] == '/':
    dir_path = dir_path[:-1]
if out_dir[-1] == '/':
    out_dir = out_dir[:-1]


# Read meta file
with open(f"{dir_path}/meta.txt", "r") as meta_file:
    lines = meta_file.read().splitlines()
    
    # Read parallax props
    for l in lines:
        parallax_props = l.split()
        texture_filename = parallax_props.pop(0)

        # Append image type to props
        if texture_filename.endswith(".bmp"):
            parallax_props.append(0)
        elif texture_filename.endswith(".png"):
            parallax_props.append(1)

        buffer.extend([int(x) for x in parallax_props])

        # Read texture file
        with open(f"{dir_path}/{texture_filename}", "rb") as texture_file:
            texture_bytes = texture_file.read()
            buffer.extend(len(texture_bytes).to_bytes(4, "little"))
            buffer.extend(texture_bytes)

# Write results to file
with open(f"{out_dir}/b_{backdrop_name}", "wb") as backdrop_file:
    backdrop_file.write(buffer)