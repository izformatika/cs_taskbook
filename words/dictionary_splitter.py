# coding=cp1251
import common
def all_to_uniq_nuniq():
    f=open("russian_nouns.txt","r",encoding="UTF8")
    l=f.readlines()
    f.close()
    uniq = open("uniq.txt","a+",encoding="UTF8")
    nuniq = open("nuniq.txt","a+",encoding="UTF8")
    for i in l:
        signature=list(Counter(i[:-1]).values())
        if len(signature) == len(i) - 1:
            uniq.write(i)
        else:
            nuniq.write(i)
    uniq.close()
    nuniq.close()

def uniq_to_sig():
    f=open("uniq.txt","r",encoding="UTF8")
    l=[]
    l=f.readlines()
    f.close()
    j = 0
    for i in l:
        vow_count = 0
        spec_count = 0
        for let in i[:-1]:
            if let in vowels:
                vow_count += 1
            elif let in special:
                spec_count += 1
        file=open("sig/uniq/vow "+str(vow_count)+" cons " + str(len(i) - spec_count - vow_count - 1)+" spec " + str(spec_count) + ".txt", "a+",encoding="UTF8")
        file.write(i)
        file.close()
        j += 1
        if j % 100 == 0:
            print(str(j) + ' of ' + str(len(l)))
    print('uniq done')

def nuniq_to_sig():
    f=open("nuniq.txt","r",encoding="UTF8")
    l=[]
    l=f.readlines()
    f.close()
    j = 0
    for i in l:
        vow_sub = []
        cons_sub = []
        spec_sub = []
        for let in i[:-1]:
            if let in vowels:
                vow_sub.append(let)
            elif let in special:
                spec_sub.append(let)
            else:
                cons_sub.append(let)
        vow_sig=list(Counter(vow_sub).values())
        cons_sig=list(Counter(cons_sub).values())
        spec_sig=list(Counter(spec_sub).values())
        vow_sig.sort()
        cons_sig.sort()
        spec_sig.sort()
        file=open("sig/nuniq/vow "+str(vow_sig)+" cons "+str(cons_sig)+" spec "+str(spec_sig)+".txt","a+",encoding="UTF8")
        file.write(i)
        file.close()
        j += 1
        if j % 100 == 0:
            print(str(j) + ' of ' + str(len(l)))
