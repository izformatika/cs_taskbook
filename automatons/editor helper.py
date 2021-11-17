def f(s):
    while '01' in s or '04' in s or '09' in s:
        s = s.replace('01', '109')
        s=s.replace('04', '1901')
        s = s.replace('09', '4110')
        print(s)
    return s
mode = 1
if mode == 0:
    one = f('01')
    four = f('04')
    nine = f('09')
    onesum = sum(map(int, list(one)))
    foursum = sum(map(int, list(four)))
    ninesum = sum(map(int, list(nine)))
    print(onesum,foursum,ninesum)
    maxsum = 10*onesum+10*foursum+10*ninesum
    print(maxsum)
else:
    lst = [[] for i in range(300)]
    for i in range(10):
        for j in range(10):
            for k in range(10):
                lst[7*i+17*j+6*k].append([i,j,k])
    for i in range(300):
        if len(lst[i])<2:
            continue
        j = 0
        while j != len(lst[i]):
            if lst[i][j].count(0)>1:
                del lst[i][j]
            else:
                j+=1
        lst[i].sort(key=lambda a:a[0]+a[1]+a[2])
        if len(lst[i])>1 and sum(lst[i][1])-sum(lst[i][0])<3:
            print(i, lst[i])

    