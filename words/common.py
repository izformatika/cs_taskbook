# coding=cp1251
from collections import Counter
alphabet = "��������������������������������"
vowels=["�","�","�","�","�","�","�","�","�","�"]
special=["�", "�"]
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
        return "����"
    elif n % 10 == 1:
        return "�����"
    elif 2 <= n % 10 <= 4:
        return "�����"
    else:
        return "����"
    
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
