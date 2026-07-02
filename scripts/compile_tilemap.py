from sys import argv
import os

if len(argv) < 2:
    print("ERROR: compile_tilemap.py: No tilemap directory provided!")
    exit()

def key_func(x):
    name = os.path.splitext(x)[0]
    try:
        return int(name)
    except ValueError:
        return float('inf')  # pushes non-numbers to the end

for dir_path in argv[1:]:
    meta_buffer = bytearray([0xA0, 0x44])
    texture_buffer = bytearray()
    tilemap_name = ""
    parent_dir = os.path.dirname(dir_path)
    
    for file in sorted(os.listdir(dir_path), key=key_func):
        print(file)

        if file.endswith(".txt"):
            tilemap_name = file.removesuffix(".txt")
            with open(f"{dir_path}/{file}", "rb") as meta_file:
                curr_value = 0
                tile_count = 0
                for c in meta_file.read():
                    if c == ord('\n'):
                        meta_buffer.append(curr_value)
                        curr_value = 0
                        tile_count += 1
                    elif c == ord(' '):
                        meta_buffer.append(curr_value)
                        curr_value = 0
                    else:
                        curr_value = curr_value * 10 + (c - ord('0'))
                meta_buffer.append(curr_value)
                meta_buffer.insert(3, tile_count)

        elif file.endswith(".bmp"):
            with open(f"{dir_path}/{file}", "rb") as texture_file:
                data = texture_file.read()

                offset = int.from_bytes(data[10:14], "little")
                width = int.from_bytes(data[18:22], "little")
                height = int.from_bytes(data[22:26], "little")

                raw = data[offset:]
                row_size = width * 4

                for y in range(height):
                    src_y = height - 1 - y
                    row = raw[src_y * row_size:(src_y + 1) * row_size]

                    for i in range(0, len(row), 4):
                        b, g, r, a = row[i:i+4]
                        texture_buffer.extend((r, g, b, a))

    with open(f"{parent_dir}/{tilemap_name}", "wb") as tilemap_file:
        tilemap_file.write(meta_buffer)
        tilemap_file.write(texture_buffer)