import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
import sys

if len(sys.argv) < 2:
    print("Использование: python inertia.py <файл_с_данными>")
    print("Пример: python inertia.py data.txt")
    sys.exit(1)

filename = sys.argv[1]

data = np.array([float(line.strip()) for line in open(filename)]).reshape(-1, 1)

k_values = range(2, 18)
inertias = [KMeans(k, n_init=18).fit(data).inertia_ for k in k_values]

plt.plot(k_values, inertias, 'bo-')
plt.xlabel('k')
plt.ylabel('Инерция')
plt.grid()
plt.title('Метод локтя')

output = sys.argv[1].replace('.txt', '_elbow.png')
plt.savefig(output, dpi=150)

for k, i in zip(k_values, inertias):
    print(f"k={k}: {i:.2f}")
