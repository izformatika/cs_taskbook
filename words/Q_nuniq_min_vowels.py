# coding=cp1251
import common

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
