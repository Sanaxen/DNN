# -*- coding: utf-8 -*-

import re

f = open('examples.utf', 'r',encoding="utf-8_sig")

f_j = open('tanaka_corpus_j.txt', 'w',encoding="utf-8_sig")
f_e = open('tanaka_corpus_e.txt', 'w',encoding="utf-8_sig")

cnt = 0
for row in f:
    if row.find('B:') != -1: continue
    s = row.replace('A: ', '')

    s = re.sub('#ID=.*?$', '', s)

    j, e = s.split('\t')

    j = j.strip()
    e = e.strip()
    print(j, file=f_j)
    print(e, file=f_e)

    #if cnt > 10: break
    cnt += 1
