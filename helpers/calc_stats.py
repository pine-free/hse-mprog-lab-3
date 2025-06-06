import statistics
import math
import os
import itertools
from dataclasses import dataclass, field
import csv
import shutil
from contextlib import suppress

@dataclass
class Sample:
    file: str = field(init=True)
    _data: list[int] | None = None

    def __post_init__(self):
        with open(file) as f:
            data = f.read()

        nums = [int(n) for n in data.strip().split('\n')]
        self._data = nums

    @property
    def size(self) -> int:
        return len(self._data)

    def mean(self) -> float:
        return statistics.mean(self._data)

    def std(self) -> float:
        mean = self.mean()
        deviations = [(n - mean)**2 for n in self._data]
        return statistics.sqrt(statistics.mean(deviations))

    def varcoef(self) -> float:
        mean = self.mean()
        std = self.std()
        return std/mean

    def chi_sq(self) -> float:
        k = int(math.log2(self.size))
        max_val = max(self._data)
        normalized = sorted([n / max_val for n in self._data])

        chunks = []
        for key, g in itertools.groupby(normalized, key=lambda x: x // (1/k)):
            c = list(g)
            print(f"{key=} {len(c)=}")
            chunks.append(c)

        chi_vals = []

        for chunk in chunks:
            n_i = len(chunk)
            p_i = 1/k
            res = n_i ** 2 / p_i - self.size
            chi_vals.append(res)

        chi_val = sum(chi_vals) / self.size
        return chi_val


SAMPLES_DIR = 'samples'
DATA_DIR = 'data'

target = os.path.join(DATA_DIR, 'stats.csv')

with suppress(FileNotFoundError):
    os.remove(target)

with open(target, 'w') as f:
    writer = csv.DictWriter(f, fieldnames=['file', 'mean', 'std', 'varcoef'])
    writer.writeheader()

    for sample_f in sorted(os.listdir(SAMPLES_DIR)):
        file = os.path.join(SAMPLES_DIR, sample_f)
        sample = Sample(file=file)

        writer.writerow({'file': sample_f, 'mean': sample.mean(), 'std': sample.std(), 'varcoef': sample.varcoef()})


    
    
