#with open('27.txt') as F:
f = open("1.txt", "w")
from random import randint
n = 10
k = randint(6, 10)
f.write(f"{n} {k}\n")
for i in range(n):
  f.write(f"{randint(1, 10000)}\n")
f.close()

f = open("2.txt", "w")
from random import randint
n = 60000
k = randint(6, 10)
f.write(f"{n} {k}\n")
for i in range(n):
  f.write(f"{randint(1, 10000)}\n")
f.close()

for iii in (1,2):
  with open(str(iii)+'.txt') as F:
    N, K = map( int, F.readline().split() )
    data = [ int(F.readline()) for i in range(N) ]
  
  count = 0
  tailCount = [1] + [0]*(K-1)
  totalSum = 0
  
  for x in range(len(data)):
    totalSum += data[x]
    r = totalSum % K
    count += tailCount[r]
    tailCount[r] += 1
  count = x*(x+1)//2 - count
  print( count )
  if count == N*(N+1)//2 or count == 0:
    print("generate again")