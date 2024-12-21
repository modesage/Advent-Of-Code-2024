import sys
import re
import heapq
from collections import deque
from copy import deepcopy

sys.setrecursionlimit(10**6)
DIRECTIONS = [(-1, 0), (0, 1), (1, 0), (0, -1)]

def parse_ints(s):
    return [int(x) for x in re.findall('-?\\d+', s)]

result1 = 0
input_data = open("input.txt").read().strip()

pad1 = ['789', '456', '123', ' 0A']
pad2 = [' ^A', '<v>']

def get_pad1(position):
    r, c = position
    if not (0 <= r < len(pad1) and 0 <= c < len(pad1[r])):
        return None
    if pad1[r][c] == ' ':
        return None
    return pad1[r][c]

def get_pad2(position):
    r, c = position
    if not (0 <= r < len(pad2) and 0 <= c < len(pad2[r])):
        return None
    if pad2[r][c] == ' ':
        return None
    return pad2[r][c]

def move_pad1(position, move):
    if move == 'A':
        return (position, get_pad1(position))
    elif move == '<':
        return ((position[0], position[1] - 1), None)
    elif move == '^':
        return ((position[0] - 1, position[1]), None)
    elif move == '>':
        return ((position[0], position[1] + 1), None)
    elif move == 'v':
        return ((position[0] + 1, position[1]), None)

def move_pad2(position, move):
    if move == 'A':
        return (position, get_pad2(position))
    elif move == '<':
        return ((position[0], position[1] - 1), None)
    elif move == '^':
        return ((position[0] - 1, position[1]), None)
    elif move == '>':
        return ((position[0], position[1] + 1), None)
    elif move == 'v':
        return ((position[0] + 1, position[1]), None)

def solve_part1(code, pads):
    start = [0, (3, 2), 'A', '', '']
    queue = []
    heapq.heappush(queue, start)
    visited = {}
    while queue:
        dist, p1, p2, output, path = heapq.heappop(queue)
        assert p2 in ['<', '>', 'v', '^', 'A']
        if output == code:
            return dist
        if not code.startswith(output):
            continue
        if get_pad1(p1) is None:
            continue
        key = (p1, p2, output)
        if key in visited:
            assert dist >= visited[key], f'{key=} {dist=} {visited[key]=}'
            continue
        visited[key] = dist
        for move in ['^', '<', 'v', '>', 'A']:
            new_p1 = p1
            new_output = output
            new_p1, output_val = move_pad1(p1, move)
            if output_val is not None:
                new_output = output + output_val
            move_cost = calculate_cost2(move, p2, pads)
            new_path = path
            assert move_cost >= 0
            heapq.heappush(queue, [dist + move_cost, new_p1, move, new_output, new_path])

def calculate_cost2_slow(char, prev_move, pads):
    start_pos = {'^': (0, 1), '<': (1, 0), 'v': (1, 1), '>': (1, 2), 'A': (0, 2)}[prev_move]
    start = [0, start_pos, '']
    for _ in range(pads - 1):
        start.append((0, 2))
    queue = deque([start])
    visited = set()
    while queue:
        dist, p1, path, *positions = queue.popleft()
        key = (p1, tuple(positions))
        if key in visited:
            continue
        if get_pad2(p1) is None:
            continue
        ok = True
        for pos in positions:
            if get_pad2(pos) is None:
                ok = False
                break
        if not ok:
            continue
        visited.add(key)
        for move in ['^', '<', 'v', '>', 'A']:
            new_p1 = p1
            new_positions = deepcopy(positions)
            new_move = move
            for i, pos in reversed(list(enumerate(positions))):
                new_positions[i], new_move = move_pad2(positions[i], new_move)
                if new_move is None:
                    break
                else:
                    for j in range(len(positions)):
                        if j > i:
                            assert new_positions[j] == (0, 2)
            if new_move is not None:
                new_p1, output = move_pad2(p1, new_move)
                if output == char:
                    return path + move
            queue.append([dist + 1, new_p1, path + move] + new_positions)
    assert False, f'{char=} {prev_move=} {pads=}'

cache = {}
def calculate_cost2(char, prev_move, pads):
    key = (char, prev_move, pads)
    if key in cache:
        return cache[key]
    if pads == 0:
        return 1
    else:
        assert char in ['^', '>', 'v', '<', 'A']
        assert prev_move in ['^', '>', 'v', '<', 'A']
        assert pads >= 1
        queue = []
        start_pos = {'^': (0, 1), '<': (1, 0), 'v': (1, 1), '>': (1, 2), 'A': (0, 2)}[prev_move]
        heapq.heappush(queue, [0, start_pos, 'A', '', ''])
        visited = {}
        while queue:
            dist, p, prev, output, path = heapq.heappop(queue)
            if get_pad2(p) is None:
                continue
            if output == char:
                cache[key] = dist
                return dist
            elif len(output) > 0:
                continue
            seen_key = (p, prev)
            if seen_key in visited:
                assert dist >= visited[seen_key]
                continue
            visited[seen_key] = dist
            for move in ['^', '<', 'v', '>', 'A']:
                new_p, output_val = move_pad2(p, move)
                move_cost = calculate_cost2(move, prev, pads - 1)
                new_dist = dist + move_cost
                new_path = path
                new_output = output
                if output_val is not None:
                    new_output = new_output + output_val
                heapq.heappush(queue, [new_dist, new_p, move, new_output, new_path])
        assert False, f'{char=} {pads=}'

def solve_part2(code):
    start = [0, (0, 2), '', '']
    queue = deque([start])
    visited = set()
    while queue:
        dist, p, output, path = queue.popleft()
        key = (p, output)
        if output == code:
            yield path
        if not code.startswith(output):
            continue
        if key in visited:
            continue
        visited.add(key)
        if get_pad2(p) is None:
            continue
        for move in ['^', '<', 'v', '>', 'A']:
            new_p = p
            new_output = output
            new_p, output_val = move_pad2(p, move)
            if output_val is not None:
                new_output = output + output_val
            heapq.heappush(queue, [dist + 1, new_p, new_output, path + move])

def solve(code):
    pads = int(sys.argv[2])
    return solve_part1(code, pads)

def slow_solve(code, total_pads):
    start = [0, (3, 2), '', '']
    for _ in range(total_pads):
        start.append((0, 2))
    queue = deque([start])
    visited = set()
    while queue:
        dist, p1, output, path, *positions = queue.popleft()
        key = (p1, output, tuple(positions))
        if output == code:
            return path
        if not code.startswith(output):
            continue
        if key in visited:
            continue
        if get_pad1(p1) is None:
            continue
        ok = True
        for pos in positions:
            if get_pad2(pos) is None:
                ok = False
                break
        if not ok:
            continue
        visited.add(key)
        if len(visited) % 10**5 == 0:
            print(len(visited), key)
        for move in ['^', '<', 'v', '>', 'A']:
            new_p1 = p1
            new_output = output
            new_positions = deepcopy(positions)
            new_move = move

            for i, pos in reversed(list(enumerate(positions))):
                new_positions[i], new_move = move_pad2(positions[i], new_move)
                if new_move is None:
                    break
                else:
                    for j in range(len(positions)):
                        if j > i:
                            assert new_positions[j] == (0, 2)
            if new_move is not None:
                new_p1, output_val = move_pad1(p1, new_move)
                if output_val is not None:
                    new_output = output + output_val
            queue.append([dist + 1, new_p1, new_output, path + move] + new_positions)

p1_total = 0
p2_total = 0

for line in input_data.split('\n'):
    s1 = solve_part1(line, 2)
    s2 = solve_part1(line, 25)
    line_int = parse_ints(line)[0]
    p1_total += line_int * s1
    p2_total += line_int * s2

print(p1_total)
print(p2_total)
