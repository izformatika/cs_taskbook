# coding=cp1251
from collections import Counter
alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
vowels=["а","я","у","ю","э","е","о","ё","ы","и"]
special=["ь", "ъ"]
def vowcount(str):
    c=0
    for i in str:
        if i in vowels:
            c+=1
    return c
l=[]

def rm_old_questions():
    import shutil
    try:
        shutil.rmtree('./questions')
    except:
        pass
    import os
    os.makedirs('./questions')    

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
    rm_old_questions()
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
    rm_old_questions()
    if abs(last) < 2:
        print("an ending sequence must be at least 2 letters long (otherwise its not a sequence)")
        return
    
    ansdict = {}#in every question
    flist = []
    #from itertools import permutations
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
        if first < 0 and -first>length//2:
            #print("not enough letters to fill in starting slots")
            continue

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
                    if pre[-1]==1:
                        if len(pre)<f:
                            #print('alarm')
                            alarm=True
                        break
                    pre.append(pre[-1] - 1)
                after.pop(0)
            #print(cur,m)
            return ans + (cur*m if not alarm else 0)
        if last > 0 and first < 0:
            ffirst = -first
            if last >= ffirst:
                ans=two_lists(ffirst,mid,[i for i in range(mid + ffirst, 0, -1)])#i think this can be done simpler, but im too stupid for it
            else: #last < first
                ans=two_lists(ffirst,mid,[i for i in range(mid, 0, -1)][:ffirst-last]+[i for i in range(mid-(ffirst-last) + ffirst, 0, -1)])
        elif last > 0 and first > 0:
            ans=factorial(first)*(mid+1)*factorial(mid)
        elif last < 0 and first < 0:
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
        
        if ans < 0:
            continue
        if difficulty == 1 and (ans < 5000 or ans > 30000) \
           or difficulty == 0 and (ans < 50 or ans > 2000):
            continue
            
        if length not in ansdict.keys():#in every question
            ansdict[length] = 0
        elif ansdict[length] > 30:
            continue
        f = open("sig/uniq/" + filename, "r", encoding = "UTF8")
        l = f.readlines()
        f.close()
        if len(l) == 0:#shouldnt be, otherwise file wouldnt be created
            continue
        file = open("questions/uniq two conseq " +str(first) + ' ' +str(last) + ' ' + str(difficulty) + ".xml", "a+",encoding = "UTF8")
        
        
        for i in l:
            if length not in ansdict.keys():#in every question
                ansdict[length] = 0
            elif ansdict[length] < 30:
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
    def header_and_footer_to_xmls_uniq_seq():
        from re import sub
        flist = []
        for(dirpath, dirnames, filenames) in walk('./questions'):
            flist.extend(filenames)
        for filename in flist:
            first,last,dif=map(int,sub(r"[a-z\.]","",filename).split())
            file = open('./questions/'+filename, "r",encoding = "UTF8")
            txt = file.readlines()
            file.close()
            file = open('./questions/'+filename, "w",encoding = "UTF8")
            file.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
            file.write("<quiz>")
            file.write("<!-- question: 0  -->")
            file.write("<question type=\"category\">")
            file.write("<category>")
            file.write("<text>top/общая информатика/количество информации/комбинаторика/на словах/eq: "+("большие" if dif == 1 else "небольшие")+"/eq: uniq two sequences/eq: "+('+ ' if first>0 else '- ')+('+' if last>0 else '-')+"/eq: "+str(abs(first))+' '+str(abs(last))+"</text>")
            file.write("</category>")
            file.write("<info format=\"moodle_auto_format\">")
            file.write("<text></text>")
            file.write("</info>")
            file.write("</question>")
            for i in txt:
                file.write(i)
            file.write("</quiz>")
            file.close()
    header_and_footer_to_xmls_uniq_seq()
        

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
        


def seq(tgt, other, qtty, must,lvl=0):
    #print("QTTY: "+str(qtty))
    if (qtty*2<tgt):#otherwise the task becomes MUCH harder
        return (-1)
    if other<0:
        return 0
    ans = 0
    length = tgt+other
    if must:
        if tgt < qtty:
            ans = factorial(length)
        elif tgt >= qtty and other == 0:
            ans = factorial(tgt)
        elif tgt == qtty:
            ans = factorial(other+1)*factorial(tgt)
        else:
            tmp=factorial(tgt)//factorial(tgt-qtty)*(other)*factorial(length-qtty-1)#5 5 2 + - 504000 ok
            #print('\t'*lvl+f'tto - factorial({tgt})//factorial({tgt-qtty})*({other})*factorial({length-qtty-1})')
            #print('\t'*lvl+str(tmp))
            ans+=tmp
            tmp=factorial(tgt)//factorial(tgt-qtty)*(other)*seq(tgt-qtty,other-1,qtty,False)#5 5 2 + - 144000 ok
            #print('\t'*lvl+f'ott - factorial({tgt})//factorial({tgt-qtty})*({other})*seq({tgt-qtty},{other-1},{qtty},False)')
            #print('\t'*lvl+str(tmp))
            ans+=tmp
            for j in range(length-qtty-2+1):#before otto
                after = length-qtty-j-2
                ttmp = 0
                #print('\t'*lvl+f'[{j}][{after}]')
                for k in range(max(0,tgt-qtty-after), min(tgt-qtty+1, j+1)):#how many tgt goes to before otto
                    tmp=factorial(tgt)//factorial(tgt-qtty)*(other)*(other-1)*seq(k, j-k, qtty, False, lvl+1)*factorial(length-qtty-j-2)#5 5 2 +: [0][6] 288000; [1][5] 288000; [2][4] 230400; [3][3] 187200; [4][2] 144000; [5][1] 100800; [6][0] 57600
                    #print('\t'*lvl+f'otto factorial({tgt})//factorial({tgt-qtty})*({other})*({other-1})*seq({k}, {j-k}, {qtty}, False, {lvl+1})*factorial({length-qtty-j-2})')
                    #print('\t'*lvl,tmp)
                    #if k>1:
                    tmp*=(factorial(tgt-qtty)//factorial(k)//factorial(tgt-qtty-k))
                    #print('\t',tmp)
                    #if j-k>1:
                    tmp*=(factorial(other-2)//factorial(j-k)//factorial(other-2-j+k))
                    #print('\t'*lvl+'\t\t'+str(tmp))
                    ttmp+=tmp
                #print('\t'*lvl+str(ttmp))
                ans+=ttmp
            #print('\t'*lvl+'! only ', qtty, ' ',ans)
            tmp=seq(tgt,other,qtty+1,must,lvl+1)
            #print(tmp)
            ans+=tmp
                
        #print(lvl*'\t',tgt, other, qtty, must, '\t',ans)
        return(ans)
    else:#not must
        if tgt<qtty:
            ans = factorial(tgt+other)
        else:
            ans = factorial(tgt+other) - seq(tgt,other,qtty,True,lvl+1)
        #print(lvl*'\t',tgt, other, qtty, must, '\t',ans)
        return(ans)


def Q_uniq_several_vows(vow, qtty, must, difficulty):
    '''
    vow = True - several vows in a row, False - consonants
    qtty - how many in a row
    must - True/False
    diff 0 50 < answer < 500
    diff 1 5000 < answer < 30000
    '''
    rm_old_questions()
    if qtty <= 1:
        return
    ansdict = {}
    flist = []
   
    for(dirpath, dirnames, filenames) in walk('sig/uniq'):
        flist.extend(filenames)
    for filename in flist:
        spec = int(filename[-6:-4].replace('.',''))
        vows = int(filename[4:6])
        cons = int(filename[10:13].replace('.',''))
        length = vows + cons + spec
        if must and (vow and vows < qtty or not vow and cons < qtty):
            continue
        if not must and not vow and (cons > int(length/2+1) or cons <= qtty):
            continue
        if not must and vow and (vows > int(length/2+1) or vows <= qtty):
            continue        
        ans = 0
        if (vows, cons, spec) in ansdict:
            if ansdict[(vows,cons,spec)][1]>=10:
                continue
            else:
                ans = ansdict[(vows,cons,spec)][0]
        else:
            if vow:
                tgt = vows
                other = cons+spec
            else:
                tgt = cons
                other = vows+spec
            ans = seq(tgt, other, qtty, must)
            if ans==-1:
                continue
            ansdict[(vows,cons,spec)] = [ans,0]
        #print(ans)
        if difficulty == 0 and not (50 <= ans <= 500) or difficulty == 1 and not (5000 <= ans <= 30000):
            continue
        f = open("sig/uniq/" + filename, "r", encoding = "UTF8")
        l = f.readlines()
        f.close()
        if len(l) == 0:#shouldnt be, otherwise file wouldnt be created
            continue            
        file = open("questions/uniq " +('+' if must else '-') + str(qtty) + ' ' +('vows' if vow else 'cons') + ' ' + str(difficulty) + ".xml", "a+",encoding = "UTF8")
        for wrd in l:
            if ansdict[(vows,cons,spec)][1]>=10:
                break
            ansdict[(vows,cons,spec)][1]+=1
            question = 'Сколько слов (не обязательно осмысленных) длиной '+ str(length) + ' '+letters(length)+' можно составить из букв слова \'' +  wrd[:-1] + '\', если каждую букву можно использовать ровно один раз, и при этом в слове ' + ('обязательно' if must else 'не') + \
                ' должна встречаться последовательность из ' + str(qtty) + (' со' if not vow else ' ') + 'гласных букв?'
            shortanswer(wrd[:-1], question, ans, file)
            
        file.close()
        def header_and_footer_to_xmls_uniq_vow():
            from re import sub
            flist = []
            for(dirpath, dirnames, filenames) in walk('./questions'):
                flist.extend(filenames)
            for filename in flist:
                qtty=int(filename[5:7])
                let =filename[8:12] 
                dif = int(filename[-5:-4])
                file = open('./questions/'+filename, "r",encoding = "UTF8")
                txt = file.readlines()
                file.close()
                file = open('./questions/'+filename, "w",encoding = "UTF8")
                file.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
                file.write("<quiz>")
                file.write("<!-- question: 0  -->")
                file.write("<question type=\"category\">")
                file.write("<category>")
                file.write("<text>top/общая информатика/количество информации/комбинаторика/на словах/eq: "+("большие" if dif == 1 else "небольшие")+"/eq: uniq vows/eq: " + ("-" if qtty<0 else "+")+ "/eq: "+str(abs(qtty))+"</text>")
                file.write("</category>")
                file.write("<info format=\"moodle_auto_format\">")
                file.write("<text></text>")
                file.write("</info>")
                file.write("</question>")
                for i in txt:
                    file.write(i)
                file.write("</quiz>")
                file.close()
    header_and_footer_to_xmls_uniq_vow()
        
    
            
#for i in range(4):
#    Q_uniq_spec_position(i, 0)
#    Q_uniq_spec_position(i, 1)


#Q_uniq_several_seq(-3,-2,0)

     

#for i in range(-5,5):
#    for j in range(-5,5):
#        Q_uniq_several_seq(i, j, 1)

'''for i in (True, False):
    for j in range(2,10):
        for k in (True, False):
            Q_uniq_several_vows(i, j, k, 1)
            
header_and_footer_to_xmls_uniq_vow()
'''

def Q_uniq_any():
    rm_old_questions()
    ansdict = {}
    flist = []
   
    for(dirpath, dirnames, filenames) in walk('sig/uniq'):
        flist.extend(filenames)
    for filename in flist:
        spec = int(filename[-6:-4].replace('.',''))
        vows = int(filename[4:6])
        cons = int(filename[10:13].replace('.',''))
        length = vows + cons + spec
        for curlen in range(5, length):
            ans = factorial(length)//factorial(length-curlen)
            if ans in ansdict and ansdict[ans]>10:
                continue
            if not (50 <= ans <= 20000):
                continue
            f = open("sig/uniq/" + filename, "r", encoding = "UTF8")
            l = f.readlines()
            f.close()
            if len(l) == 0:#shouldnt be, otherwise file wouldnt be created
                continue            
            file = open("questions/uniq any.xml", "a+",encoding = "UTF8")
            for wrd in l:
                if ans in ansdict and ansdict[ans]>10:
                    break
                elif ans not in ansdict:
                    ansdict[ans] = 0
                ansdict[ans]+=1
                question = 'Сколько слов (не обязательно осмысленных) длиной '+ str(curlen) + ' '+letters(curlen)+' можно составить из букв слова \'' +  wrd[:-1] + '\', если каждую букву можно использовать ровно один раз?'#TODO: other lengths!
                shortanswer(wrd[:-1], question, ans, file)
                
            file.close()
    def header_and_footer_to_xmls_uniq_any():
        flist = []
        for(dirpath, dirnames, filenames) in walk('./questions'):
            flist.extend(filenames)
        for filename in flist:
            file = open('./questions/'+filename, "r",encoding = "UTF8")
            txt = file.readlines()
            file.close()
            file = open('./questions/'+filename, "w",encoding = "UTF8")
            file.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
            file.write("<quiz>")
            file.write("<!-- question: 0  -->")
            file.write("<question type=\"category\">")
            file.write("<category>")
            file.write("<text>top/общая информатика/количество информации/комбинаторика/на словах/eq: небольшие"+"/eq: uniq any</text>")
            file.write("</category>")
            file.write("<info format=\"moodle_auto_format\">")
            file.write("<text></text>")
            file.write("</info>")
            file.write("</question>")
            for i in txt:
                file.write(i)
            file.write("</quiz>")
            file.close()        
        header_and_footer_to_xmls_uniq_any()
        

        
#Q_uniq_any()
#header_and_footer_to_xmls_uniq_any()

def Q_nuniq_any():
    rm_old_questions()
    from math import factorial
    ansdict = {}
    flist = []
   
    for(dirpath, dirnames, filenames) in walk('sig/nuniq'):
        flist.extend(filenames)
    for filename in flist:
        from re import sub
        sig = list((map(int, sub("[^0-9]"," ", filename).split())))
        dif_letters = len(sig)
        orig_len = sum(sig)
        if orig_len > 10:
            continue
        for curlen in range(3, min(orig_len, dif_letters)):
            ans = factorial(dif_letters)//factorial(dif_letters-curlen)
            if ans in ansdict and ansdict[ans]>10:
                continue
            if not (50 <= ans <= 5000):
                continue
            f = open("sig/nuniq/" + filename, "r", encoding = "UTF8")
            l = f.readlines()
            f.close()
            if len(l) == 0:#shouldnt be, otherwise file wouldnt be created
                continue            
            file = open("questions/nuniq any " + str(curlen) + ".xml", "a+",encoding = "UTF8")
            for wrd in l:
                if ans in ansdict and ansdict[ans]>10:
                    break
                elif ans not in ansdict:
                    ansdict[ans] = 0
                ansdict[ans]+=1
                question = 'Сколько слов (не обязательно осмысленных) длиной '+ str(curlen) + ' '+letters(curlen)+' можно составить из букв слова \'' +  wrd[:-1] + '\', если каждую букву можно использовать сколько угодно раз?'
                shortanswer(wrd[:-1], question, ans, file)
                
            file.close()
    #header
    flist = []
    for(dirpath, dirnames, filenames) in walk('./questions'):
        flist.extend(filenames)
    for filename in flist:
        qtty=int(filename[10:11].replace(".",''))
        file = open('./questions/'+filename, "r",encoding = "UTF8")
        txt = file.readlines()
        file.close()
        file = open('./questions/'+filename, "w",encoding = "UTF8")
        file.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
        file.write("<quiz>")
        file.write("<!-- question: 0  -->")
        file.write("<question type=\"category\">")
        file.write("<category>")
        file.write("<text>top/общая информатика/количество информации/комбинаторика/на словах/eq: небольшие"+"/eq: nuniq any/eq: " +str(qtty)+"</text>")
        file.write("</category>")
        file.write("<info format=\"moodle_auto_format\">")
        file.write("<text></text>")
        file.write("</info>")
        file.write("</question>")
        for i in txt:
            file.write(i)
        file.write("</quiz>")
        file.close()
        
        
        
#Q_nuniq_any()

def Q_nuniq_min_vowels(min_vow):
    rm_old_questions()
    from math import factorial
    ansdict = {}
    flist = []
    resflist = []
   
    for(dirpath, dirnames, filenames) in walk('sig/nuniq'):
        flist.extend(filenames)
    for filename in flist:
        from re import sub, match
        sig = list(match("vow \[(.*)\] cons \[(.*)\] spec \[(.*)\].txt", filename).groups())
        vow_sig = [i for i in map(int, sub(",", " ", sig[0]).split())]
        cons_sig = [i for i in map(int, sub(",", " ", sig[1]).split())]
        spec_sig = [i for i in map(int, sub(",", " ", sig[2]).split())]
        orig_len = sum(vow_sig + cons_sig + spec_sig)
        uniq_let = len(vow_sig) + len(cons_sig) + len(spec_sig)
        if uniq_let < 4 or uniq_let > 10 or orig_len > 10:
            continue
        for curlen in range(5, 7):
            ans = 0
            for curvow in range(min_vow, curlen + 1):
                ans += (len(vow_sig)**min_vow)*((len(cons_sig)+len(spec_sig))**(curlen-min_vow))*factorial(curlen)//factorial(curlen - curvow)
            if ans in ansdict and ansdict[ans]>10:
                continue
            if not (50 <= ans <= 5000):
                continue
            f = open("sig/nuniq/" + filename, "r", encoding = "UTF8")
            l = f.readlines()
            f.close()
            if len(l) == 0:#shouldnt be, otherwise file wouldnt be created
                continue            
            if ("questions/nuniq minvow " + str(min_vow) + ".xml") not in resflist:
                resflist.append("questions/nuniq minvow " + str(min_vow) + ".xml")
            file = open(resflist[-1], "a+",encoding = "UTF8")
            for wrd in l:
                if ans in ansdict and ansdict[ans]>10:
                    break
                elif ans not in ansdict:
                    ansdict[ans] = 0
                ansdict[ans]+=1
                question = 'Сколько слов (не обязательно осмысленных) длиной '+ str(curlen) + ' '+letters(curlen)+' можно составить из букв слова \'' +  wrd[:-1] + '\', если каждую букву можно использовать сколько угодно раз, и минимальное количество гласных букв в получившихся словах должно быть равным ' + str(min_vow) + '?'
                shortanswer(wrd[:-1], question, ans, file)
                
            file.close()
    for filename in resflist:
        qtty=int(filename[23:24].replace(".",''))
        file = open(filename, "r",encoding = "UTF8")
        txt = file.readlines()
        file.close()
        file = open(filename, "w",encoding = "UTF8")
        file.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
        file.write("<quiz>")
        file.write("<!-- question: 0  -->")
        file.write("<question type=\"category\">")
        file.write("<category>")
        file.write("<text>top/общая информатика/количество информации/комбинаторика/на словах/eq: небольшие"+"/eq: nuniq minvow/eq: " +str(qtty)+"</text>")
        file.write("</category>")
        file.write("<info format=\"moodle_auto_format\">")
        file.write("<text></text>")
        file.write("</info>")
        file.write("</question>")
        for i in txt:
                file.write(i)
        file.write("</quiz>")
        file.close()
Q_nuniq_min_vowels(2)

import winsound
winsound.Beep(2500, 1000)