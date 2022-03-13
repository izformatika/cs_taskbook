#coding:utf-8
gen = True
example = True
two = True
from random import randint, shuffle

if gen:
  f = open("1.txt", "w")
  n = 50
  f.write(f"{n}\n")
  for i in range(n):
    f.write(f"{randint(1, 10000)}\n")
  f.close()

  if two:
    f = open("2.txt", "w")
    n = 60000
    f.write(f"{n}\n")
    for i in range(n):
      f.write(f"{randint(1, 10000)}\n")
    f.close()
if not example:
  numbers = [2,3,5,7,11,13,17,19,23,29,31,37]
  shuffle(numbers)
  five = numbers.pop()
  seven = numbers.pop()
else:
  numbers = [2,3,5,7,11,13,17,19,23,29,31,37]
  shuffle(numbers)
  five = numbers.pop()
  seven = numbers.pop()
  numbers[1]=five
  numbers[2]*=five
  numbers[5]*=five
  numbers[4]*=seven
  numbers[7]*=seven
  numbers[8]=five
  print()
  print(10, *numbers, sep = '\n')
  subseq = [[], [], []]
  for i in range(len(numbers)):
    for j in range(i+1, len(numbers)+1):
      fv = 0
      sv = 0
      for k in range(i, j):
        if numbers[k] % five == 0:
          fv+=1
        if numbers[k]%seven==0:
          sv+=1
      if fv == sv:
        subseq[fv].append(numbers[i:j])
  subseqs = 0
  for i in subseq:
    subseqs+=len(i)
  
  print(f"В этом наборе следующие подпоследовательности с одинаковым количеством чисел, кратных {five} и {seven}:\n- без чисел, кратных {five} или {seven}: ", end='')
  print(f'{", ".join(map(str, subseq[0]))}')
  print(f"- по одному числу: ", end='')
  print(f'{", ".join(map(str, subseq[1]))}')
  print(f"- по два числа: ", end='')
  print(f'{", ".join(map(str, subseq[2]))}')
  print(f"Количество этих подпоследовательностей {subseqs}. Ответ: {subseqs}.")
  
  print()

for iii in (1,2):

  with open(str(iii)+".txt") as F:
    N = int(F.readline())
    data = [ int(F.readline()) for i in range(N) ]
  
  count = 0
  tailDiffCount = { 0: 1 }
  count5 = count7 = 0
  for i in range(N):
    if data[i] % five == 0: count5 += 1
    if data[i] % seven == 0: count7 += 1
    if count5-count7 not in tailDiffCount:
      tailDiffCount[count5-count7] = 0
    count += tailDiffCount[count5-count7]
    tailDiffCount[count5-count7] += 1
    # print( data[i], count, tailDiffCount )
  
  print( count, count5, count7 )
  if count == N*(N+1)//2 or count < 5 or count5 < 4 or count7 < 4:
    print("generate again")  
  if not two:
    break
  