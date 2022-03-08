# Based on work: https://int-i.github.io/python/2021-11-07/matplotlib-google-benchmark-visualization/

from argparse import ArgumentParser
from itertools import groupby
from cycler import cycler
from random import randint
import json
import math
import operator
import matplotlib as mpl
import matplotlib.pyplot as plt


def generate_color(size):
    colors = []

    for i in range(size):
        colors.append('#%06X' % randint(0, 0xFFFFFF))

    colors = sorted(set(colors), key=colors.index)  # Remove all same elements
    return colors


def extract_label_from_benchmark(benchmark):
    bench_full_name = benchmark['name']
    bench_name = bench_full_name.split('/')[0]  # Remove all after /
    if (bench_name.startswith('BM_')):  # Remove if string start with BM_
        return bench_name[3:]  # Remove BM_
    else:
        return bench_name


def extract_size_from_benchmark(benchmark):
    bench_name = benchmark['name']
    return bench_name.split('/')[1]  # Remove all before /


if __name__ == "__main__":
    plt.rcParams['figure.figsize'] = [21, 12]
    mpl.rcParams['axes.prop_cycle'] = cycler(color=generate_color(200))

    parser = ArgumentParser()
    parser.add_argument('path', help='benchmark result json file')
    args = parser.parse_args()

    with open(args.path) as file:
        benchmark_result = json.load(file)
        benchmarks = benchmark_result['benchmarks']
        elapsed_times = groupby(benchmarks, extract_label_from_benchmark)
        for key, group in elapsed_times:
            benchmark = list(group)
            x = list(map(extract_size_from_benchmark, benchmark))
            y = list(map(operator.itemgetter('bytes_per_second'), benchmark))
            #log_y = list(map(math.log, y))
            plt.plot(x, y, label=key, marker=None)

        plt.grid(color='green', linestyle='--', linewidth=0.2)  # Add grid
        plt.xlabel('Array size')
        plt.ylabel('Gigabyte per second (GB/s)')
        plt.title('CRC32 Algorithm Benchmark')
        plt.legend()
        plt.savefig('benchmark.png', bbox_inches='tight', dpi=300)
        # plt.savefig('benchmark.svg')
        plt.show()
