# -*- coding: utf-8 -*-

import random


f_j = open('tanaka_corpus_j.txt', 'r',encoding="utf-8_sig")
f_e = open('tanaka_corpus_e.txt', 'r',encoding="utf-8_sig")

js = []
es = []
for row in f_j: js.append(row)
for row in f_e: es.append(row)

size_j = len(js)
size_e = len(es)

index = random.sample(range(size_e), 10000)

f_j_w = open('tanaka_corpus_j_10000.txt', 'w',encoding="utf-8_sig")
f_e_w = open('tanaka_corpus_e_10000.txt', 'w',encoding="utf-8_sig")

for i in index:
    hj = js[i]
    he = es[i]
    hj = hj.strip()
    he = he.strip()
    print(hj, file=f_j_w)
    print(he, file=f_e_w)
