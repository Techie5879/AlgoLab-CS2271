import numpy as np
import csv
import matplotlib.pyplot as plt


random_numbers = np.zeros(int(10e6))

with open('./rand_normal.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    i = 0
    for row in csv_reader:
        random_numbers[i] = row[0]
        i += 1

plt.figure("Histogram for Normal Distribution Dataset")
plt.title("Histogram for Normal Distribution Dataset")
plt.xlabel("Number")
plt.ylabel("No. of Occurrences")
plt.hist(random_numbers, bins=range(101))
plt.show()



