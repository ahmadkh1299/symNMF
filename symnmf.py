import math
import sys
import pandas as pd
import numpy as np
import symNMF as SNMF


def Perform_goal(file_name, goal, k):
    filePD = pd.read_csv(file_name, header=None)
    np_array = filePD.to_numpy()
    np_array = np_array.tolist()
    N = len(np_array)
    d = len(np_array[0])
    if goal != "symnmf":
        final_mat = SNMF.perform_goal(np_array, goal, N, k, d, None)
    else:
        W_mat = SNMF.perform_goal(np_array, "norm", N, k, d, None)
        H = initial_H(W_mat, N, d, k)
        final_mat = SNMF.perform_goal(np_array, "symnmf", N, k, d, H)

    return final_mat


def print_H(H):
    for i in range(len(H)):
        for j in range(0, len(H[i]) - 1):
            print("%.4f," % H[i][j], end='')
        print("%.4f" % H[i][len(H[i]) - 1])

def initial_H(W_mat: np, N, d, k) -> np:
    try:
        m = (np.sum(np.array(W_mat))) / (pow(N,2))
        H = np.random.uniform(0,2*np.sqrt(m/k),size=(N,k))
        return H.tolist()
    except:
        print("An Error Has Occurred")
        raise Exception("")


# main
np.random.seed(0)
if(len(sys.argv)==4):
    k = int(sys.argv[1])
    goal = sys.argv[2]
    file_name = sys.argv[3]
    if ((goal != "symnmf" and goal != "sym" and goal != "norm" and goal != "ddg") or k < 0):
        print("An Error Has Occurred")
    else:
        H = Perform_goal(file_name, goal, k)
        print_H(H)

