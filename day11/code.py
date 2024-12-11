# Read and process input data
stones = [int(x) for x in open('input.txt').read().strip().split()]

# Cache for memoization
memo = {}

def calc_length(stone, steps):
    """Calculates the length of the resulting list after [steps] transformations on [stone]."""
    if (stone, steps) in memo:
        return memo[(stone, steps)]
    
    if steps == 0:
        result = 1
    elif stone == 0:
        result = calc_length(1, steps - 1)
    elif len(str(stone)) % 2 == 0:
        s = str(stone)
        mid = len(s) // 2
        left, right = int(s[:mid]), int(s[mid:])
        result = calc_length(left, steps - 1) + calc_length(right, steps - 1)
    else:
        result = calc_length(stone * 2024, steps - 1)
    
    memo[(stone, steps)] = result
    return result

def total_length(steps):
    return sum(calc_length(stone, steps) for stone in stones)

# Output the results
print(total_length(25))
print(total_length(75))
