#coding: utf-8
from math import ceil
from random import randint
import winsound

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

def eratosphenes(upto):
    upto += 1
    cand = list(range(upto))
    for i in range(2, ceil(upto**0.5)):
        for j in range(i*i, upto, i):
            cand[j] = 0
    return list(filter(lambda x: x>1, cand))

primes = eratosphenes(50000)

numbers = []

class generator:
    ans_types = 1
    txt = ""
    def gen(self, lst, upto):
        return {}
    
class two(generator):
    ans_types = 2
    desc = "у которых ровно два различных нетривиальных делителя"
    range_len = 1000
    window_size = 4
    def gen(self, lst, upto):
        res = []
        for a in range(len(lst)):
            for b in range(a+1, len(lst)):
                if lst[a]*lst[b] <= upto:
                    res.append((lst[a]*lst[b], 0))
                if lst[a]*lst[b]>upto:
                    break
            if lst[a]>=upto**0.5:
                break
        for a in lst:
            if a**3 > upto:
                break
            res.append((a**3, 1))
        res.sort()
        res = [(i, res[i][0], res[i][1]) for i in range(len(res))]
        return res
    
class three(generator):
    ans_types = 1
    desc = "у которых ровно три различных нетривиальных делителя"
    range_len = 50000000
    window_size = 4
    def gen(self, lst, upto):
        res = []
        for a in lst:
            if a**4 > upto:
                break
            res.append((a**4, 1))
        res.sort()
        res = [(i, res[i][0], res[i][1]) for i in range(len(res))]
        return res

class four(generator):
    ans_types = 2
    desc = "у которых ровно четыре различных нетривиальных делителя"
    range_len = 20000
    window_size = 4
    def gen(self, lst, upto):
        res = []
        for a in range(len(lst)):
            for b in range(len(lst)):
                if a == b:
                    continue
                if lst[a]*lst[a]*lst[b]>upto:
                    break                
                if lst[a]*lst[a]*lst[b] <= upto:
                    res.append((lst[a]*lst[a]*lst[b], 0))
                
            if lst[a]>=upto**0.5:
                break        
        for a in lst:
            if a**5 > upto:
                break
            res.append((a**5, 1))
        res.sort()
        res = [(i, res[i][0], res[i][1]) for i in range(len(res))]
        return res
    
class five(generator):
    ans_types = 1
    desc = "у которых ровно пять различных нетривиальных делителей"
    range_len = 100000
    window_size = 4
    def gen(self, lst, upto):
        res = []
        
        for a in lst:
            if a**6 > upto:
                break
            res.append((a**6, 1))
        res.sort()
        res = [(i, res[i][0], res[i][1]) for i in range(len(res))]
        return res

class six(generator):
    ans_types = 3
    desc = "у которых ровно шесть различных нетривиальных делителей"
    range_len = 40000
    window_size = 10
    def gen(self, lst, upto):
        res = []
        for a in range(len(lst)):
            for b in range(a+1, len(lst)):
                for c in range(b+1, len(lst)):
            
                    cur = lst[a]*lst[b]*lst[c]
                    if cur>upto:
                        break                
                    if cur <= upto:
                        res.append((cur, 0))
                if upto / (lst[a]*lst[b])>lst[b]:
                    break
            if lst[a]>=upto**0.5:
                break
        for a in range(len(lst)):
            for b in range(len(lst)):
                if a == b:
                    continue
                cur = lst[a]*lst[a]*lst[a]*lst[b]
                if cur>upto:
                    break                
                if cur <= upto:
                    res.append((cur, 1))
                
            if lst[a]>=upto**0.5:
                break        
        
        for a in lst:
            if a**7 > upto:
                break
            res.append((a**7, 2))
        res.sort()
        res = [(i, res[i][0], res[i][1]) for i in range(len(res))]
        return res
    
file = open("data.xml", 'w', encoding='utf-8')
file.write('<?xml version="1.0" encoding="UTF-8"?><quiz>')
t = six()#TODO: setup here
prods = t.gen(primes, 1000000000)
print('halfway there')
#print(prods)
window_size = t.window_size
cur_window = prods[:window_size]
types = [i[2] for i in cur_window]
prenum = 0
done = 0
for i in range(window_size, len(prods) - 1):
    if len(set(types)) == t.ans_types and prenum+1 < cur_window[i%window_size][1]:# and prenum > 10000000:    
        prenum = prenum+1
        postnum = prods[cur_window[(i-1)%window_size][0]+1][1]-1
        if postnum > cur_window[(i-1)%window_size][1] and postnum-prenum > t.range_len:
                print(prenum, cur_window, postnum, postnum-prenum)
                question_txt = f"Найдите все натуральные числа на отрезке [{prenum}, {postnum}], {t.desc}. В ответе перечислите эти числа в порядке возрастания через пробел."
                ans_txt = " ".join(list(map(str, sorted([i[1] for i in cur_window]))))
                shortanswer(f"{done:0>3}", question_txt, ans_txt, file)
                done += 1
    prenum = cur_window[i%window_size][1]
    cur_window[i%window_size] = prods[i]
    types[i%window_size] = prods[i][2]

file.write("</quiz>")
file.close()
winsound.Beep(2500, 1000)
