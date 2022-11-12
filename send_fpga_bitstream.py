import serial
import time
import sys
import getopt
import os

#default values
com_port = "COM3"
baudrate = "115200"
bitstream_path = ""

# call this script like <script_name.py> -i <bitstream file> -c COM4

# list of arguments without the first one (is only the python file name)
argv = sys.argv[1:]

try:
    opts, args = getopt.getopt(argv, 'i:b:c:h')
except getopt.GetoptError:
    # Print a message or do something useful
    print('Something went wrong!')
    sys.exit(2)

for opt, arg in opts:
    if (opt == '-i'):
        bitstream_path = arg
    if (opt == '-b'):
        baudrate = arg
    if (opt == '-c'):
        com_port = arg
    if (opt == '-h'):
        print("You've requested help. No worries - it should be quite easy\n")
        print("Example usage: " + str(__file__ + " -i <path_to_bitstream_to_program -b <baud_rate_of_arduino> -c <com_port_of_arduino\n"))
        print("The parameters -c for specifying the COM-port and -b for specifying the bit rate are optional and default values will be used if they are omitted.")
        sys.exit(2)

# Open serial connection
arduino = serial.Serial(port=com_port, baudrate=baudrate, timeout=.1)

def close_connection():
    arduino.close()
    print("Connection closed?: " + str(not arduino.is_open))

if __name__ == '__main__':
    if arduino.is_open:
        # Transmit bitstream
        print("Transmitting data from " + bitstream_path + " to FPGA")
        # Open the bitstream file
        file_stats = os.stat(bitstream_path)
        byte_size = file_stats.st_size
        current_byte = 0
        with open(bitstream_path, "rb") as f:

            # Maybe neccessary idk...
            #print("Maybe")
            print(str(arduino.read_all()))
            time.sleep(3)

            while (byte := f.read(1)):
                # Do stuff with byte.
                # Send byte
                arduino.write(byte)
                arduino.flushInput()

                #print("Byte was sent")

                # Wait for confirmation that byte was received correctly
                response = 0
                while (response != byte):
                    response = arduino.read(arduino.inWaiting())
                    #print("I received: " + str(response))
                
                #print("I sent: " + str(byte) + " and received back: " + str(response))
                sys.stdout.write("FPGA Programming Progress: %d%%   \r" % (int((current_byte / byte_size) * 100)) )
                sys.stdout.flush()
                current_byte += 1

        print("All done :)")
        # Close serial connection
        close_connection()

    else:
        print("Connection could not be established")
        #Try to close connection that doesn't exist anyways...
        close_connection()
        sys.exit()

# TODO:
# Automatically detect COM Ports
# https://www.youtube.com/watch?v=AHr94RtMj1A