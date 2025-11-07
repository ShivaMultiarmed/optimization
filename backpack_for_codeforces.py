def find_max(capacity, weights):
    values = [0] * (capacity + 1)
    contents = [[0] * len(weights) for _ in range(capacity + 1)]  
    for c in range(capacity + 1):
        for i in range(len(weights)):
            if c - weights[i] >= 0:
                if values[c] < values[c - weights[i]] + weights[i]:
                    values[c] = values[c - weights[i]] + weights[i]
                    contents[c] = contents[c - weights[i]][:]
                    contents[c][i] += 1
    return values[capacity]

if __name__ == "__main__":
    capacity, count = list(map(lambda x: int(x), input().split(" ")))
    weights = list(map(lambda x: int(x), input().split(" ")))
    max_value = find_max(capacity, weights)
    print(max_value)