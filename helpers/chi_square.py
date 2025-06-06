import os
import csv

from calc_stats import Sample, SAMPLES_DIR, DATA_DIR

target = os.path.join(DATA_DIR, 'chi_sq.csv')
with open(target, 'w') as f:
    writer = csv.DictWriter(f, fieldnames=['file', 'chi_sq'])
    writer.writeheader()

    for sample_f in sorted(os.listdir(SAMPLES_DIR)):
        file = os.path.join(SAMPLES_DIR, sample_f)
        sample = Sample(file=file)

        print(f"{file=}")
        writer.writerow({'file': sample_f, 'chi_sq': sample.chi_sq()})


