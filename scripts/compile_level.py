from sys import argv

if len(argv) < 2:
    print("ERROR: compile_level.py: No level file provided!")
    exit()

tile_map_start = 6
new_line = ord('\n')

for file_path in argv[1:]:
    with open(file_path, "rb") as map_file:
        trait = 0
        result = bytearray([0xA0, 0x43])

        for c in map_file.read():
            if trait < 6:
                if c == new_line:
                    result.append(0)
                    trait += 1
                else:
                    result.append(c)

            elif trait == 6 and c != new_line:
                result.append(c - ord('0') if c != ord(' ') else 0)
                

        with open(file_path.removesuffix(".level"), "wb") as result_file:
            result_file.write(result)