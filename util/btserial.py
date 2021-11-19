#!/usr/bin/env python3
import time

import serial


# http://myosuploads3.banggood.com/products/20190129/20190129043725SKUA87502.pdf
# https://medium.com/@yostane/using-the-at-09-ble-module-with-the-arduino-3bc7d5cb0ac2


def read_all(s: serial.Serial) ->None:
  last = b''
  while True:
    line = s.readline()
    if not line:
      return
    last = line
    print(line)

def run_command(s: serial.Serial, cmd: bytes) -> None:
  if not cmd.startswith(b'AT'):
    s.write(b'AT+')
  s.write(cmd)
  s.write(b'?\n')
  s.flush()

  read_all(s)



def pyserial_exp() -> None:
  with serial.Serial('/dev/ttyUSB0', 9600, timeout=1) as s:
    run_command(s, b'HELP')
    while True:
      read_all(s)
    # run_command(s, b'AT')
    # run_command(s, b'DEFAULT') # Reset to factory settings
    # run_command(s, b'PIN')
    # run_command(s, b'IAC')
    # run_command(s, b'ROLE')
    # run_command(s, b'VERSION')
    # run_command(s, b'BAUD')
    # run_command(s, b'NAME')
    # run_command(s, b'LSP')
    # run_command(s, b'LADDR')
    # run_command(s, b'COD')
    # run_command(s, b'RESETPDL')
    # run_command(s, b'STATE')
    # Only on BLE adapters, our BT module is not BLE, but only Bluetooth classic.
    # run_command(s, b'UUID')
    # run_command(s, b'CHAR')

def ble_exp() -> None:
  pass


if __name__ == '__main__':
  pyserial_exp()
