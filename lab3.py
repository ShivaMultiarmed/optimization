from collections.abc import Callable

import numpy
import sympy
from sympy.abc import x, y

E = 1e-6
PHI = (1 + 5 ** 0.5) / 2.0
RESPHI = 2 - PHI

def gold(f: Callable[[float], float], a: float, b: float, e: float = E, verbose: bool = False) -> float:
    iteration = 0
    while abs(b - a) > e:
        iteration += 1
        if verbose:
            print(f"Шаг № {iteration}")
        x1 = a + RESPHI * (b - a)
        x2 = b - RESPHI * (b - a)
        if f(x1) < f(x2):
            b = x2
        else:
            a = x1
    if verbose:
        print(f"Всего шагов: {iteration}")
    return (a + b) / 2.0


def solve(f):
    prev_point = numpy.array([0, 0])
    cur_point = numpy.array([10, 10])
    df_dx = sympy.lambdify([x, y], sympy.diff(f, x))
    df_dy = sympy.lambdify([x, y], sympy.diff(f, y))
    f = sympy.lambdify([x, y], f)
    grad = lambda point: numpy.array([df_dx(*point), df_dy(*point)])
    cur_grad = grad(cur_point)
    scalar = None
    d_point = cur_point - prev_point
    iteration = 0
    while abs(d_point[0]) > E or abs(d_point[1]) > E:
        print(f"Итерация № {iteration}: x={cur_point[0]:.3f} y={cur_point[1]:.3f} f={f(cur_point[0], cur_point[1]):.3f} dx={d_point[0]:.3f} dy={d_point[1]:.3f}", end="")
        if scalar is None:
            print()
        else:
            print(f" scalar={scalar:.3f}")
        t = gold(lambda r: f(*(cur_point - r * cur_grad)), 0, 10)
        prev_point = cur_point
        cur_point = prev_point - t * cur_grad
        prev_grad = cur_grad
        cur_grad = numpy.array([df_dx(*cur_point), df_dy(*cur_point)])
        cur_grad = grad(cur_point)
        scalar = numpy.dot(prev_grad, cur_grad)
        iteration += 1
        d_point = cur_point - prev_point

    print(f"Итерация № {iteration}: x={cur_point[0]:.3f} y={cur_point[1]:.3f} f={f(cur_point[0], cur_point[1]):.3f}  dx={d_point[0]:.3f} dy={d_point[1]:.3f} scalar={scalar:.3f}")
    return cur_point

if __name__ == "__main__":
    f0 = x ** 2 - 6 * x + y ** 2 - 8 * y
    f1 = x ** 2 + 8 * x + y ** 2 - 6 * y
    f2 = 2 * x ** 2 + 8 * x + y ** 2 - 6 * y
    f3 = (x ** 2 - y) ** 2 + (y - 2) ** 2
    print(solve(f0))  # 3 4
    print(solve(f1))  # -4 3
    print()
    print(solve(f2))  # -2 3
    print()
    print(solve(f3))  # 2 ** 0.5, 2