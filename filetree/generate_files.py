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
            

'''
for i in range(30):
	n=names.readline()[:-1]
	curfile = 'folder/'+n+"."+ext[random.randint(0,len(ext)-1)]
	f=open(curfile,"w")
	f.write('0'*random.randint(0, 9999999))
	f.close()    
	year = random.randint(2000, 2020)
	month = random.randint(1, 12)
	day = random.randint(1, 28)
	hour = random.randint(0, 23)
	minute = random.randint(0, 59)
	second = random.randint(0, 59)
	date = datetime.datetime(year=year, month=month, day=day, hour=hour, minute=minute, second=second)
	modTime = time.mktime(date.timetuple())
	os.utime(curfile, (modTime, modTime))

'''