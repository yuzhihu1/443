import subprocess
import sys
#import matplotlib.pyplot as plt
# total bytes of the file
TOTAL_BYTES = 52428800

# block size that I am going to test
BLOCK_SIZE = [
    (100, "100B"),
    (512, "512B"),
    (1024, "1kB"),
    (8192, "8KB"),
    (65536, "64KB"),
    (262144, "256KB"),
    (524288, "512KB"),
    (1048576, "1MB"),
    (1048576*2, "2MB"),
    (1048576*3, "3MB"),
]


def creat_ranrom_file(filename, totalbytes, block_size):
    result = subprocess.run([
        './create_random_file', filename, str(totalbytes), str(block_size),
    ], stdout=subprocess.PIPE,)

    return int(result.stdout)


if __name__ == '__main__':
    # put data in the list waiting to be plotted
    data_to_plot = [[], []]
    for block_size, name in BLOCK_SIZE:
        print("========={}========".format(name))
        for i in range(5):
            result = creat_ranrom_file("testfile", TOTAL_BYTES, block_size)
            rate = (float(1000*TOTAL_BYTES)/result)
            print(rate)
            data_to_plot[0].append(block_size)
            data_to_plot[1].append(rate)
    # plt.plot(data_to_plot[0], data_to_plot[1], 'ro')
    # plt.ylabel('read rate bytes/sec')
    # plt.xlabel('block_size')
    # plt.xscale('log')
    # plt.show()
