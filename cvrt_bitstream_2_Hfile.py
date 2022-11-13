# Idea: Save data to Flash memeory using PROGMEM.
# See: https://www.arduino.cc/reference/de/language/variables/utilities/progmem/

import os
from datetime import datetime

bitstream_path = "example_bitstreams/4bit_counter.bin"
c_header_path = "Ard_FlashBitstream/bitstream_data.h"

# Write some C syntax stuff here for the header file
c_file = open(c_header_path, "w")

# Write some stuff about circumstances
c_file.write("/* This header file was auto generated using the " + str(__file__) + " script */\n")
c_file.write("/* on " + datetime.today().strftime('%Y-%m-%d %H:%M:%S') + " */\n\n")

c_file.write("#ifndef BITSTREAM_BIN_H_\n#define BITSTREAM_BIN_H_\n\n")

# Syntax: const dataType variableName[] PROGMEM = {data0, data1, data3…​};
c_file.write("const uint8_t bitstream1[] PROGMEM = {")

file_stats = os.stat(bitstream_path)
byte_size = file_stats.st_size
byte_counter = 0
with open(bitstream_path, "rb") as f:
    while (byte := f.read(1)):
        # 1. convert byte to hex representation
        byte_hex = byte.hex()

        # 2. save in other file
        
        if (byte_counter == byte_size-1):
            # Don't print a comma (avoid trailing comma)
            c_file.write("0x" + byte_hex)
        else:
            # Print a comma
            c_file.write("0x" + byte_hex + ", ")

        byte_counter += 1

c_file.write("};\n\n")

c_file.write("#define BITSTREAM1_SIZE " + str(byte_size) + "\n\n")

# Maybe write some C stuff at the end too :)
c_file.write("#endif /* BITSTREAM_BIN_H_ */")

# Close C-file
print("All done - header file was generated :)")
c_file.close()