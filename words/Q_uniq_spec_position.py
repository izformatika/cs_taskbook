# coding=cp1251
import common
def Q_uniq_spec_position(mode, difficulty):
    '''
    mode 0 after vow
    mode 1 before vow
    mode 2 not after vow
    mode 3 not before vow
    diff 0 50 < answer < 500
    diff 1 5000 < answer < 30000
    '''
    rm_old_questions()
    ansdict = {}#in every question
    flist = []
    for(dirpath, dirnames, filenames) in walk('sig/uniq'):
        flist.extend(filenames)
    for filename in flist:
        spec = int(filename[-6:-4].replace('.',''))#unsafe
        if spec != 1:
            continue
        vows = int(filename[4:6])#unsafe
        cons = int(filename[10:13].replace('.',''))#unsafe
        length = vows + cons + spec
        ans = -1
        if mode == 0 or mode == 1:
            ans = vows * factorial(length - 2) * (length - 1)
        elif mode == 2 or mode == 3:
            ans = factorial(length) - vows * factorial(length - 2) * (length - 1)
        else:
            ans = -1
        if difficulty == 1 and (ans < 5000 or ans > 30000) \
           or difficulty == 0 and (ans < 50 or ans > 500):
            continue
        if ans not in ansdict.keys():#in every question
            ansdict[ans] = 0
        elif ansdict[ans] > 30:
            continue
        f = open("sig/uniq/" + filename, "r", encoding = "UTF8")
        l = f.readlines()
        f.close()
        if len(l) == 0:#shouldnt be, otherwise file wouldnt be created
            continue
        file = open("spec pos " + str(mode) + " " + str(difficulty) + ".txt", "a+")
        for i in l:
            if ans not in ansdict.keys():#in every question
                ansdict[ans] = 0
            elif ansdict[ans] < 30:
                ansdict[ans] = ansdict[ans] + 1
            else:
                break
            question = "Сколько слов длиной в "+str(length)+ " " + letters(length) + " (не обязательно осмысленных) можно составить " + \
                "из букв слова \""+i[:-1]+"\", если в них " + ("мягкий" if "ь" in i else "твёрдый") + " знак должен стоять строго "
            if mode == 0:
                question += "после гласной"
            elif mode == 1:
                question += "перед гласной"
            elif mode == 2:
                question += "не после гласной"
            elif mode == 3:
                question += "не перед гласной"
            else:
                question += "ОШИБКА"
            question += ", и при этом буквы из исходного слова можно использовать ровно по одному разу?"
            shortanswer(i[:-1], question, ans, file)
        file.close()