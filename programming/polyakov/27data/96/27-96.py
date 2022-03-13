#coding:utf-8
gen = False
example = False
two = False
from random import randint, shuffle

if gen:
  f = open("1.txt", "w")
  from random import randint
  n = 50
  f.write(f"{n}\n")
  for i in range(n):
    f.write(f"{randint(1, 10000)}\n")
  f.close()
  
  if two:
    f = open("2.txt", "w")
    from random import randint, shuffle
    n = 60000
    f.write(f"{n}\n")
    for i in range(n):
      f.write(f"{randint(1, 10000)}\n")
    f.close()
    
if not example:
  numbers = [2,3,5,7,11,13,17,19,23,29,31,37]
  shuffle(numbers)
  five = 7#numbers.pop()
  seven = 2#numbers.pop()
else:
  numbers = [2,3,5,7,11,13,17,19,23,29,31,37]
  shuffle(numbers)
  five = numbers.pop()
  seven = numbers.pop()
  numbers1 = numbers[::1]
  numbers1[1]=five
  numbers1[2]*=five
  numbers1[5]*=five
  numbers1[4]*=seven
  numbers1[7]*=seven
  numbers1[8]=five
  print()
  print(five, seven)
  print(10, *numbers1, sep = '\n')
  print(f'В этом наборе максимальную сумму элементов {sum(numbers1[2:8])} имеет подпоследовательность ({", ".join(map(str, numbers1[2:8]))}), содержащая два числа делящихся на {five} ({numbers1[2]} и {numbers1[5]}) и два числа, делящихся на {seven} ({numbers1[4]} и {numbers1[7]}).')


for iii in (1,2):

  with open(str(iii)+'.txt') as F:
    N = int(F.readline())
    data = [ int(F.readline()) for i in range(N) ]
  
  
  tailMinSum = { 0: 0 }
  totalSum = count5 = count7 = 0
  maxSum = None
  for i in range(N):
    totalSum += data[i]
    if data[i] % five == 0: count5 += 1
    if data[i] % seven == 0: count7 += 1
    if count5-count7 not in tailMinSum:
      tailMinSum[count5-count7] = totalSum
    else:
      minTail = tailMinSum[count5-count7]
      if maxSum == None or totalSum - minTail > maxSum:
        maxSum = totalSum - minTail
      if totalSum < tailMinSum[count5-count7]:
        tailMinSum[count5-count7] = totalSum
  
  print( maxSum , totalSum, count5, count7)
  if (maxSum < totalSum*0.3 and N < 1000) or maxSum > totalSum*0.67 or count5 < 4 or count7 < 4:
    print("generate again")  
  if not two:
    break