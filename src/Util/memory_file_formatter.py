# Standard Libraries
from argparse import ArgumentParser
import os
import sys

import logging
logger = logging.getLogger(__name__)

EXIT_SUCCESS = 0
HEX_CHARACTERS_PER_BYTE = 2
WORDS_PER_ROW = 16
WORD_SIZE_IN_BYTES = 4
STARTING_MEMORY_ADDRESS = 0x20000000
ENDIANNESS = 'little'

def read_and_format_file(input_file_name, output_file_name=None):

    if (output_file_name == None):
        output_file_name = input_file_name.rsplit('.')[0] + '_formatted.txt'

    # Open files
    input_file = open(input_file_name, 'rb')
    output_file = open(output_file_name, 'w')

    memory_address_label = STARTING_MEMORY_ADDRESS

    i = 0
    word = input_file.read(WORD_SIZE_IN_BYTES)
    while (word):
        if (i % WORDS_PER_ROW == 0):
            output_file.write('\n0x{:X}: '.format(memory_address_label))
            memory_address_label = memory_address_label + WORDS_PER_ROW
        data = int.from_bytes(word, byteorder=ENDIANNESS)
        output_file.write('{:0{}X} '.format(data, WORD_SIZE_IN_BYTES * HEX_CHARACTERS_PER_BYTE))
        word = input_file.read(WORD_SIZE_IN_BYTES)
        i += 1

    # Close files
    input_file.close()
    output_file.close()

def main():
    argument_parser = ArgumentParser(
        prog='python memory_file_formatter memory_file',
        description='Converts a binary file to a formatted memory display'
    )
    argument_parser.add_argument('memory_file')
    argument_parser.add_argument('--verbose', '-v', action='store_true')
    args = argument_parser.parse_args()

    if not os.path.isfile(args.memory_file):
        raise ValueError("File {} does not exist".format(args.memory_file))

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)
    else:
        logging.basicConfig(level=logging.INFO)

    read_and_format_file(args.memory_file)

    logger.info("Memory file formatting complete: SUCCESS")

    return EXIT_SUCCESS


if __name__ == '__main__':
    sys.exit(main())
