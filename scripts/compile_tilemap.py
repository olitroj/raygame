from sys import argv
import os
import json

if len(argv) != 3:
    print('ERROR: compile_tilemap.py <input-dir> <output-dir>')
    exit()

dir_path = argv[1]
out_dir = argv[2]

# Removes slash at the end, it causes problems
if dir_path[-1] == '/':
    dir_path = dir_path[:-1]
if out_dir[-1] == '/':
    out_dir = out_dir[:-1]

tilemap_name = os.path.basename(dir_path)
buffer = bytearray([0xA0, 0x44])

# Read meta file
with open(f'{dir_path}/meta.json', 'r') as meta_file:
    tilemap = json.load(meta_file)

    for tile in tilemap['tiles']:
        # Read tile properties
        tile_filename = tile['filename']
        tile_friction = tile['friction']
        tile_collision = tile['collision']
        if tile_filename.endswith('.bmp'):
            tile_image_type = 0
        elif tile_filename.endswith('.png'):
            tile_image_type = 1
        buffer.extend([tile_friction, tile_collision, tile_image_type])

        # Read texture file
        with open(f'{dir_path}/{tile_filename}', 'rb') as texture_file:
            texture_bytes = texture_file.read()
            buffer.extend(len(texture_bytes).to_bytes(4, 'little'))
            buffer.extend(texture_bytes)

# Write results to file
with open(f'{out_dir}/t_{tilemap_name}', 'wb') as tilemap_file:
    tilemap_file.write(buffer)