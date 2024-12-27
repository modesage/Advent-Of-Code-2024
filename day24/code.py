import sys
sys.setrecursionlimit(10**6)
infile = "input.txt"
with open(infile) as f:
    s = f.read().strip()

ans = res = 0

g = {}
inits, gates = s.split("\n\n")  
for line in inits.split("\n"):
    a,b = line.split(": ")
    b = int(b)
    g[a] = b

gd = {}

for l in gates.strip().split("\n"):
    l = l.split(" ")
    a = l[0]
    op = l[1]
    b = l[2]
    out = l[-1]
    gd[out] = (a,b,op)

def dfs(reg):
    if reg not in g:
        a,b,op = gd[reg]
        left = dfs(a)
        right = dfs(b)
        if op == "OR":
            res = left | right
        elif op == "AND":
            res = left & right
        else:
            res = left ^ right
        g[reg] = res
    return g[reg]

zouts = {}
for reg in gd.keys():
    if reg.startswith("z"): 
        zouts[reg] = dfs(reg)

keys = sorted(list(zouts.keys()))[::-1]
ans = 0
for k in keys:
    ans <<= 1
    ans |= zouts[k]

print(ans)