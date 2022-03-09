#!/bin/python3

import os
import shutil
import argparse
import tempfile
from pathlib import Path
import shutil

parser = argparse.ArgumentParser()
parser.add_argument('-i', '--input-file', nargs=1, help='input z80 instruction')
parser.add_argument('-o', '--output-file', nargs=1, default=['./roms/dmg_rom.txt'], help="output file, generated in a C array format")
args = parser.parse_args()

with tempfile.NamedTemporaryFile() as tmp:
    with open(args.output_file[0], 'w') as of:
        my_file = Path(args.output_file)
        if my_file.is_file():
            shutil.copyfile(args.output_file, f'{args.output_file}.bkp')
        os.system(f'z80asm -i {args.input_file[0]} -o {tmp.name}')
        assmebled = tmp.read()
        out = ''
        for n, b in enumerate(assmebled):
            if n % 16 == 0:
                out += '\n' 
            out += f'{hex(b)}, '
        of.write(out)
