s="вдагм"
c=0
for i1 in s:
    for i2 in s:
        for i3 in s:
            for i4 in s:
                for i5 in s:
                    #for i6 in s:
                    s1=i1+i2+i3+i4+i5#+i6
                    if not (i1==i2 or i2==i3 or i3==i4 or i4==i5) and ("а" in s1 or "ю" in s1):
                        c+=1
print (c)
