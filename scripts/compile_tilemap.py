from sys import argv
import os

if len(argv) != 3:
    print("ERROR: compile_tilemap.py <input-dir> <output-dir>")
    exit()

dir_path = argv[1]
out_dir = argv[2]
tilemap_name = os.path.basename(dir_path)
buffer = bytearray([0xA0, 0x44])

# Removes slash at the end, it causes problems
if dir_path[-1] == '/':
    dir_path = dir_path[:-1]
if out_dir[-1] == '/':
    out_dir = out_dir[:-1]

# Read meta file
with open(f"{dir_path}/meta.txt", "r") as meta_file:
    lines = meta_file.read().splitlines()

    # Read tilemap ID
    tile_id = lines.pop(0)
    if not tile_id.isnumeric() or int(tile_id) < 0 or int(tile_id) > 255:
        print(f"ERROR: compile_tilemap.py: Tilemap ID must be 0-255 ({tile_id})!")
        exit()
    buffer.extend(int(tile_id).to_bytes())
    
    # Read tile props
    for l in lines:
        tile_props = l.split()
        texture_filename = tile_props.pop(0)

        # Append image type to props
        if texture_filename.endswith(".bmp"):
            tile_props.append(0)
        elif texture_filename.endswith(".png"):
            tile_props.append(1)

        # Convert to bytes
        try:
            buffer.extend([int(x) for x in tile_props])
        except:
            print(f"ERROR: compile_tilemap.py: Tile properties must be 0-255!")
            exit()

        # Read texture file
        with open(f"{dir_path}/{texture_filename}", "rb") as texture_file:
            texture_bytes = texture_file.read()
            buffer.extend(len(texture_bytes).to_bytes(4, "little"))
            buffer.extend(texture_bytes)

# Write results to file
with open(f"{out_dir}/t_{tilemap_name}", "wb") as tilemap_file:
    tilemap_file.write(buffer)