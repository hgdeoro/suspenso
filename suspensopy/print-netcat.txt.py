import pathlib
import struct
import sys

MAX_SIZE = 128


def main():
    input_file = pathlib.Path(sys.argv[1])
    assert input_file.exists() and input_file.is_file()
    iter_num = 1
    with input_file.open(mode='rb') as file_obj:
        while True:
            size_bytes = file_obj.read(4)
            if not len(size_bytes):
                break

            # --- #1
            # size = int.from_bytes(size_bytes, "little", signed=False)

            # --- #2
            # size_bytes = bytes([size_bytes[3], size_bytes[2], size_bytes[1], size_bytes[0]])
            # size = struct.unpack('>I', size_bytes)[0]

            # --- #3
            size = struct.unpack('<I', size_bytes)[0]

            assert 1 <= size <= MAX_SIZE, f"Invalid size: {size}"

            remaining_size = 8 + (size - 1) * 12
            message = file_obj.read(remaining_size)
            assert len(message) == remaining_size, \
                f"read() returned {len(message)} bytes, expected {remaining_size} bytes"

            print(f"size={size}")
            iter_num += 1


if __name__ == '__main__':
    main()
