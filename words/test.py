def f1():
    from collections import Counter
    s="аукционер"
    plus=0
    minus = 0
    print(s[:2])
    for i1 in s:
        print(i1)
        for i2 in s.replace(i1, ''):
            for i3 in s.replace(i1, '').replace(i2, ''):
                for i4 in s.replace(i1, '').replace(i2, '').replace(i3, ''):
                    for i5 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, ''):
                        for i6 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, ''):
                            for i7 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, ''):
                                for i8 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, ''):
                                    for i9 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, '').replace(i8, ''):
                                        s1=i1+i2+i3+i4+i5+i6+i7+i8+i9#+i10+i11+i12+i13+i14
                                            #signature=list(Counter(s1).values())
                                                #if len(signature) == len(s1) - 1 and
                                        if s[0] not in s1[:2] and s[1] not in s1[:2] and "нер" in s1:
                                            #print(s1)
                                            plus+=1
                                        else:
                                            minus +=1

    print (plus, minus)
    
def f2():
    from itertools import permutations
    ans = 0
    wrd = "водичка"
    lst = list(map(''.join, list(permutations(wrd))))
    #print(len(lst))
    #print(wrd[-3:])
    first = 3
    last = 2
    for i in lst:
        good = True
        for j in range(first):
            if wrd[j] in i[:first]:
                good = False
                break
        if not good:
            continue
        if wrd[-last:] in i:
            #print(i)
            ans += 1
    print(ans)
    
def f3():
    from math import factorial
    first = 3
    last = 2
    length = 7
    mid = length - first - last
    pre = []#i am well aware this can be done simpler, but im too stupid for it
    after = [i for i in range(mid, 0, -1)][:first-last]+[i for i in range(mid + first - 1, 0, -1)]
    ans = 0
    cur = 1
    while len(pre) <= first:
        print(*pre, '\t', *after)
        cur = 1
        for i in pre:
            cur *= i
        for i in after:
            cur *= i
        
        ans += cur
        if len(pre)==0:
            pre.append(mid)
        else:
            pre.append(pre[-1] - 1)
        after.pop(0)
                        
    ans += cur * mid
    print(ans)
f2()
f3()
