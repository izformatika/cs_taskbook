
# coding: 1251
def find_good_sig():
    s1='текстглавы'.lower()
    for f in range(0, len(s1), 100):
        for t in range(f, len(s1)+1, 100):
            s = s1[f:t]
            counters = [[0, i] for i in range(32)]
            
            for i in s:
                counters[ord(i) - ord('а')][0] += 1
            
            #print(counters)
            counters.sort(key = lambda a: a[0], reverse = True)
            #print(*[ord(i)-ord('а') for i in 'оеаинтсрвл'])
            top_let = [i[1] for i in counters[:10]]
			top_occur = [i[0] for i in counters[:10]]
            #print(top_let)
            if top_let == [14, 5, 0, 8, 13, 18, 17, 16, 2, 11] and len(set(top_occur))==10:
                print(f, t)
def random_encode():
    from random import shuffle
    code = [i for i in range(32)]
    shuffle(code)
    s = 'текстглавы'.lower()[23400:26900]#numbers from find_good_sig
    s1 = ''
    for i in s:
        s1 += chr(ord('а')+code[(ord(i)-ord('а'))])
    for i in range(0, len(s1), 100):
        print(s1[i:min(i+100,len(s1))])
    s2='текстэпиграфа'.lower()
    s3=''
    for i in s2:
        s3 += chr(ord('а')+code[(ord(i)-ord('а'))])
    print()
    print(s3)
#random_encode()
#find_good_sig()