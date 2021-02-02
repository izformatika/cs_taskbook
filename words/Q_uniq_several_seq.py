# coding=cp1251
import common
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
        
