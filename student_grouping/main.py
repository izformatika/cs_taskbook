people_q = 20
teamsize = 4
people_id = list(range(people_q))
seen = [[0] * people_q for i in range(people_q)]

for i in range(people_q):
    seen[i][i] = people_q**2

def keyf(a):
    sum_a = 0
    for i in range(people_q):
        sum_a += seen[a][i]
    return sum_a

teams = [people_id[i * teamsize:min((i + 1) * teamsize, people_q)]
                         for i in range(people_q // teamsize)]

for team in teams:
    for person in team:
        for another in team:
            if another > person:
                seen[person][another] += 1
                seen[another][person] += 1
print(*teams)
for p in seen:
    print(*p)

cur_queue = sorted(people_id, key=keyf)
print(cur_queue)
print()
nteams = []

for cur_person in cur_queue:
    cur_team = [cur_person]
    min_seen = min(seen[cur_person])
    added = False
    while len(cur_team) < teamsize:
        for i in people_id:
            if seen[cur_person][i] == min_seen:
                if i not in cur_team:
                    cur_team.append(i)
                    added = True
                    break
        if not added:
            min_seen += 1
            added = False
    nteams.append(cur_team)
print(*nteams)
print('ok')