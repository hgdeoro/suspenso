import re

import serial


def readlines(client: serial.Serial):
    lines = []
    line = client.readline().decode('ascii')
    while line:
        lines.append(line.rstrip())
        line = client.readline().decode('ascii')
    return lines


def parse_message(lines):
    lines = '\n'.join(lines)
    # <part:1085377743>
    # Opcion invalida
    # </part:1085377743>
    MESSAGE_REGEX = re.compile(r'<part:(\d+)>(.*)</part:(\d+)>', re.DOTALL)
    match = MESSAGE_REGEX.search(lines)
    if not match:
        return None

    ret = match.group(2).splitlines()
    if not ret[0]:
        ret.pop(0)
    if not ret[-1]:
        ret.pop()
    return ret


def main():
    arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=0.5)
    readlines(arduino)  # clean buffer
    print("> sending 'a'")
    arduino.write(b'a')

    print("> waiting for response...")
    response = readlines(arduino)
    print("> -------------------- RESPONSE: ")
    print('\n'.join(response))
    print("> -------------------- MESSAGE: ")
    print('\n'.join(parse_message(response)))
    print("> done")


if __name__ == '__main__':
    main()
