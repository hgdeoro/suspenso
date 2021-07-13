import dataclasses
import logging
import pathlib
import subprocess
import threading
from time import time

import serial

from suspensopy import serial_client


class SubProcessOnThread(threading.Thread):
    def __init__(self, stdout, stderr, *args, **kwargs):
        super(*args, **kwargs)
        self.process: subprocess.Popen = None
        self.stdout = stdout
        self.stderr = stderr
        self.returncode = None

    def run(self):
        self.process = subprocess.Popen(["netcat", "-u", "-s", "0.0.0.0", "-p", "4545", "-l"],
                                        stdout=self.stdout,
                                        stderr=self.stderr)
        while True:
            try:
                self.returncode = self.process.wait(timeout=1.0)
            except subprocess.TimeoutExpired:
                pass


@dataclasses.dataclass
class PerfTest:
    name: str
    menu: str


def main():
    with serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=0.5) as arduino:
        serial_client.readlines(arduino)  # clean buffer
        print("> sending 'a'")
        arduino.write(b'a')

        print("> waiting for response...")
        response = serial_client.readlines(arduino)
        print("> -------------------- RESPONSE: ")
        print('\n'.join(response))
        print("> -------------------- MESSAGE: ")
        print('\n'.join(serial_client.parse_message(response)))
        print("> done")

    TESTS = [
        PerfTest(name='flood_single_datapoint_string', menu='c'),
        # PerfTest(name='flood_single_datapoint_string', menu='d'),
        PerfTest(name='flood_single_datapoint_two_writes', menu='f'),
        # PerfTest(name='flood_single_datapoint_two_writes', menu='g'),
        PerfTest(name='flood_multiple_datapoint_struct', menu='i'),
        # PerfTest(name='flood_multiple_datapoint_struct', menu='k'),
    ]

    with serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=10.0) as arduino:
        start_time = int(time())
        for test in TESTS:
            stdout_filename = f'{start_time}-netcat-stdout-{test.menu}-{test.name}.raw'
            stderr_filename = f'{start_time}-netcat-stderr-{test.menu}-{test.name}.raw'
            serial_output_filename = f'{start_time}-serial-{test.menu}-{test.name}.txt'

            with open(stdout_filename, 'bw') as stdout:
                with open(stderr_filename, 'bw') as stderr:
                    netcat = subprocess.Popen(["netcat", "-u", "-s", "0.0.0.0", "-p", "4545", "-l"],
                                              stdout=stdout,
                                              stderr=stderr)

                    print(f"> sending menu '{test.menu}'")
                    arduino.write(test.menu.encode('ascii'))

                    print("> waiting for response...")
                    response = serial_client.readlines(arduino)
                    print("> -------------------- RESPONSE: ")
                    print('\n'.join(response))
                    print("> -------------------- MESSAGE: ")
                    message = serial_client.parse_message(response)

                    print('\n'.join(message))
                    print("> done")

                    pathlib.Path(serial_output_filename).write_text('\n'.join(message))

                    netcat.terminate()
                    print("Wait for subprocess...")
                    netcat.wait()
                    print("Subprocess done")


if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG)
    main()
