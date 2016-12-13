# Read domino csv file and show the top 100 passwords used with their counter
import csv
import md5
import os

pwrds = dict()
with open('domino', "r") as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',')
	spamreader.next()
	for line in spamreader:
		pw = line[6]
		if pw not in pwrds:
			pwrds[pw] = 1
		else:
			pwrds[pw] += 1

top = sorted(pwrds.keys(), key=pwrds.__getitem__, reverse=True)[:100]
#for p in top:
#	print p, pwrds[p]

# get words from the dictionary
f = open('french.txt', 'r')
words = f.readlines()
f.close()

# add manually used passwords
words.append("123456")
words.append("1234")
words.append("password")
words.append("PASSWORD")
words.append("motdepass")

# hash the words from the dictionary and add to a dictionary
t1,_,_,_,_ = os.times()
hash_dict = dict()
for word in words:
	hash_dict[md5.new(word).hexdigest()] = word;
t2,_,_,_,_ = os.times()

# print the hashed with the passwords that are in domino db
for hs in (set(hash_dict.keys()) & set(top)):
	print hs, hash_dict[hs]

# print computing time
print "------------------------------------------------"
print (t2-t1), "s to compute ", len(words), " hashes."
print (t2-t1)/len(words), "s for hashing 1 word in average."

