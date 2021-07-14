import pathlib
import struct
import sys

MAX_SIZE = 256


def main():
    input_file = pathlib.Path(sys.argv[1])
    assert input_file.exists() and input_file.is_file()
    iter_num = 1
    with input_file.open(mode='rb') as file_obj:
        while True:
            num_messages_bytes = file_obj.read(4)
            if not len(num_messages_bytes):
                break

            num_messages = struct.unpack('<I', num_messages_bytes)[0]

            assert 1 <= num_messages <= MAX_SIZE, f"Invalid num_messages: {num_messages}"

            remaining_size = 8 + (num_messages - 1) * 12
            if remaining_size > 1500 - 4:
                # This is required because Arduino Nano 33 IoT just sends the first 1500 bytes
                truncated = True
                remaining_size = 1500 - 4
            else:
                truncated = False

            message = file_obj.read(remaining_size)
            assert len(message) == remaining_size, \
                f"read() returned {len(message)} bytes, expected {remaining_size} bytes"

            if truncated:
                print(f"num_messages={num_messages} (truncated)")
            else:
                print(f"num_messages={num_messages}")

            iter_num += 1


if __name__ == '__main__':
    main()
