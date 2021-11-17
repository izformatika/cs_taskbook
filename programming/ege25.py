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
import winsound
#rainbow_table = {}

def divisors(x, first):
    div = []
    divprod = 1
    lim = x**(1/first)
    for i in range(2, x//2+1):
        if x%i==0:
            div.append(i)
            divprod *= i
            if divprod>x:
                return []
            if len(div) >= first:
                return div            
            lim = (x//divprod)**(1/(first - len(div)))
        if i>lim:
            return []
    return div

ending_len = 2
modby = 10**ending_len

def gen_task(f, div_qtty, num_qtty):
    endings = {}
    for i in range(f+1, f+1000001):
        divs = divisors(i, div_qtty)
        if len(divs)<div_qtty:
            continue
        divprod = 1
        for j in divs[:div_qtty]:
            divprod*=j
        if divprod<i:
            ending = divprod%modby
            if ending not in endings.keys():
                endings[ending] = [divs[:div_qtty]]
            else:
                endings[ending].append(divs[:div_qtty])
                if len(endings[ending]) == num_qtty:
                    if i-f<100:
                        return []
                    ans = []
                    for i in endings[ending]:
                        cur = 1
                        for j in i:
                            cur*=j
                        ans.append(cur)
                    return ans
    return []
def product_of_smaller_divisors_less_than_original():     
    answers = {}
    done = 0
    file = open("data.xml", 'w', encoding='utf-8')
    for f in range(200000000, 500000000, 1000000):
        for div_qtty in range(5, 8):
            for num_qtty in range(5, 8):
                ans_i=gen_task(f, div_qtty, num_qtty)
                if ans_i is None or len(ans_i)<num_qtty:
                    continue
                ending = ans_i[0]%modby
                if ending in answers.keys() and answers[ending]>5:
                    continue            
                
                task_txt = f"Пусть M (N) – произведение {div_qtty} наименьших различных натуральных делителей натурального числа N, не считая единицы. Если у числа N меньше {div_qtty} таких делителей, то M (N) считается равным нулю.<br/>\nНайдите {num_qtty} наименьших натуральных чисел, превышающих {f}, для которых 0 < M (N) < N, и M(N) заканчивается на {ending:0>{ending_len}}. <br/>\nВ ответе запишите через пробел только найденные значения M (N) в порядке возрастания соответствующих им чисел N (но не обязательно в порядке возрастания M (N)).<br/>\n<i>Источник задания: диагностическая работа Статград по информатике 27.11.2021, сборник К.Ю. Полякова №25.183.</i>"
                
                bad = True
                for i in range(len(ans_i)-1):
                    if ans_i[i]>ans_i[i+1]:
                        bad = False
                        break
                if bad: continue
                if ending not in answers.keys():
                    answers[ending] = 1
                else:
                    answers[ending]+=1
                ans = ' '.join(list(map(str, ans_i)))
                shortanswer(f'{done:0>2}', task_txt, ans, file)
                done+=1
                print(done)
                file.flush()
                #winsound.Beep(2500, 1000)
                if done >= 30:
                    break          
            if done >= 30:
                break               
        if done >= 30:
            break
    file.close()
    winsound.Beep(2500, 1000)
def eratosphenes(upto):
    upto+=1
    cand = list(range(0, upto))
    cand[1]= 0
    for i in range(2, ceil(sqrt(upto))):
        for j in range(i*2, upto, i):
            cand[j] = 0
    primes = list(filter(lambda x: x!=0, cand))
    return primes
g_primes = []
def is_prime(x):
    if x in g_primes:
        return True
    if x%2 == 0:
        return False
    for i in range(3, ceil(sqrt(x))+1):
        if x%i==0:
            return False
    g_primes.append(x)
    return True
def primes_in_luka():
    #primes = eratosphenes(10**9)
    done = 0
    file = open("data.xml", 'w', encoding='utf-8')
    for aa in 0,1,2,3:
        for bb in 0,1,2,3:
            if aa==0 and bb==0:
                continue
            a=aa
            b=aa
            c=bb
            n = 2
            primes_luka = []
            if is_prime(a):
                primes_luka.append([1, a])
            if is_prime(b):
                primes_luka.append([2, b])                
            while c<10**9:
                a = b
                b = c
                c = a+b
                n+=1
                if is_prime(c):
                    primes_luka.append([n, c])
            if len(primes_luka)<2 or primes_luka[-2][1]<100000:
                continue
            low = 10**floor(log(primes_luka[-2][1], 10))
            task_txt = f"Последовательность Люка – это последовательность чисел, в которых каждое последующее число образуется из суммы двух предшествующих ему чисел. Первые два числа в последовательности Люка: {aa}, {bb}. Найдите все простые числа Люка, принадлежащие отрезку [{low}, 1000000000]. Для каждого найденного числа выведите сначала номер числа в последовательности Люка, а затем само число.<br/><i>Источник задания: сборник К.Ю. Полякова, №23.182</i>"
            ans = list(filter(lambda x:x[1]>low, primes_luka))
            ans = ' '.join([''.join(f"{x[0]} {x[1]}") for x in ans])
            shortanswer(f'{done:0>2}', task_txt, ans, file)
            done+=1
            
primes_in_luka()
                    