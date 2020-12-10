# coding=cp1251
from collections import Counter
vowels=["а","я","у","ю","э","е","о","ё","ы","и"]
special=["ь", "ъ"]
def vowcount(str):
    c=0
    for i in str:
        if i in vowels:
            c+=1
    return c
l=[]

def letters(n):
    if 5 <= n%100 <= 20:
        return "букв"
    elif n % 10 == 1:
        return "буква"
    elif 2 <= n % 10 <= 4:
        return "буквы"
    else:
        return "букв"
    

def all_to_uniq_nuniq():
    f=open("russian_nouns.txt","r",encoding="UTF8")
    l=f.readlines()
    f.close()
    uniq = open("uniq.txt","a+",encoding="UTF8")
    nuniq = open("nuniq.txt","a+",encoding="UTF8")
    for i in l:
        signature=list(Counter(i[:-1]).values())
        if len(signature) == len(i) - 1:
            uniq.write(i)
        else:
            nuniq.write(i)
    uniq.close()
    nuniq.close()

def uniq_to_sig():
    f=open("uniq.txt","r",encoding="UTF8")
    l=[]
    l=f.readlines()
    f.close()
    j = 0
    for i in l:
        vow_count = 0
        spec_count = 0
        for let in i[:-1]:
            if let in vowels:
                vow_count += 1
            elif let in special:
                spec_count += 1
        file=open("sig/uniq/vow "+str(vow_count)+" cons " + str(len(i) - spec_count - vow_count - 1)+" spec " + str(spec_count) + ".txt", "a+",encoding="UTF8")
        file.write(i)
        file.close()
        j += 1
        if j % 100 == 0:
            print(str(j) + ' of ' + str(len(l)))
    print('uniq done')

def nuniq_to_sig():
    f=open("nuniq.txt","r",encoding="UTF8")
    l=[]
    l=f.readlines()
    f.close()
    j = 0
    for i in l:
        vow_sub = []
        cons_sub = []
        spec_sub = []
        for let in i[:-1]:
            if let in vowels:
                vow_sub.append(let)
            elif let in special:
                spec_sub.append(let)
            else:
                cons_sub.append(let)
        vow_sig=list(Counter(vow_sub).values())
        cons_sig=list(Counter(cons_sub).values())
        spec_sig=list(Counter(spec_sub).values())
        vow_sig.sort()
        cons_sig.sort()
        spec_sig.sort()
        file=open("sig/nuniq/vow "+str(vow_sig)+" cons "+str(cons_sig)+" spec "+str(spec_sig)+".txt","a+",encoding="UTF8")
        file.write(i)
        file.close()
        j += 1
        if j % 100 == 0:
            print(str(j) + ' of ' + str(len(l)))
from os import walk
from math import factorial
def Q_uniq_spec_position(mode, difficulty):
    '''
    mode 0 after vow
    mode 1 before vow
    mode 2 not after vow
    mode 3 not before vow
    diff 0 50 < answer < 500
    diff 1 5000 < answer < 30000
    '''
    ansdict = {}#in every question
    flist = []
    for(dirpath, dirnames, filenames) in walk('sig/uniq'):
        flist.extend(filenames)
    for filename in flist:
        spec = int(filename[-6:-4].replace('.',''))#unsafe
        if spec != 1:
            continue
        vows = int(filename[4:6])#unsafe
        cons = int(filename[10:13].replace('.',''))#unsafe
        length = vows + cons + spec
        ans = -1
        if mode == 0 or mode == 1:
            ans = vows * factorial(length - 2) * (length - 1)
        elif mode == 2 or mode == 3:
            ans = factorial(length) - vows * factorial(length - 2) * (length - 1)
        else:
            ans = -1
        if difficulty == 1 and (ans < 5000 or ans > 30000) \
           or difficulty == 0 and (ans < 50 or ans > 500):
            continue
        if ans not in ansdict.keys():#in every question
            ansdict[ans] = 0
        elif ansdict[ans] > 30:
            continue
        f = open("sig/uniq/" + filename, "r", encoding = "UTF8")
        l = f.readlines()
        f.close()
        if len(l) == 0:#shouldnt be, otherwise file wouldnt be created
            continue
        file = open("spec pos " + str(mode) + " " + str(difficulty) + ".txt", "a+")
        for i in l:
            if ans not in ansdict.keys():#in every question
                ansdict[ans] = 0
            elif ansdict[ans] < 30:
                ansdict[ans] = ansdict[ans] + 1
            else:
                break
            question = "Сколько слов длиной в "+str(length)+ " " + letters(length) + " (не обязательно осмысленных) можно составить " + \
                "из букв слова \""+i[:-1]+"\", если в них " + ("мягкий" if "ь" in i else "твёрдый") + " знак должен стоять строго "
            if mode == 0:
                question += "после гласной"
            elif mode == 1:
                question += "перед гласной"
            elif mode == 2:
                question += "не после гласной"
            elif mode == 3:
                question += "не перед гласной"
            else:
                question += "ОШИБКА"
            question += ", и при этом буквы из исходного слова можно использовать ровно по одному разу?"
            shortanswer(i[:-1], question, ans, file)
        file.close()
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
    for(dirpath, dirnames, filenames) in walk('sig/uniq'):
        flist.extend(filenames)
    for filename in flist:
        spec = int(filename[-6:-4].replace('.',''))
        vows = int(filename[4:6])
        cons = int(filename[10:13].replace('.',''))
        length = vows + cons + spec
        mid = length - abs(first) - abs(last)
        if length <= 2 or abs(last) > length or abs(first) > length or abs(first)+abs(last)>=length:
            continue
        if first < 0 and last>0 and mid+last < -first:
            #print("not enough letters to fill in starting slots")
            continue

        ans = 0
        def two_lists(f,m,after):
            pre=[]
            ans = 0
            cur = 1
            while len(pre) <= f:
                print(*pre, '\t', *after)
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
                    if pre[-1]==1 and len(pre)!=f-1:#todo: not sure here
                        alarm = True
                        break
                    pre.append(pre[-1] - 1)
                after.pop(0)
            print()
            return ans + (cur*m if not alarm else 0)#todo: and here
        if last > 0 and first < 0:
            ffirst = -first
            if last >= ffirst:#--------------------------------------OK
                ans=two_lists(ffirst,mid,[i for i in range(mid + ffirst, 0, -1)])#i think this can be done simpler, but im too stupid for it
            else: #last < first#--------------------------------------OK
                ans=two_lists(ffirst,mid,[i for i in range(mid, 0, -1)][:ffirst-last]+[i for i in range(mid-(ffirst-last) + ffirst, 0, -1)])
        elif last > 0 and first > 0:
            ans=factorial(first)*(mid+1)*factorial(mid)#--------------OK
        elif last < 0 and first < 0:
            llast=-last
            ffirst=-first#todo: wrong answer alchnost -3 -2 must be 6192, says 1500
            if llast >= ffirst:
                ans=factorial(llast+mid)//factorial(ffirst)*factorial(llast+mid) - two_lists(ffirst,mid,[i for i in range(mid + ffirst, 0, -1)])
            else: #last < first
                ans=factorial(llast+mid)//factorial(ffirst)*factorial(llast+mid) - two_lists(ffirst,mid,[i for i in range(mid, 0, -1)][:ffirst-llast]+[i for i in range(mid-(ffirst-llast) + ffirst, 0, -1)])            
        else:#todo other formulas
            ans = -1
            
        if ans < 0:
            continue
        if difficulty == 1 and (ans < 5000 or ans > 30000) \
           or difficulty == 0 and (ans < 50 or ans > 2000):
            continue
            
        if length not in ansdict.keys():#in every question
            ansdict[length] = 0
        elif ansdict[length] > 1:#TODO: 30 when all debugged, unique answers for now
            continue
        f = open("sig/uniq/" + filename, "r", encoding = "UTF8")
        l = f.readlines()
        f.close()
        if len(l) == 0:#shouldnt be, otherwise file wouldnt be created
            continue
        file = open("uniq two conseq " +str(first) + ' ' +str(last) + ' ' + str(difficulty) + ".txt", "a+")
        for i in l:
            if length not in ansdict.keys():#in every question
                ansdict[length] = 0
            elif ansdict[length] < 1:#TODO: 30
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
                            ("\" не должны встречаться" if first < 0 else "\" обязательно должны встречаться только") + " на первых " + str(abs(first)) + " позициях."
            
            shortanswer(i[:-1], question, ans, file)
        file.close()

def shortanswer(name, question, answer, file):
    file.write("<question type=\"shortanswer\">\n")
    file.write("<name>\n")
    file.write("<text>" +name+ "</text>\n")
    file.write("</name>\n")
    file.write("<questiontext format=\"html\">\n")
    file.write("<text><![CDATA[<p>" + question + "</p>]]></text>\n")
    file.write("</questiontext>\n")
    file.write("<generalfeedback format=\"html\">\n")
    file.write("<text></text>\n")
    file.write("</generalfeedback>\n")
    file.write("<defaultgrade>1.0000000</defaultgrade>\n")
    file.write("<penalty>0.3333333</penalty>\n")
    file.write("<hidden>0</hidden>\n")
    file.write("<idnumber></idnumber>\n")
    file.write("<usecase>0</usecase>\n")
    file.write("<answer fraction=\"100\" format=\"moodle_auto_format\">\n")
    file.write("<text>" + str(answer) + "</text>\n")
    file.write("<feedback format=\"html\">\n")
    file.write("<text></text>\n")
    file.write("</feedback>\n" )
    file.write("</answer>\n")
    file.write("</question>\n\n" )
        
#uniq_spec_position()
#print(factorial(5))
#uniq_to_sig()

#Q_not_two_conseq(1)
'''
for i in range(4):
    Q_uniq_spec_position(i, 0)
    Q_uniq_spec_position(i, 1)


for i in range(-5,5):
    for j in range(-5,5):
        print('go')
        Q_uniq_several_seq(i, j, 0)#doesnt work, wrong answers
        '''
Q_uniq_several_seq(-3,-2,0)