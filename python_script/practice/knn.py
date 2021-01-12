import numpy as np

def computeKNNMat(X):
    n,m = X.shape
    G = np.dot(X,X.T)
    H = np.tile(np.diag(G), (n,1))
    print(H)
    return H + H.T - 2 * G
if __name__ == '__main__':
    X = np.array([[1,0,0],[1,0,3]])
    print(np.dot(X.T,X))
    ans = computeKNNMat(X)
    print(ans)