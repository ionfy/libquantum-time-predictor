import numpy as np
from sklearn.cluster import KMeans
import sys


if len(sys.argv) < 3:
    print("Использование: python script.py <файл> <кол-во кластеров>")
    sys.exit(1)

clusters_count = int(sys.argv[2])

data = np.array([float(l.strip()) for l in open(sys.argv[1]) if l.strip()]).reshape(-1, 1)
print(f"Файл: {sys.argv[1]}, точек: {len(data)}")

kmeans = KMeans(n_clusters=clusters_count, n_init=100).fit(data)

labels = kmeans.labels_

fake_count = clusters_count;

print("\n {", end = "")
for cluster in range(clusters_count):
    cluster_points = data[labels == cluster]
    print(f"{len(cluster_points):6d}, ", end = "")
    if (len(cluster_points) < 10):
        fake_count -= 1
        continue
print("}")

output = sys.argv[1].replace('.txt', '_s.txt')
f = open(output, "w");
f.write(f"{fake_count} ")
for cluster in range(clusters_count):
    cluster_points = data[labels == cluster]
    if (len(cluster_points)>=10):
        f.write(f"{len(cluster_points)} ")
f.close()

print("\n {")

output = sys.argv[1].replace('.txt', '_cl.txt')
f = open(output, "w");

output = sys.argv[1].replace('.txt', '_real.txt')
f2 = open(output, "w");



f.write(f"{fake_count} ")

for cluster in range(clusters_count):
    print("  ", end = "")
    cluster_points = data[labels == cluster]
    cluster_indices = np.where(labels == cluster)[0]
    center = kmeans.cluster_centers_[cluster]
    
    distances = np.abs(cluster_points - center)
    n_nearest = min(10, len(cluster_points))
    nearest_idx = np.argsort(distances.flatten())[:n_nearest]
        
    for i, idx in enumerate(nearest_idx, 1):
        orig_idx = cluster_indices[idx]
        print(f"{orig_idx:6d}, ", end = "")
        
        if (len(cluster_points)>=10):
            f.write(f"{orig_idx} ")
            f2.write(f"{int(data[orig_idx][0])}\n")

    
    print()


f.close()
f2.close()
print("}")

