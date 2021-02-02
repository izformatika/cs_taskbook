# coding=cp1251
import common

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
        
