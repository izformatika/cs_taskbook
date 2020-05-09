from collections import Counter
vowels=["а","я","у","ю","э","е","о","ё","ы","и"]
special=["ь", "ъ"]
def vowcount(str):
    c=0
    for i in str:
        if i in vowels:
            c+=1
    return c
f=open("russian_nouns.txt","r",encoding="UTF8")

l=[]
l=f.readlines()
f.close()
for i in l:
    signature=list(Counter(i[:-1]).values())
    signature.sort()
    f1=open(str(signature)+".txt","a+")
    f1.write(i)
    f1.close()


'''l=[]
l=f.readlines()
f.close()
for i in l:
    if len(set(i))==len(i) and "ь" not in i and "ъ" not in i:
        vow=vowcount(i)
        cons=len(i)-vow
        f1=open("vow "+str(vow)+" cons "+str(cons)+".txt", "a+")
        f1.write(i)
        f1.close()
'''
