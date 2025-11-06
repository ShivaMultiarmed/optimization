backpack_max = 30
backpack_max = 1000000

backpack_data = [
    [3, 5, 9],  
    [8, 14, 26]  
]

def find_max(backpack_max, weights, values):
    f = [0] * (backpack_max + 1)
    count = [[0] * len(weights) for _ in range(backpack_max + 1)]  
    for w in range(backpack_max + 1):
        for i in range(len(weights)):
            weight = weights[i]
            value = values[i]
            if w - weight >= 0:
                oldF = f[w]
                f[w] = max(f[w], f[w - weight] + value)
                if f[w] != oldF:
                    count[w] = count[w - weight][:]
                    count[w][i] += 1
            #print(f'{count[w][i]} ', end = '')
        #print()
    #	for element in f:
    #    print(f'{element} ', end = '')
    return f[backpack_max], count[backpack_max]

if __name__ == "__main__":
    weights = backpack_data[0]
    values = backpack_data[1]
    max_value, item_count = find_max(backpack_max, weights, values)
    print(f"Максимальная стоимость, которую можно получить: {max_value}")
    print("Состав рюкзака:")
    for i in range(len(weights)):
        print(f"Вес {weights[i]}: {item_count[i]}")
