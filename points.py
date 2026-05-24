import sys
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler
import numpy as np

K = int(sys.argv[2] or 10)
name = sys.argv[1]

points = np.loadtxt("data/" + name + ".txt", ndmin=2)
scaled = StandardScaler().fit_transform(points)
kmeans = KMeans(n_clusters=K, n_init=20).fit(scaled)
labels = kmeans.labels_
centers = kmeans.cluster_centers_

size = 0

for cl in range(K):
    if (np.sum(labels == cl)) >= 10:
        size += 1

with open("data/" + name + "_cl.txt", "w") as f:
    f.write(str(size) + " ")
    for cl in range(K):
        idxs = np.where(labels == cl)[0]
        dists = np.linalg.norm(scaled[idxs] - centers[cl], axis=1)
        nearest = idxs[np.argsort(dists)[:10]]
        if (np.sum(labels == cl) >= 10):
            f.write(" ".join(map(str, nearest)) + " ")

with open("data/" + name + "_s.txt", "w") as f:
    f.write(str(size) + " ")
    for cl in range(K):
        if (np.sum(labels == cl) >= 10):
            f.write(str(np.sum(labels == cl)) + " ")
