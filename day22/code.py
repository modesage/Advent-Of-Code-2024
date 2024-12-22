import sys
import re

sys.setrecursionlimit(10**6)
DIRECTIONS = [(-1, 0), (0, 1), (1, 0), (0, -1)]

def parse_integers(s):
    return [int(x) for x in re.findall('-?\\d+', s)]

data = open("input.txt").read().strip()

def xor(a, b):
    return a ^ b

def limit(x):
    return x % 16777216

def generate_prices(secret):
    prices = [secret]
    for _ in range(2000):
        secret = limit(xor(secret, 64 * secret))
        secret = limit(xor(secret, secret // 32))
        secret = limit(xor(secret, secret * 2048))
        prices.append(secret)
    return prices

def compute_changes(prices):
    return [prices[i+1] - prices[i] for i in range(len(prices) - 1)]

def calculate_scores(prices, changes):
    scores = {}
    for i in range(len(changes) - 3):
        pattern = (changes[i], changes[i+1], changes[i+2], changes[i+3])
        if pattern not in scores:
            scores[pattern] = prices[i+4]
    return scores

total_sum = 0
score_map = {}
for line in data.split('\n'):
    prices = generate_prices(int(line))
    total_sum += prices[-1]
    prices = [p % 10 for p in prices]
    changes = compute_changes(prices)
    scores = calculate_scores(prices, changes)
    for pattern, score in scores.items():
        if pattern not in score_map:
            score_map[pattern] = score
        else:
            score_map[pattern] += score

print(total_sum)
print(max(score_map.values()))
