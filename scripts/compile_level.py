from sys import argv
import os

if len(argv) != 3:
    print("ERROR: compile_level.py <input-file> <output-dir>")
    exit()

new_line = ord('\n')

file_path = argv[1]
filename = os.path.basename(file_path).removesuffix(".txt")

# Removes slash at the end, it causes problems
if file_path[-1] == '/':
    dir_path = file_path[:-1]

traits = True
prev_newline = False

with open(file_path, "rb") as map_file:
    result = bytearray([0xA0, 0x43])
    for c in map_file.read():
        if traits:
            if c == new_line and prev_newline:
                traits = False
            elif c == new_line:
                result.append(0)
                prev_newline = True
            else:
                result.append(c)
                prev_newline = False

        elif c != new_line:
            result.append(c - ord('0') if c != ord(' ') else 255)
            

    with open(f"{argv[2]}/l_{filename}", "wb") as result_file:
        result_file.write(result)