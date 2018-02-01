from collections import Counter
from bs4 import BeautifuSoup

n = raw_input()
read = raw_input()

n = int(n)
a = map(int, read.split())

d = Counter(a)
ans = 0

l = list(set(a))
l.sort()
length = len(l)

for i in xrange(length):
	x = l[i]
	k = d[x] % 3
	if k == 0:
		continue
	elif k == 1:
		if i == length - 1:
			ans += 2
		elif l[i+1] - l[i] > 20:
			ans += 2
		elif l[i+1] - l[i] > 10:
			ans += 1
			d[l[i+1]] -= 1
		elif l[i+1] - l[i] <= 10:
			if d[l[i+1]] >= 2:
				d[l[i+1]] -= 2
			else:
				d[l[i+1]] -= 1
				if i == length - 2:
					ans += 1
				elif l[i+2] - l[i+1] > 10:
					ans += 1
				else:
					d[l[i+2]] -= 1
	elif k == 2:
		if i == length - 1:
			ans += 1
		elif l[i+1] - l[i] > 10:
			ans += 1
		else:
			d[l[i+1]] -= 1

print ans
