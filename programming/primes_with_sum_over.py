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

def eratosphenes(upto, sum_more):
    def good(x):
        if x <= 1:
            return False
        s = 0
        while x > 0:
            s += x%10
            x //= 10
        if s>sum_more:
            return True
        return False
            
    upto += 1
    cand = list(range(upto))
    for i in range(2, ceil(upto**0.5)):
        for j in range(i*i, upto, i):
            cand[j] = 0
    res = list(filter(good, cand))
    return [(i, res[i]) for i in range(len(res))]#this is stupid, but i dont want to calculate previous prime right now
        

sum_more = 35#TODO: config here

primes = eratosphenes(60000, sum_more)


file = open("data.xml", 'w', encoding='utf-8')
file.write('<?xml version="1.0" encoding="UTF-8"?><quiz>')

print('halfway there')
window_size = 3
cur_window = primes[:window_size]

prenum = 0
done = 0
for i in range(window_size, len(primes) - 1):
    if prenum+1 < cur_window[i%window_size][1]:  
        prenum = prenum+1
        postnum = primes[cur_window[(i-1)%window_size][0]+1][1]-1
        if postnum > cur_window[(i-1)%window_size][1] and postnum-prenum>200:
                print(prenum, cur_window, postnum, postnum-prenum)
                question_txt = f"Для отрезка [{prenum}, {postnum}] найдите все простые числа такие, что сумма их цифр больше {sum_more}. В ответе перечислите эти числа в порядке возрастания через пробел."
                ans_txt = " ".join(list(map(str, [j[1] for j in cur_window])))
                shortanswer(f"{done:0>3}", question_txt, ans_txt, file)
                done += 1
    prenum = cur_window[i%window_size][1]
    cur_window[i%window_size] = primes[i]
    

file.write("</quiz>")
file.close()
winsound.Beep(2500, 1000)
