import os
import random
names=open("names.txt")
ext=["txt","docx","odt","mp3","pptx","ppt","doc","ini","exe","ods","xls","xlsx","odp","mov","iso","mkv","avi","jpg","jpeg","png","gif"]

for i in list("12345"):
    os.makedirs(i)
    n=names.readline()[:-1]
    f=open(i+"/"+n+"."+ext[random.randint(0,len(ext)-1)],"w")
    f.close()
    for j in list("abcde"):
        os.makedirs(i+"/"+j)
        n=names.readline()[:-1]
        f=open(i+"/"+j+"/"+n+"."+ext[random.randint(0,len(ext)-1)],"w")
        f.close()
        for k in list("@#$%&"):
            os.makedirs(i+"/"+j+"/"+k)
            n=names.readline()[:-1]
            f=open(i+"/"+j+"/"+k+"/"+n+"."+ext[random.randint(0,len(ext)-1)],"w")
            f.close()
            n=names.readline()[:-1]
            f=open(i+"/"+j+"/"+k+"/"+n+"."+ext[random.randint(0,len(ext)-1)],"w")
            f.close()
            

