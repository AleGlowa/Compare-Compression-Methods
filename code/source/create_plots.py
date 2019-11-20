from collections import defaultdict
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np


def main():
    outputPath = Path('./output')
    orderedPaths = [orderedPath for orderedPath in outputPath.glob('*ordered.txt')]
    comp_symbols = [str(orderedPath)[7:-11] for orderedPath in orderedPaths]


    uncompressPoints = []
    decompressPoints = defaultdict(list)
    distances = defaultdict(list)
    r_diffs = defaultdict(list)
    avg_distance = defaultdict(float)


    for orderedPath, symbol in zip(orderedPaths, comp_symbols):
        with open(orderedPath) as orderedFile:
            for line in orderedFile:
                line = line.rstrip().split()
                line = list(map(float, line))
                if symbol == comp_symbols[0]:
                    uncompressPoints.append(tuple([line[0], line[1], line[2], line[3]]))
                decompressPoints[symbol].append(tuple([line[4], line[5], line[6], line[7]]))
                distances[symbol].append(line[8])
                r_diffs[symbol].append(line[9])
            
            avg_distance[symbol] = np.average(distances[symbol])

    element_vertex = len(uncompressPoints)

    # point_id vs distance plots
    fig, axes = plt.subplots(3, 1, sharex=True)
    fig.suptitle('Comparision of the methods based on differences in distance')
    fig.subplots_adjust(hspace=0.6)
    for ax, symbol in zip(axes, comp_symbols):
        ax.scatter(range(1, element_vertex + 1), distances[symbol])
        ax.hlines(avg_distance[symbol], 1, element_vertex, 'yellow', linewidths=2)
        ax.set_title('Method {}'.format(symbol))
        ax.set_xlabel('point_id')
        ax.set_ylabel('distances')

    plt.savefig(outputPath / 'point_vs_distance.pdf')

    #plt.show()

    


if __name__ == '__main__':
    main()