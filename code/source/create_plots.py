import sys
from collections import defaultdict
import matplotlib.pyplot as plt


def main():
    uncompressPoints = []
    decompressPoints = defaultdict(list)
    fileA = open(sys.argv[1], 'r')
    fileB = open(sys.argv[2], 'r')
    fileC = open(sys.argv[3], 'r')

    for line in fileA:
        line = line.rstrip().split()
        line = list(map(float, line))
        uncompressPoints.append(tuple([line[0], line[1], line[2], line[3]]))
        decompressPoints['A'].append(tuple([line[4], line[5], line[6], line[7]]))
        #print(decompressPoints['A'][-1])

    #print(decompressPoints['A'])
    #print(type(uncompressPoints[-1]))

    fileC.close()
    fileB.close()
    fileA.close()


if __name__ == '__main__':
    main()