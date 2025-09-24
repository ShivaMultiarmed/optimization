import sys
from typing import Callable, Tuple

phi = (1 + 5 ** 0.5) / 2
resphi = 2 - phi

def goldenSection(f: Callable[[float], float], l: float, r: float, e: float, verbose: bool = False, arg: str = 'X') -> Tuple[float, float]:
    a = l
    b = r
    x1 = a + resphi * (b - a)
    x2 = b - resphi * (b - a)
    f1 = f(x1)
    f2 = f(x2)
    count = 0
    while abs(b - a) > e:
        if verbose:
            print(f"номер итерации {arg}: {count}")
            print(f"{arg} = [{x1}; {x2}]")
        if f1 < f2:
            b = x2
            x2 = x1
            f2 = f1
            x1 = a + resphi * (b - a)
            f1 = f(x1)
        else:
            a = x1
            x1 = x2
            f1 = f2
            x2 = b - resphi * (b - a)
            f2 = f(x2)
        count += 1
    print(f"количество итераций {arg}: {count}")
    print(f"{arg} = [{x1}; {x2}]")
    min = (a + b) / 2.0
    return min, count

def goldenSectionXY(f: Callable[[float, float],float], l: float, r: float, e: float) -> Tuple[float, float, float]:
    a = l
    b = r
    count_x = 0
    sum_y = 0
    while abs(b - a) > e:
        x1 = a + resphi * (b - a)
        x2 = b - resphi * (b - a)
        print(f"номер итерации X: {count_x}")
        print(f"X = [{x1}; {x2}]")
        y1_opt, cy1 = goldenSection(lambda y: f(x1, y), l, r, e, False, 'Y')
        y2_opt, cy2 = goldenSection(lambda y: f(x2, y), l, r, e, False,'Y')
        sum_y += cy1 + cy2
        if f(x1, y1_opt) <= f(x2, y2_opt):
            b = x2
        else:
            a = x1
        count_x += 1
    x = (a + b) / 2.0
    y, cy_final = goldenSection(lambda y: f(x, y), l, r, e, False, 'Y')
    sum_y += cy_final
    return x, y, count_x + sum_y

e_values = [10**(-6), 10**(-8), 10**(-10)]
for e in e_values:
    print(f"Для e = {e}")
    if len(sys.argv) < 2 or sys.argv[1] == "1":
        f = lambda x: x ** 2 - 6 * x
        x_min, total_count = goldenSection(f, -10, 10, e, True)
        print(f"x_min = {x_min}")
        print(f"f_min = {f(x_min)}")
        print(f"total_count = {total_count}")
    else:
        f = lambda x, y: x ** 2 - 6 * x + y ** 2 - 8 * y
        x_min, y_min, total_count = goldenSectionXY(f, -10, 10, e)
        print(f"x_min = {x_min}")
        print(f"y_min = {y_min}")
        print(f"f_min = {f(x_min, y_min)}")
        print(f"total_count = {total_count}")