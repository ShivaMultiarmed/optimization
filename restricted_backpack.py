input_data = [
    [3, 5, 9],
    [8, 14, 26],
    [3, 2, 2]
]

def solve(data, capacity):
    weights = data[0]
    n = len(weights)
    values = data[1]
    max_numbers = data[2]
    totals = [0] * (capacity + 1)
    backpack = [[0] * n for _ in range(capacity + 1)]
    for i in range(n):
        for c in range(capacity, -1, -1):
            for k in range(1, max_numbers[i] + 1):
                if k * weights[i] <= c:
                    value = totals[c - k * weights[i]] + k * values[i]
                    if value > totals[c]:
                        totals[c] = value
                        backpack[c] = backpack[c - k * weights[i]].copy()
                        backpack[c][i] = k
                else:
                    break

    return totals[capacity], backpack[capacity]

if __name__ == '__main__':
    total, item_indices = solve(input_data, 1000)
    print(f"Элементы: {item_indices}")
    output_values = [a * b for a, b in zip(item_indices, input_data[1])]
    print(f"Стоимости: {output_values}: {sum(output_values)}")
    output_weights = [a * b for a, b in zip(item_indices, input_data[0])]
    print(f"Веса: {output_weights}: {sum(output_weights)}")
