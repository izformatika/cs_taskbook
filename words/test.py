# coding=cp1251
def f1():
    def good(s2):
        isgood = False
        ''' if s[2] not in vowels and s[3] in vowels and s[4] in vowels and s[5] not in vowels:
            isgood=True
        else:
            return False'''
        for i in range(len(s2)-3):
            if (i == 0 or s2[i-1] not in vowels) and s2[i] in vowels and s2[i+1] in vowels and s2[i+2] in vowels and s2[i+3] in vowels and (i == len(s2)-4 or s2[i+4] not in vowels):
                isgood = True
                break
        return isgood
    from collections import Counter
    vowels=["а","я","у","ю","э","е","о","ё","ы","и"]
    s="ауыежцфхкъ"
    plus=0
    minus = 0
    #print(s[:2])
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
                                        for i10 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, '').replace(i8, '').replace(i9, ''):
                                            s1=i1+i2+i3+i4+i5+i6+i7+i8+i9+i10#+i11+i12+i13+i14                   
                                            if good(s1):
                                                #print(s1)
                                                plus+=1
                                            else:
                                                #print(s1)
                                                minus+=1
                                    
    print (plus, minus)
'''
4 6 2 True	2574720
'''

    
    
def f2(first, last):
    from itertools import permutations
    ans = 0
    wrd = "власть"
    lst = list(map(''.join, list(permutations(wrd))))
    #print(len(lst))
    print(wrd[-last:])
    for i in lst:
        if wrd[-last:] not in i:
            continue
        good = True
        for j in range(first):
            if wrd[j] in i[:first]:
                good = False
                break
        if not good:
            continue
    
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

from os import walk
from math import factorial
def letters(n):
    if 5 <= n%100 <= 20:
        return "Р±СѓРєРІ"
    elif n % 10 == 1:
        return "Р±СѓРєРІР°"
    elif 2 <= n % 10 <= 4:
        return "Р±СѓРєРІС‹"
    else:
        return "Р±СѓРєРІ"

def f4(length, first, last, difficulty):
    mid = length - abs(first) - abs(last)
    if length <= 2 or abs(last) > length or abs(first) > length or abs(first)+abs(last)>=length:
        return
    if first < 0 and last>0 and mid+last < -first:
        #print("not enough letters to fill in starting slots")
        return

    ans = 0
    def two_lists(f,m,after):
        pre=[]
        ans = 0
        cur = 1
        while len(pre) <= f:
            #print(*pre, '\t', *after)
            cur = 1
            alarm = False
            for i in pre:
                cur *= i
            for i in after:
                cur *= i
            
            ans += cur
            if len(pre)==0:
                pre.append(m)
            else:
                if pre[-1]==1:#todo: not sure here
                    if len(pre)<f:
                        #print('alarm')
                        alarm=True
                    break
                pre.append(pre[-1] - 1)
            after.pop(0)
        #print(cur,m)
        return ans + (cur*m if not alarm else 0)#todo: and here
    if last > 0 and first < 0:
        ffirst = -first
        if last >= ffirst:
            ans=two_lists(ffirst,mid,[i for i in range(mid + ffirst, 0, -1)])#i think this can be done simpler, but im too stupid for it
        else: #last < first
            ans=two_lists(ffirst,mid,[i for i in range(mid, 0, -1)][:ffirst-last]+[i for i in range(mid-(ffirst-last) + ffirst, 0, -1)])
    elif last > 0 and first > 0:
        ans=factorial(first)*(mid+1)*factorial(mid)
    elif last < 0 and first < 0:# ----------------------------------------------------------------------------------------------------fuck!
        llast=-last
        ffirst=-first
        if llast >= ffirst:
            tmp=two_lists(ffirst,mid,[i for i in range(mid + ffirst, 0, -1)])
            #print(tmp)
            ans=factorial(llast+mid)//factorial(llast+mid-ffirst)*factorial(llast+mid) - tmp
        else: #last < first
            tmp=two_lists(ffirst,mid,[i for i in range(mid, 0, -1)][:ffirst-llast]+[i for i in range(mid-(ffirst-llast) + ffirst, 0, -1)])
            #print(tmp,'!')
            ans=factorial(llast+mid)//factorial(llast+mid-ffirst)*factorial(llast+mid) - tmp
    elif last < 0 and first > 0:
        #print(mid-last)
        ans = factorial(first)*factorial(mid-last) - factorial(first)*factorial(mid)*(mid+1)
    else:
        ans = -1
    return(ans)
def shortanswer(name, question, answer, file):
    print (question, answer)


#print(f4(8, -3, -2, 0),'=6192')
#print(f4(8, -2, -3, 0),'=21264')

'''print(f4(9, 3, 2, 0),'=720')
print(f4(9, 2, 3, 0),'=240')
print(f4(9, -3, 2, 0),'=10080')
print(f4(9, 2, -3, 0),'=9840')
print(f4(9, 3, -2, 0),'=3600')
print(f4(9, -2, 3, 0),'=2640')
print(f4(9, -3, -2, 0),'=76320')
print(f4(9, -2, -3, 0),'=209040')
'''
#print(f4(9, -3, 4, 0),'=180')
#print(f4(9, -3, -4, 0),'=WAT')
#print(f4(9, -3, -2, 0),'=76320')
#print(f4(9, 3, -2, 0),'=3600')
#print(f4(8, -3, 2, 0),'=1008')
#print(f4(8, -3, 4, 0),'=30')


#восьмёркаы 3024000 604800

from math import factorial

def seq(tgt, other, qtty, must,lvl=0):
    if other<0:
        return 0
    ans = 0
    length = tgt+other
    if must:
        if tgt >= qtty and other == 0:
            ans = factorial(tgt)
        elif tgt == qtty:
            ans = factorial(other+1)*factorial(tgt)
        else:
            tmp=factorial(tgt)//factorial(tgt-qtty)*(other)*factorial(length-qtty-1)
            print(tmp)
            ans+=tmp
            tmp=factorial(tgt)//factorial(tgt-qtty)*(other)*seq(tgt-qtty,other-1,qtty,False)
            print(tmp)
            ans+=tmp
            for j in range(length-qtty-2+1):#before otto
                after = length-qtty-j-2
                print(f'[{j}][{after}]')
                for k in range(max(0,tgt-qtty-after), min(tgt-qtty+1, j+1)):#how many tgt goes to before otto
                    tmp=factorial(tgt)//factorial(tgt-qtty)*(other)*(other-1)*seq(k, j-k, qtty, False, lvl+1)*factorial(length-qtty-j-2)
                    print('\t',tmp)
                    #if k>1:
                    tmp*=(factorial(tgt-qtty)//factorial(k)//factorial(tgt-qtty-k))
                    print('\t',tmp)
                    #if j-k>1:
                    tmp*=(factorial(other-2)//factorial(j-k)//factorial(other-2-j+k))
                    print('\t\t',tmp)
                    ans+=tmp
            print('!',ans)
            for i in range(qtty+1, tgt+1):
                tmp=seq(tgt,other,i,must,lvl+1)
                print(tmp)
                ans+=tmp
                
        print(lvl*'\t',tgt, other, qtty, must, '\t',ans)
        return(ans)
    else:#not must
        if tgt<qtty:
            ans = factorial(tgt+other)
        else:
            ans = factorial(tgt+other) - seq(tgt,other,qtty,True,lvl+1)
        #print(lvl*'\t',tgt, other, qtty, must, '\t',ans)
        return(ans)

f1()

'''
#print(seq(2, 2, 2, True))
#print(seq(2, 2, 2, False))
assert(seq(2, 4, 2, True) == 240)
assert(seq(3, 2, 2, True)==108)
assert(seq(3, 3, 2, True)==576)
assert(seq(3, 4, 3, True)==720)
assert(seq(3, 4, 2, True)==3600)
assert(seq(3, 5, 2, True)==25920)
assert(seq(3, 6, 2, True)==211680)
print()
print()
print()
'''
#assert(seq(4, 6, 2, True)==3024000)#362880  259200 259200 241920 ... 259200
#
#2177280 only 2
#725760 only 3
#120960 only 4
