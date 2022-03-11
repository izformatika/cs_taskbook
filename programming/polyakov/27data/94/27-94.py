#coding:utf-8
f = open("1.txt", "w")
from random import randint
n = 20
f.write(f"{n}\n")
for i in range(n):
  f.write(f"{randint(1, 10000)}\n")
f.close()

f = open("2.txt", "w")
from random import randint, shuffle
n = 60000
f.write(f"{n}\n")
for i in range(n):
  f.write(f"{randint(1, 10000)}\n")
f.close()

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
print(five, seven)
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
mlen = 0
for i in subseq:
  for j in i:
    mlen = max(mlen, len(j))

print(f"В этом наборе следующие подпоследовательности с одинаковым количеством чисел, кратных {five} и {seven}:\n- без чисел, кратных {five} или {seven}: ", end='')
print(f'{", ".join(map(str, subseq[0]))}')
print(f"- по одному числу: ", end='')
print(f'{", ".join(map(str, subseq[1]))}')
print(f"- по два числа: ", end='')
print(f'{", ".join(map(str, subseq[2]))}')
print(f"Самая длинная последовательность из перечисленных имеет длину {mlen}. Ответ: {mlen}.")

print()

for iii in (1,2):

  with open(str(iii)+".txt") as F:
    N = int(F.readline())
    data = [ int(F.readline()) for i in range(N) ]
  
  tailLenByDiff = { 0: -1 }
  
  maxLen = 0
  count5 = count7 = 0
  for i in range(N):
    if data[i] % 5 == 0: count5 += 1
    if data[i] % 7 == 0: count7 += 1
    if count5-count7 not in tailLenByDiff:
      tailLenByDiff[count5-count7] = i
    maxLen = max( maxLen, i - tailLenByDiff[count5-count7] )
  
  print( maxLen )
  if maxLen > N - 5 or maxLen == 0:
    print("generate again")
