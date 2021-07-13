import logging
import re

import serial

logger = logging.getLogger(__name__)


def readlines(client: serial.Serial):
    lines = []
    line = client.readline().decode('ascii')
    while line:
        lines.append(line.rstrip())
        line = client.readline().decode('ascii')
        logger.debug("Got line: '%s'", line.rstrip())
    return lines


def parse_message(lines):
    lines = '\n'.join(lines)
    # <part:1085377743>
    # Invalid option
    # </part:1085377743>
    MESSAGE_REGEX = re.compile(r'<part:(\d+)>(.*)</part:(\d+)>', re.DOTALL)
    match = MESSAGE_REGEX.search(lines)
    if not match:
        return []

    ret = match.group(2).splitlines()
    if not ret[0]:
        ret.pop(0)
    if not ret[-1]:
        ret.pop()
    return ret


def main():
    with serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=0.5) as arduino:
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
    logging.basicConfig(level=logging.DEBUG)
    main()
