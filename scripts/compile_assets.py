from sys import argv

if len(argv) < 2:
    exit()

values_until_tilemap = 6

# TODO: Convert ASCII numbers into binary
for file_path in argv[1:]:
    with open(file_path, "rb") as map_file:
        value = 0
        result = bytearray([0xA0, 0x43])
        for c in map_file.read():
            if c == ord('\n') and value < values_until_tilemap:
                result.append(0)
                value += 1
            elif c != ord('\n'):
                result.append(c)

        with open(file_path.removesuffix(".level"), "wb") as result_file:
            result_file.write(result)