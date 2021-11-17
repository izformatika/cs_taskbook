#coding:utf8
# coding=cp1251
    
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

from math import ceil, floor, sqrt, log
from random import randint

rainbow_table = {}

def divisors(x, first):
    div = []
    lim = x**(1//4)
    for i in range(2, x//2+1):
        if x%i==0:
            div.append(i)
            if len(div) >= first:
                return div
        if i>lim and len(div):
            return []
    return div

for f in range(200000000, 300000000):
    if f%1000 == 0:
        print(f)
    d = divisors(f, 8)
    if len(d)==8:
        rainbow_table[f] = d

def gen_task(f, div_qtty, num_qtty, ending):
    modby = 10**ceil(log(ending, 10))
    ans = []
    
    for i in range(f+1, f+1000001):
        divs = rainbow_table[i]
        if len(divs)<div_qtty:
            continue
        divprod = 1
        for j in divs[:div_qtty]:
            divprod*=j
        if divprod<i and divprod%modby == ending:
            ans.append(divprod)
            if len(ans)>=num_qtty:
                return ans
    return []
     
answers = []
file = open("data.xml", 'w', encoding='utf-8')
for f in range(200000000, 500000000, 1000000):
    for div_qtty in range(5, 8):
        for num_qtty in range(5, 8):
            for ending in range(10, 99):
                if ending % 10 == 0:
                    print(ending)
                ans_i=gen_task(f, div_qtty, num_qtty, ending)
                task_txt = f"Пусть M (N) – произведение {div_qtty} наименьших различных натуральных делителей натурального числа N, не считая единицы. Если у числа N меньше {div_qtty} таких делителей, то M (N) считается равным нулю.<br/>\nНайдите {num_qtty} наименьших натуральных чисел, превышающих {f}, для которых 0 < M (N) < N, и M(N) заканчивается на {ending}. <br/>\nВ ответе запишите через пробел только найденные значения M (N) в порядке возрастания соответствующих им чисел N (но не обязательно в порядке возрастания M (N)).<br/>\n<i>Источник задания: диагностическая работа Статград по информатике 27.11.2021, сборник К.Ю. Полякова №25.183.</i>"
                
                if ans_i is None:
                    continue
                if len(ans_i)<num_qtty or ans_i in answers:
                    print(':(')
                    continue
                bad = True
                for i in range(len(ans_i)-1):
                    if ans_i[i]>ans_i[i+1]:
                        bad = False
                        break
                if bad: continue
                answers.append(ans_i)
                ans = ' '.join(list(map(str, ans_i)))
                shortanswer(f'{len(answers):0>2}', task_txt, ans, file)
                if len(ans) >= 30:
                    break   
            if len(ans) >= 30:
                break         
        if len(ans) >= 30:
            break               
    if len(ans) >= 30:
        break
file.close()
import winsound
winsound.Beep(2500, 1000)