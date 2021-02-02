# coding=cp1251
import common

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
        
        
