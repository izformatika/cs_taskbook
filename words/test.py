# coding=cp1251
def f1():
    from collections import Counter
    s="��������"
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
                                    #for i9 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, '').replace(i8, ''):
                                        #for i10 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, '').replace(i8, '').replace(i9, ''):
                                    s1=i1+i2+i3+i4+i5+i6+i7+i8#+i9#+i10#+i11+i12+i13+i14
                                        #signature=list(Counter(s1).values())
                                            #if len(signature) == len(s1) - 1 and
                                    if s[0] not in s1[:3] and s[1] not in s1[:3] and s[2] not in s1[:3] and "��" not in s1:
                                        #print(s1)
                                        plus+=1
                                    else:
                                        minus +=1

    print (plus, minus)
    
def f2(first, last):
    from itertools import permutations
    ans = 0
    wrd = "������"
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
        return "букв"
    elif n % 10 == 1:
        return "буква"
    elif 2 <= n % 10 <= 4:
        return "буквы"
    else:
        return "букв"

def Q_uniq_several_seq(first, last, difficulty):
    '''
    diff 0 50 < answer < 500
    diff 1 5000 < answer < 30000
    last length of postfix that has to be (positive)/has to be missing (negative)
    first length of prefix - those letters must (positive)/cant (negative) be in first not_first letters
    '''
    if abs(last) < 2:
        print("an ending sequence must be at least 2 letters long (otherwise its not a sequence)")
        return
    alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
    ansdict = {}#in every question
    flist = []
    from itertools import permutations
    for(dirpath, dirnames, filenames) in walk('sig/debug'):
        flist.extend(filenames)
    for filename in flist[:-1]:
        spec = int(filename[-6:-4].replace('.',''))
        vows = int(filename[4:6])
        cons = int(filename[10:13].replace('.',''))
        length = vows + cons + spec
        mid = length - abs(first) - abs(last)
        if length <= 2 or abs(last) > length or abs(first) > length or abs(first)+abs(last)>=length:
            continue
        if first > 0 and length - first < first:
            #print("not enough letters to fill in starting slots")
            continue

        ans = 0
        if last > 0 and first < 0:
            ffirst = -first
            if last >= ffirst:
                pre = []#i am well aware this can be done simpler, but im too stupid for it
                after = [i for i in range(1, mid + ffirst + 1)]
                ans = 0
                cur = 1
                while len(pre) <= ffirst:
                    print(*pre, '\t', *after)
                    cur = 1
                    for i in pre:
                        cur *= i
                    for i in after:
                        cur *= i
                    #print(cur)
                    ans += cur
                    if len(pre)==0:
                        pre.append(mid)
                    else:
                        pre.append(pre[-1] - 1)
                    after.pop()
                
                ans += cur * mid
            else: #last < first
                pre = []#i am well aware this can be done simpler, but im too stupid for it
                after = [i for i in range(mid, 0, -1)][:ffirst-last]+[i for i in range(mid + ffirst - 1, 0, -1)]
                ans = 0
                cur = 1
                while len(pre) <= ffirst:
                    #print(*pre, '\t', *after)
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
        #elif last > 0 and first > 0:
        else:#todo other formulas
            ans = -1
            '''
        if difficulty == 1 and (ans < 5000 or ans > 30000) \
           or difficulty == 0 and (ans < 50 or ans > 500):
            continue
            '''
        if length not in ansdict.keys():#in every question
            ansdict[length] = 0
        elif ansdict[length] > 1:
            continue
        f = open("sig/debug/" + filename, "r", encoding = "UTF8")
        l = f.readlines()
        f.close()
        if len(l) == 0:#shouldnt be, otherwise file wouldnt be created
            continue
        file = open("uniq two conseq " +str(first) + ' ' +str(last) + ' ' + str(difficulty) + ".txt", "a+")
        for i in l:
            if length not in ansdict.keys():#in every question
                ansdict[length] = 0
            elif ansdict[length] < 1:
                ansdict[length] += 1
            else:
                break
            question = "Сколько слов длиной в "+str(length)+ " " + letters(length) + " (не обязательно осмысленных) можно составить " + \
                "из букв слова \""+i[:-1]+"\", если в них " + \
                ("не" if last < 0 else "обязательно") + " должно встречаться сочетание \"" + i[length-abs(last):-1] + \
                "\", и при этом буквы из исходного слова можно использовать ровно по одному разу?"
            if abs(first) == 1:
                question +=" При этом слова " + ("не" if first < 0 else "обязательно") + " должны начинаться с буквы \"" + i[0]+ "\"."
            else:
                question +=" При этом буквы \"" + '\", \"'.join(i[:abs(first)]) + \
                            ("\" не должны встречаться" if first < 0 else " обязательно должны встречаться только") + " на первых " + str(abs(first)) + " позициях."
            
            shortanswer(i[:-1], question, ans, file)
        file.close()

def shortanswer(name, question, answer, file):
    print (question, answer)
'''        
Q_uniq_several_seq(-3, 2, 0)
f2(3,2)
'''
f1()