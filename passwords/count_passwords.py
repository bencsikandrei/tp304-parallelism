# Read domino csv file and show the top 100 passwords used with their counter
import csv

flag = True
pwrds = dict()
with open('domino', "r") as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',')
	for line in spamreader:
		# Ignore the header
		if flag:
			flag = False
			continue
		pw = line[6]
		if pw not in pwrds:
			pwrds[pw] = 1
		else:
			pwrds[pw] += 1
# remove <blank> ones
del pwrds["<blank>"]
# 
top = sorted(pwrds.keys(), key=pwrds.__getitem__, reverse=True)[:100]
for p in top:
	print p #to get the counts pwrds[p]
