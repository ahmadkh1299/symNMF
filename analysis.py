import symnmf as nmf
from sklearn.metrics import silhouette_score
def distance(point1, point2):
    total = 0
    for i in range(len(point1)):
        total += (point1[i] - point2[i]) ** 2
    total = total ** 0.5
    return total


def clustering(centroids_Arr, Points_Arr, ListsOfClusters):
    min = None
    index = 0
    for i in range(len(Points_Arr)):
        for j in range(len(centroids_Arr)):
            dist = distance(centroids_Arr[j], Points_Arr[i])
            if (min is None) or (dist < min):
                min = dist
                index = j
        ListsOfClusters[index].append(i)
        min = None
        index = 0

def Avg(lst, Points_Arr):
    avg_point = []
    d = len(Points_Arr[0])
    for i in range(d):
        sum = 0
        for item in lst:
            sum += Points_Arr[item][i]
        sum = sum / len(lst)
        avg_point.append(sum)
    return avg_point


def kmeans(k, max_iter, Points_Arr):
    centroids_Arr = []

    for i in range(k):
        centroids_Arr.append(Points_Arr[i])

    for i in range(max_iter):
        ListsOfClusters = []
        for i in range(k):
            ListsOfClusters.append([])
        clustering(centroids_Arr, Points_Arr, ListsOfClusters)
        boolean = True
        for j in range(len(centroids_Arr)):
            old_avg = centroids_Arr[j]
            centroids_Arr[j] = Avg(ListsOfClusters[j], Points_Arr)
            dist = distance(centroids_Arr[j], old_avg)
            if (dist > 0.001):
                boolean = False
        if (boolean == True):
            break

    for i in range(len(centroids_Arr)):
        for j in range(len(centroids_Arr[0])):
            x = centroids_Arr[i][j]
            centroids_Arr[i][j] = "%.4f" % round(x, 4)

    return ListsOfClusters






# main

import sys
args = sys.argv

if(args[1].isdigit()==False):
    print("Invalid Input!")
    sys.exit()

k = int(args[1])
inputfile = args[2]
maxiter=200

# read data
file = open(inputfile)
read_file = file.read()
Points_Arr = read_file.splitlines()

if (k > len(Points_Arr)) or (k <= 1) or (maxiter < 1):
    print("Invalid Input!")
    sys.exit()

for i in range(len(Points_Arr)):
    Points_Arr[i] = Points_Arr[i].split(",")
    for j in range(len(Points_Arr[i])):
        Points_Arr[i][j] = float(Points_Arr[i][j])





#NMF
H = nmf.Perform_goal(inputfile, "symnmf", k)

Lables_Snmf=[0 for i in range(len(Points_Arr))]


for i in range(len(Points_Arr)):
    max_indx = 0
    for j in range(k):

        if(H[i][max_indx]<H[i][j]):
            max_indx=j
    Lables_Snmf[i]=max_indx

Snmf_silhouette = silhouette_score(Points_Arr, Lables_Snmf, metric='euclidean')




#HW1
KMEANS_HW1=kmeans(k, maxiter, Points_Arr)

Lables_Kmeans=[0 for i in range(len(Points_Arr))]
for i in range(k):
    for point in KMEANS_HW1[i]:
        Lables_Kmeans[point]=i


kmeans_silhouette = silhouette_score(Points_Arr, Lables_Kmeans, metric='euclidean')


# print output
print("nmf: ", f"{Snmf_silhouette:.4f}")
print("kmeans: ", f"{kmeans_silhouette:.4f}")





