import numpy as np
import scipy.optimize as opt
from matplotlib import pyplot as plt


# maximize: f(x) = min(c^T * x); x1 + ... + x2 == k; x1, ..., x2 >= 0 ->
# -> maximize: y; y - c^T * x <= 0; x1 + ... + x2 == k; x1, ..., x2 >= 0 ->
# -> minimize: -y, -//-.
def vyhra(c, k):
    A_ub = np.array([[1, -c[0], -c[1],     0,     0,     0],
                     [1,     0, -c[1], -c[2], -c[3],     0],
                     [1,     0,     0,     0, -c[3], -c[4]]])
    b_ub = np.array([0, 0, 0])

    A_eq = np.array([[0, 1, 1, 1, 1, 1]])
    b_eq = np.array([k])

    new_c = np.array([-1, 0, 0, 0, 0, 0])

    r = opt.linprog(new_c, A_ub, b_ub, A_eq, b_eq)

    return r.x[1:]

# maximize: f(x) = min(c^T * x); x1 + ... + x2 == k; x1, ..., x2 >= m ->
# -> maximize: y; y - c^T * x <= 0; x1 + ... + x2 == k; x1, ..., x2 >= m ->
# -> minimize: -y, -//-.
def vyhra2(c, k, m):
    A_ub = np.array([[1, -c[0],     0,     0],
                     [1,     0, -c[1],     0],
                     [1,     0,     0, -c[2]]])
    b_ub = np.array([0, 0, 0])

    A_eq = np.array([[0, 1, 1, 1]])
    b_eq = np.array([k])

    new_c = np.array([-1, 0, 0, 0])

    bounds = [(0, None)] + [(m, None)] * 3

    r = opt.linprog(new_c, A_ub, b_ub, A_eq, b_eq, bounds)

    return r.x[1:]

# minimize: maxi|a^T * xi + b - yi| ->
# -> minimize: z; -z - a^T * xi - b <= -yi; -z + a^T * xi + b <= yi, for all i
def minimaxfit(x,y):
    m, n = x.shape
    A_ub = np.concatenate((
        np.array([[-1] + list(-xi) + [-1] for xi in x.T]),
        np.array([[-1] + list(xi) + [1] for xi in x.T])
    ), axis=0)
    b_ub = np.concatenate((-y[0], y[0]))

    c = np.zeros(m + 2)
    c[0] = 1

    bounds = [(0, None)] + [(None, None)] * (m + 1)

    res = opt.linprog(c, A_ub, b_ub, None, None, bounds)

    return res.x[1: m + 1], res.x[-1], res.x[0]

def plotline(x, y, a, b, r):
    # x_range = np.linspace(-100, 100, 1000)
    x = x.flatten()
    y = y.flatten()
    # a = float(a)
    yu = a * x + b + r
    ym = a * x + b
    yl = a * x + b - r

    plt.grid(True)
    plt.grid(True, linewidth=0.1)
    # plt.xlim(-100, 100)
    # plt.ylim(-100, 100)
    plt.plot(x, y, 'bx', label='body')
    plt.plot(x, yu, 'r-')
    plt.plot(x, yl, 'r-')
    plt.plot(x, ym, 'g-')
    plt.axis('tight')
    plt.axis('equal')
    plt.show()

if __name__ == '__main__':
    c = np.array([1.27, 1.02, 4.70, 3.09, 9.00])
    k = 3000
    x = vyhra(c, k)
    print(x)

    # x = array([3.40905816e-06, 2.69461077e+03, 9.28004584e-07, 1.68174891e-08, 3.05389222e+02]) or
    # x = [3.40905816e-06, 2.69461077e+03, 9.28004584e-07, 1.68174891e-08, 3.05389222e+02] etc.

    c = np.array([1.27, 4.70, 9.00])
    k = 3000
    m = 400
    x = vyhra2(c, k, m)
    print(x)

    # x = array([2046.90108498,  553.09881711,  400.00004477]) or
    # x = [2046.90108498,  553.09881711,  400.00004477] etc.

    x = np.array([[1, 2, 3, 3, 2], [4, 1, 2, 5, 6], [7, 8, 9, -5, 7]])
    y = np.array([[7, 4, 1, 2, 5]])
    a, b, r = minimaxfit(x, y)
    print(a, b, r)

    # a = [-2.776, 0.194, -0.030]
    # b = 9.403
    # r = 0.194

    plt.switch_backend('TkAgg')
    plt.plot()
    plt.grid(True)
    plt.grid(True, linewidth=0.1)
    plt.axis('tight')
    plt.axis('equal')
    # plt.xlim(-100, 100)
    # plt.ylim(-100, 100)
    points = plt.ginput(-1)
    plt.close()

    x = np.array([[p[0] for p in points]])
    y = np.array([[p[1] for p in points]])

    a, b, r = minimaxfit(x, y)
    plotline(x, y, a, b, r)



