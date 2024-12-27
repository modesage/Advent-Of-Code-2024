import sys
import re

sys.setrecursionlimit(10**6)

def parse_integers(s):
    return [int(x) for x in re.findall('-?\\d+', s)]

def parse_shape(shape_str):
    return [list(line) for line in shape_str.split('\n')]

def is_key(grid):
    return all(cell == '.' for cell in grid[0])

def fits(key_grid, lock_grid):
    rows = len(key_grid)
    cols = len(key_grid[0])

    if rows != len(lock_grid) or cols != len(lock_grid[0]):
        return False

    for r in range(rows):
        for c in range(cols):
            if key_grid[r][c] == '#' and lock_grid[r][c] == '#':
                return False
    return True

def count_valid_pairs(keys, locks):
    valid_pairs = 0
    for key in keys:
        for lock in locks:
            if fits(key, lock):
                valid_pairs += 1
    return valid_pairs

def main():
    with open("input.txt") as f:
        data = f.read().strip()

    shape_strings = data.split('\n\n')

    keys = []
    locks = []

    for shape_str in shape_strings:
        grid = parse_shape(shape_str)

        if is_key(grid):
            keys.append(grid)
        else:
            locks.append(grid)

    valid_pairs = count_valid_pairs(keys, locks)
    
    print(valid_pairs)

if __name__ == "__main__":
    main()
