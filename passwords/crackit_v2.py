# -*- coding: utf-8 -*-
# Read domino csv file and show the top 100 passwords used with their counter
import csv
import md5
import os
import sys
import hashlib

import argparse

# function to get the hashed passwords
def get_dominos_data(filename):
	# get all the passwords from the CSV
	domino_pwrds = dict()
	# open the file
	with open(filename, "r") as csvfile:
		spamreader = csv.reader(csvfile, delimiter=',')
		spamreader.next()
		for line in spamreader:
			# the passwords are at position 7 ( that is 6 )
			pw = line[6]
			# if the hashed pass is not in the dict already, add it
			if pw not in domino_pwrds:
				domino_pwrds[pw] = 1
				# else icrement the counter
			else:
				domino_pwrds[pw] += 1	
	return domino_pwrds

# get a word list from a file
# must be a file with one word per line
def get_word_list(filename):
	# open file
	file_wlist = open(filename, 'r')
	# use read and splitlines to avoid the \r\n
	words = file_wlist.read().splitlines() 
	# close file
	file_wlist.close()
	return words

def get_word_from_file_descriptor(file_wlist):
	# use read and splitlines to avoid the \r\n
	words = file_wlist.read().splitlines() 
	# close file
	file_wlist.close()
	return words

def write_to_file(filename, user_and_decoded_pass):
	# open file
	target = open(filename, 'w')
	# 
	for tup in user_and_decoded_pass:
		target.write(str(tup))
		target.write('\n')


# def concat_word_lists(word_lists):

# __main__
# default filename 
parser = argparse.ArgumentParser()
parser.add_argument('flist', type=argparse.FileType('r'), nargs='+', help='dictionaries for decoding - one word per line files')
args = parser.parse_args()

# print(type(man_words))
all_fr_words = set()
for f in args.flist:
	all_fr_words = all_fr_words.union(set(get_word_from_file_descriptor(f)))
filename = "domino.csv"

# save the passwords in a dictionary {hasshedpass, nb_of_times_password_appears)
domino_pwrds = get_dominos_data(filename)

print ("Passwords in the domino file: " + str(len(domino_pwrds.keys())) )

# print(len(all_fr_words))
most_used = get_word_list("dictionaries/most_used_passwords.txt")
# do hash for the most common passwds as well
set_most_used = set()
for word in most_used:
	set_most_used.add( md5.new(word).hexdigest() )

# sort them so we have a nice list with the most used passwords on top
top = set(sorted(domino_pwrds.keys(), key=domino_pwrds.__getitem__, reverse=True)[:100])

# union the two
top = top.union(set_most_used)
# print the nb of most used pass
print("The number of most used passwords that we decided on is: " + str(len(top)))
# hash the words from the dictionary and add to a dictionary
hash_dict = dict()
# hash them all
for word in all_fr_words:
	hash_dict[md5.new(word).hexdigest()] = word;

# list of passwwords
list_of_pass = list()
# a sub list containing the most interesting
top_pass = list()
# make a set of the decoded passwords -> meaning we take only the ones we decode
set_of_decoded_paswd = (set(hash_dict.keys()) & set(domino_pwrds.keys()))
# print the hashed with the passwords that are in domino db
count = 0
for hs in set_of_decoded_paswd:
	if hs in top:
		top_pass.append( (hs, hash_dict[hs]) )
 	list_of_pass.append( (hs, hash_dict[hs]) )
 	count += 1

print("We cracked " + str(count) + " passwords !")
# write them to the file and wait for the beers!!!!
write_to_file("passwords.txt", list_of_pass)
write_to_file("top_"+ str(len(top)) + "_pass.txt", top_pass)
