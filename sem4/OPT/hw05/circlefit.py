import scipy.io as sio
import numpy as np
from math import pi
from matplotlib import pyplot as plt

def quad_to_center(d,e,f):
    x0 = -d/2
    y0 = -e/2
    r = np.sqrt(-f + (e**2)/4 + (d**2)/4)

    return x0, y0, r

def fit_circle_nhom(X):
    A = np.hstack((X, np.ones((X.shape[0], 1))))
    b = -np.sum(X**2, axis=1)
    res, _, _, _ = np.linalg.lstsq(A, b, rcond=None)
    d, e, f = res

    return d, e, f

def fit_circle_hom(X):
    A = np.hstack(((np.sum(X**2, axis=1)).reshape(-1, 1), X, np.ones((X.shape[0], 1))))
    U, S, V = np.linalg.svd(A)
    a, d, e, f = V[-1]

    return d/a, e/a, f/a

def dist(X, x0, y0, r):
    return np.linalg.norm(X - np.array([x0,y0]), axis=1) - r

def fit_circle_ransac(X, num_iter, threshold):
    best_params = None
    best_inliers_num = -np.inf
    for i in range(num_iter):
        indxs = np.random.choice(X.shape[0], 3, replace=False)
        d,e,f = fit_circle_nhom(X[indxs])
        x0, y0, r = quad_to_center(d,e,f)

        inliers_num = np.sum(np.abs(dist(X, x0, y0, r)) < threshold)
        if(inliers_num > best_inliers_num):
            best_inliers_num = inliers_num
            best_params = [x0, y0, r]

    return best_params

def plot_circle(x0,y0,r, color, label):
    t = np.arange(0,2*pi,0.01)
    X = x0 + r*np.cos(t)
    Y = y0 + r*np.sin(t)
    plt.plot(X,Y, color=color, label=label)

if(__name__ == '__main__'):
    data = sio.loadmat('data.mat')
    X = data['X'] # only inliers
    A = data['A'] # X + outliers

    def_nh = fit_circle_nhom(X)
    x0y0r_nh = quad_to_center(*def_nh)
    dnh = dist(X, *x0y0r_nh)

    def_h = fit_circle_hom(X)
    x0y0r_h = quad_to_center(*def_h)
    dh = dist(X, *x0y0r_h)

    results = {'def_nh':def_nh, 'def_h':def_h, 
               'x0y0r_nh' : x0y0r_nh, 'x0y0r_h': x0y0r_nh,
               'dnh': dnh, 'dh':dh}
    
    GT = sio.loadmat('GT.mat')
    for key in results:
        print('max difference',  np.amax(np.abs(results[key] - GT[key])), 'in', key)


    x = fit_circle_ransac(A, 2000, 0.1)

    plt.figure(1)
    plt.subplot(121)
    plt.scatter(X[:,0], X[:,1], marker='.', s=3)
    plot_circle(*x0y0r_h, 'r', 'hom')
    plot_circle(*x0y0r_nh, 'b', 'nhom')
    plt.legend()
    plt.axis('equal')    
    plt.subplot(122)
    plt.scatter(A[:,0], A[:,1], marker='.', s=2)
    plot_circle(*x, 'y', 'ransac')
    plt.legend()
    plt.axis('equal')
    plt.show()
    
