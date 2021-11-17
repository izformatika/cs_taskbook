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

from math import ceil, floor, sqrt
def gen_task(f, div_qtty, num_qtty):
    ans = []
    def divisors(x):
        div = [1, x]
        for i in range(2, floor(sqrt(x))):
            if x%i==0:
                div.append(i)
                div.append(x//i)
        if sqrt(x) == floor(sqrt(x)):
            div.append(sqrt(x))
        div.sort()
        return div

    for i in range(f+1, f+10001):
        divs = divisors(i)    
        if len(divs)<div_qtty:
            continue
        divprod = 1
        for j in divs[:div_qtty+1]:
            divprod*=j
        if divprod<i:
            ans.append(divprod)
            if len(ans)>=num_qtty:
                return ans
            
answers = []
file = open("data.xml", 'w', encoding='utf-8')
for f in range(200000000, 1000000000, 1000000):
    for div_qtty in range(5, 8):
        for num_qtty in range(5, 8):
            task_txt = f"Пусть M (N) – произведение {div_qtty} наименьших различных натуральных делителей натурального числа N, не считая единицы. Если у числа N меньше {div_qtty} таких делителей, то M (N) считается равным нулю.<br/>\nНайдите {num_qtty} наименьших натуральных чисел, превышающих {f}, для которых 0 < M (N) < N. <br/>\nВ ответе запишите через пробел только найденные значения M (N) в порядке возрастания соответствующих им чисел N (но не обязательно в порядке возрастания M (N)).<br/>\n<i>Источник задания: диагностическая работа Статград по информатике 27.11.2021.</i>"
            ans_i=gen_task(f, div_qtty, num_qtty)
            if len(ans_i)<num_qtty or ans_i in answers:
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
file.close()
import winsound
winsound.Beep(2500, 1000)