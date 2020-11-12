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
def Q_uniq_two_conseq(mode, difficulty):# Q_uniq_several_seq , seq, not_first):
    '''
    mode 0 l1l2 not allowed
    mode 1 l1l2 necessary
    diff 0 50 < answer < 500
    diff 1 5000 < answer < 30000
    seq length of postfix that has to be/has to be missing
    not_first length of prefix - those letters cant be in first not_first letters
    '''
    not_first = 2
    ansdict = {}#in every question
    flist = []
    for(dirpath, dirnames, filenames) in walk('sig/uniq'):
        flist.extend(filenames)
    for filename in flist:
        spec = int(filename[-6:-4].replace('.',''))
        vows = int(filename[4:6])
        cons = int(filename[10:13].replace('.',''))
        length = vows + cons + spec
        if length <= 2:
            continue
        ans = 0
        if mode == 0:
            ans = (length - 1)*factorial(length - 1)
        else:
            ans = factorial(length - 1)
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
        file = open("uniq two conseq " +str(mode) + ' ' + str(difficulty) + ' ' + str(not_first) + ".txt", "a+")
        for i in l:
            if ans not in ansdict.keys():#in every question
                ansdict[ans] = 0
            elif ansdict[ans] < 30:
                ansdict[ans] = ansdict[ans] + 1
            else:
                break
            question = "Сколько слов длиной в "+str(length)+ " " + letters(length) + " (не обязательно осмысленных) можно составить " + \
                "из букв слова \""+i[:-1]+"\", если в них " + ("не" if mode == 0 else "обязательно") + " должно встречаться сочетание \"" + i[-3:-1] + "\", и при этом буквы из исходного слова можно использовать ровно по одному разу?"
            if not_first == 1:
                question +=" При этом слова не должны начинаться с буквы " + i[0]+ "."
            elif not_first > 1:
                question +=" При этом буквы " + str(['\'' + str(j) + '\'' for j in i[:not_first]])[2:-2].replace("\"","") + " не должны встречаться на первых " + str(not_first) + " позициях."
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
'''
for i in range(1):
    Q_uniq_two_conseq(0, 0)#, i)
    Q_uniq_two_conseq(1, 0)#, i)
    Q_uniq_two_conseq(0, 1)#, i)
    Q_uniq_two_conseq(1, 1)#, i)
