'''
from collections import Counter
s="водичка"
plus=0
minus = 0
for i1 in s:
    for i2 in s.replace(i1, ''):
        for i3 in s.replace(i1, '').replace(i2, ''):
            for i4 in s.replace(i1, '').replace(i2, '').replace(i3, ''):
                for i5 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, ''):
                    for i6 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, ''):
                        for i7 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, ''):
                            #for i8 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, ''):
                                for i9 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, '').replace(i8, ''):
                                    for i10 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, '').replace(i8, '').replace(i9, ''):
                                        for i11 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, '').replace(i8, '').replace(i9, '').replace(i10, ''):
                                            for i12 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, '').replace(i8, '').replace(i9, '').replace(i10, '').replace(i11, ''):
                                          
                        s1=i1+i2+i3+i4+i5+i6#+i7#+i8+i9+i10+i11+i12
                                        #signature=list(Counter(s1).values())
                                            #if len(signature) == len(s1) - 1 and
                        if i1 not in s[:2] and i2 not in s[:2] and "ва" in s1:
                            plus+=1
                        else:
                            minus +=1
                            '''
#print (plus, minus)
from itertools import permutations
ans = 0
wrd = "водичка"
first = 2
last = -2
lst = list(map(''.join, list(permutations(wrd))))
print (wrd[-last:])
print(wrd[:abs(first)])
print(wrd.find("д"))
for i in lst:
    if (last < 0 and wrd[last:] in i) or (last > 0 and wrd[-last:] not in i):
        continue
    good = True
    for j in wrd[:abs(first)]:
        if (first > 0 and i.find(j) >= first) or (first < 0 and i.find(j) < -first):
            good = False
            break
    if good:
        print(i)
        ans+=1
print(ans)
