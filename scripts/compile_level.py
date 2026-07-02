from sys import argv

if len(argv) < 2:
    print("ERROR: compile_level.py: No level file provided!")
    exit()

new_line = ord('\n')

for file_path in argv[1:]:
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
                

        with open(file_path.split(".")[0], "wb") as result_file:
            result_file.write(result)