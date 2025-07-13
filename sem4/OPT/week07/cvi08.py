import numpy as np
import matplotlib.pyplot as plt

def f(x):
    a = 1
    return (x**2 - a)**2

def fast_plot(f, x):
    plt.plot(x, f(x), label='f(x)')
    plt.title('func. graph f(x)')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.grid(True)
    plt.legend()
    plt.axhline(0, color='black', linewidth=0.5)
    plt.axvline(0, color='black', linewidth=0.5)
    plt.show()

if __name__ == '__main__':
    fast_plot(f, np.linspace(-1.5, 1.5, 400))

