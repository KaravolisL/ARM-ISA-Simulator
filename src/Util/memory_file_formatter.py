import sys

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
        i = i + 1

    # Close files
    input_file.close()
    output_file.close()


if __name__ == '__main__':

    # argparser here

    if (len(sys.argv) < 2):
        print("Please include the name of the file to translate")
        sys.exit()
    else:
        input_file_name = sys.argv[1]

    read_and_format_file(input_file_name)

    print("Memory file formatting complete: SUCCESS")