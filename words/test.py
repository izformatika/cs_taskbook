from collections import Counter
s="объятие"
c=0
for i1 in s:
    print(i1)
    for i2 in s.replace(i1, ''):
        for i3 in s.replace(i1, '').replace(i2, ''):
            for i4 in s.replace(i1, '').replace(i2, '').replace(i3, ''):
                for i5 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, ''):
                    for i6 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, ''):
                        for i7 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, ''):
                            '''for i8 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, ''):
                                for i9 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, '').replace(i8, ''):
                                    for i10 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, '').replace(i8, '').replace(i9, ''):
                                        for i11 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, '').replace(i8, '').replace(i9, '').replace(i10, ''):
                                            for i12 in s.replace(i1, '').replace(i2, '').replace(i3, '').replace(i4, '').replace(i5, '').replace(i6, '').replace(i7, '').replace(i8, '').replace(i9, '').replace(i10, '').replace(i11, ''):
                                            '''
                        s1=i1+i2+i3+i4+i5+i6+i7#+i8+i9+i10+i11+i12
                                                #signature=list(Counter(s1).values())
                                                #if len(signature) == len(s1) - 1 and
                        if ("оъ" in s1 or "яъ" in s1 or "иъ" in s1 or "еъ" in s1):
                            c+=1
print (c)
