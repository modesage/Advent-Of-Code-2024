import sys
import re
from collections import deque

sys.setrecursionlimit(10**6)
DIRECTIONS = [(-1, 0), (0, 1), (1, 0), (0, -1)]

def parse_ints(s):
    return [int(x) for x in re.findall('-?\\d+', s)]

result = 0
data = open("input.txt").read().strip()

grid = data.split('\n')
rows = len(grid)
cols = len(grid[0])
grid = [[grid[r][c] for c in range(cols)] for r in range(rows)]

for r in range(rows):
    for c in range(cols):
        if grid[r][c] == 'S':
            start_row, start_col = r, c
        if grid[r][c] == 'E':
            end_row, end_col = r, c

distances = {}
queue = deque([(0, end_row, end_col)])
while queue:
    dist, r, c = queue.popleft()
    if (r, c) in distances:
        continue
    distances[(r, c)] = dist
    for dr, dc in DIRECTIONS:
        nr, nc = r + dr, c + dc
        if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] != '#':
            queue.append((dist + 1, nr, nc))

def count_cheats(dist0, max_cheat_time):
    cheats = set()
    queue = deque([(0, None, None, None, start_row, start_col)])
    visited = set()
    buffer_time = 100
    while queue:
        dist, cheat_start, cheat_end, cheat_time, r, c = queue.popleft()
        assert cheat_end is None
        if dist >= dist0 - buffer_time:
            continue
        if grid[r][c] == 'E':
            if cheat_end is None:
                cheat_end = (r, c)
            if dist <= dist0 - buffer_time and (cheat_start, cheat_end) not in cheats:
                cheats.add((cheat_start, cheat_end))
        if (r, c, cheat_start, cheat_end, cheat_time) in visited:
            continue
        visited.add((r, c, cheat_start, cheat_end, cheat_time))

        if cheat_start is None:  # start cheat
            assert grid[r][c] != '#'
            queue.append((dist, (r, c), None, max_cheat_time, r, c))
        if cheat_time is not None and grid[r][c] != '#':  # end cheat
            assert grid[r][c] in ['.', 'S', 'E']
            if distances[(r, c)] <= dist0 - 100 - dist:
                cheats.add((cheat_start, (r, c)))
        if cheat_time == 0:
            continue
        else:
            for dr, dc in DIRECTIONS:
                nr, nc = r + dr, c + dc
                if cheat_time is not None:
                    assert cheat_time > 0
                    if 0 <= nr < rows and 0 <= nc < cols:
                        queue.append((dist + 1, cheat_start, None, cheat_time - 1, nr, nc))
                else:
                    if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] != '#':
                        queue.append((dist + 1, cheat_start, cheat_end, cheat_time, nr, nc))

    return len(cheats)

start_dist = distances[(start_row, start_col)]
print(count_cheats(start_dist, 2))
print(count_cheats(start_dist, 20))
