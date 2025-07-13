import numpy as np

def fit_wages(t, M):
    A = np.column_stack((np.ones(t.shape), t))      # M(t) = x1 + x2 * t
    y = M
    x = np.linalg.lstsq(A, y)[0]
    return x

def quarter2_2009(x):
    return x @ np.array([1, 2009.25])

mdata = np.loadtxt("mzdy.txt")
mx = fit_wages(mdata[:, 0], mdata[:, 1])
print(quarter2_2009(mx))
print(mx.dtype)

def fit_temps(t, T, omega):                    # T(t) = x1 + x2t + x3sin(ωt) + x4cos(ωt)
    A = np.column_stack((np.ones(t.shape), t, np.sin(omega * t), np.cos(omega * t)))
    y = T
    x = np.linalg.lstsq(A, y)[0]
    return x

tdata = np.loadtxt("teplota.txt")
omega = 2 * np.pi / 365
tx = fit_temps(tdata[:, 0], tdata[:, 1], omega)
print(tx)

