vowels=["а","я","у","ю","э","е","о","ё","ы","и"]
special=["ь", "ъ"]
def vowcount(str):
    c=0
    for i in str:
        if i in vowels:
            c+=1
    return c
let=5
vow=2
f=open(str(let)+" "+str(vow)+".txt","r")
f1=open("has vows no conseq rep "+str(let)+" "+str(vow) +".txt","w")
l=[]
l=f.readlines()

#l1=[l2 for l2 in l if (vowcount(l2)==3) and len(l2)==8 and len(set(l2))==len(l2) and "ь" in l2]
#аб-----
for i in l:
    i=i[:-1].lower()
    f1.write("<question type=\"shortanswer\">\n")
    f1.write("<name>\n")
    f1.write("<text>" +i+ "</text>\n")
    f1.write("</name>\n")
    f1.write("<questiontext format=\"html\">\n")
    f1.write("<text><![CDATA[<p>Сколько слов длиной в "+str(let)+" букв (не обязательно осмысленных) можно составить ")
    f1.write("из букв слова \""+i+"\", если в них должна быть хотя бы одна гласная, не должно стоять двух одинаковых букв подряд, и при этом буквы из исходного слова можно использовать любое количество раз?</p>]]></text>\n")
    f1.write("</questiontext>\n")
    f1.write("<generalfeedback format=\"html\">\n")
    f1.write("<text></text>\n")
    f1.write("</generalfeedback>\n")
    f1.write("<defaultgrade>1.0000000</defaultgrade>\n")
    f1.write("<penalty>0.3333333</penalty>\n")
    f1.write("<hidden>0</hidden>\n")
    f1.write("<idnumber></idnumber>\n")
    f1.write("<usecase>0</usecase>\n")
    f1.write("<answer fraction=\"100\" format=\"moodle_auto_format\">\n")
    f1.write("<text>1232</text>\n")
    f1.write("<feedback format=\"html\">\n")
    f1.write("<text></text>\n")
    f1.write("</feedback>\n" )
    f1.write("</answer>\n")
    f1.write("</question>\n\n" )
    
f.close()
f1.close()
