from collections import defaultdict
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np


def main():

    # get files from this directory in *ordered.txt format
    outputPath = Path('./output')
    orderedPaths = [orderedPath for orderedPath in outputPath.glob('*ordered.txt')]

    # extract names of compression methods from file names
    comp_symbols = [str(orderedPath)[7:-11] for orderedPath in orderedPaths]

    # Structures for storing values for each column
    uncompressPoints = []
    decompressPoints = defaultdict(list)
    distances = defaultdict(list)
    r_diffs = defaultdict(list)

    # Metrics for each compression method
    avg_distance = defaultdict(float)
    avg_r_diffs = defaultdict(float)

    # read files and insert values for each structure
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
            avg_r_diffs[symbol] = np.average(r_diffs[symbol])

    # number of points
    element_vertex = len(uncompressPoints)


    # point_id vs distance plots 
    fig, axes = plt.subplots(3, 1, sharex=True)
    fig.suptitle('Comparision of the methods based on differences in distance')
    fig.subplots_adjust(hspace=0.6)
    for ax, symbol in zip(axes, comp_symbols):
        ax.scatter(range(1, element_vertex + 1), distances[symbol])
        ax.hlines(avg_distance[symbol], 1, element_vertex, 'yellow', linewidths=1.5)
        ax.set_title('Method {}'.format(symbol))
        ax.set_xlabel('point_id')
        ax.set_ylabel('distances')

    plt.savefig(outputPath / 'point_vs_distance.pdf')
    

    # point_id vs r_diff plots    
    fig, axes = plt.subplots(3, 1, sharex=True)
    fig.suptitle('Comparision of the methods based on differences in reflectivity difference')
    fig.subplots_adjust(hspace=0.6)
    for ax, symbol in zip(axes, comp_symbols):
        ax.bar(range(1, element_vertex + 1), r_diffs[symbol])
        ax.hlines(avg_r_diffs[symbol], 1, element_vertex, 'yellow', linewidths=1.5)
        ax.set_title('Method {}'.format(symbol))
        ax.set_xlabel('point_id')
        ax.set_ylabel('r_diffs')

    plt.savefig(outputPath / 'point_vs_r_diff.pdf')


if __name__ == '__main__':
    main()