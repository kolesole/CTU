import numpy as np

def grad_f(x, y):
    df_dx = 2 * x - 2 * np.cos(y**2 - 2 * x)
    df_dy = -1 + 2 * y * np.cos(y**2 - 2 * x)
    return np.array([df_dx, df_dy])

def inv_hess_f(x, y):
    h_xx = 2 - 4 * np.sin(y**2 - 2 * x)
    h_xy = 4 * y * np.sin(y**2 - 2 * x)
    h_yy = 2 * np.cos(y**2 - 2 * x) - 4 * y**2 * np.sin(y**2 - 2 * x)
    return np.linalg.inv(np.array([[h_xx, h_xy], [h_xy, h_yy]]))

def newton(start_point, max_iter = 100, eps = 1e-10):
    x = start_point
    for i in range(max_iter):
        grad = grad_f(x[0], x[1])
        inv_hess = inv_hess_f(x[0], x[1])
        new_x = x - inv_hess @ grad
        print(f'{i + 1}. iter.: {x} -> {new_x}')
        if (np.linalg.norm(new_x - x) < eps):
            return
        x = new_x

if __name__ == '__main__':
    newton(np.array([1.0, 1.0]))