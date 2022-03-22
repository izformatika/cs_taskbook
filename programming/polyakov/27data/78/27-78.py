#coding:utf-8

gen = True
example = False
two = True

from random import randint, shuffle
stop = False
while not stop:
  one_sol_ok = False
  two_sol_ok = False  
  if gen: 
    f = open("1.txt", "w")
    from random import randint
    n = 50
    f.write(f"{n}\n")
    for i in range(n):
      f.write(f"{randint(1, 100)}\n")
    f.close()
    if two:
      f = open("2.txt", "w")
    
      n = 60000
      f.write(f"{n}\n")
      for i in range(n):
        f.write(f"{randint(1, 100)}\n")
      f.close()  
      
  K,M = 0,0
  if gen:
    while True:
      K = randint(10, 98)
      if K % 10 == 0:
        continue
      if K%10!=K//10:
        break
    M = K//10 + K%10*10
  else:
    K = 3
    M = 4
  
  for iii in (1,2):
    get_it = [0,1,2]
    with open(str(iii)+".txt") as F:
      N = int( F.readline() )
      
      tailSum = [ [0] + [None]*(K-1) ]
      for i in range(M-1):
        tailSum.append( [None]*K )
      
      tailLen = [[0]*K for i in range(M)]
      
      maxSum, minLen = 0, 0

      totalSum = 0
      r = 0
      total_subseq = 0
      best_subseq = 0
      nums = []
      
      for i in range(1,N+1):
        x = int( F.readline() )
        nums.append(x)
        totalSum += x
        ri = x % M
      
        if tailSum[ri][r] == None:
          tailSum[ri][r] = totalSum
          tailLen[ri][r] = i
      
        r0 = (M - ri) % M
        r = totalSum % K
        if tailSum[r0][r] != None:
          total_subseq += 1
          curSum = totalSum - tailSum[r0][r]
          curLen = i - tailLen[r0][r] + 1
          if curSum > maxSum or \
             (curSum == maxSum and curLen < minLen):
            if curSum > maxSum:
              best_subseq = 0
            best_subseq += 1
            maxSum = curSum
            minLen = curLen
            get_it[iii] = [nums[tailLen[r0][r]-1:i]]
      
      F.close()
      print( K,M,minLen )
      print(total_subseq)
      if iii == 1 and gen and not (minLen < 5 or total_subseq < 4):
        one_sol_ok = True
      if iii == 2 and gen and not (minLen < 5 or total_subseq < 4):
        two_sol_ok = True
      if not two:
        break
  print(one_sol_ok, two_sol_ok)
  print()
  stop = True
  
  if gen and not (one_sol_ok and two_sol_ok):
    stop = False
  else:
    print(*get_it, sep = '\n\n')
  