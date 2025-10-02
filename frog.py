import numpy

stones = numpy.array([0, 1, 2, 3, 5, 7, 10, 11, 14, 20, 22, 25])
jump_lengths = numpy.arange(int(numpy.sqrt(stones[-1]) + 2))
jump_counts = numpy.zeros((len(jump_lengths), stones[-1] + 1))
jump_counts.fill(numpy.inf)
jump_counts[0][0] = 0

def jump(position, length):
    comp = numpy.array([numpy.inf, numpy.inf, numpy.inf])
    if position - length < 0:
        return numpy.inf
    pos = position - length
    comp[0] = jump_counts[length - 1][pos]
    comp[1] = jump_counts[length][position - length]
    if length < jump_lengths[-1]:
        comp[2] = jump_counts[length + 1][pos]
    return numpy.min(comp) + 1

def backwards(array):
    out = numpy.array([])
    array = numpy.rot90(array)[::-1]
    position = stones[-1]
    jump_len = numpy.argmin(array[position])
    if array[position][jump_len] == numpy.inf:
        return [-1]
    while position != 0:
        out = numpy.append(out, position)
        position -= jump_len
        comp = numpy.array([numpy.inf, numpy.inf, numpy.inf])
        if jump_len > 0:
            comp[0] = array[position][jump_len - 1]
        comp[1] = array[position][jump_len]
        if jump_len < jump_lengths[-1]:
            comp[2] = array[position][jump_len + 1]
        jump_len += numpy.argmin(comp) - 1
    out = numpy.append(out, 0)

    return out[::-1].astype(int)


if __name__ == "__main__":
    for x in stones[1:]:
        for y in jump_lengths[1:]:
            jump_counts[y][x] = jump(x, y)

    print(" ", end="")
    for val in stones:
        print(f" {val:2}", end="")
    print()
    for x in jump_lengths:
        print(f"{x}", end="")
        for y in stones:
            if jump_counts[x][y] == numpy.inf:
                print("  -", end="")
            else:
                print(f" {jump_counts[x][y]:2.0f}", end="")
        print()

    print(backwards(jump_counts))
