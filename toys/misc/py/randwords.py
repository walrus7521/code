#!/usr/bin/python

# include hacker handles
# mangle letters E => 3, etc...

import random
import time

rapper  = True
hacker  = False
band    = False
company = False
baby    = False

PREFIX  = ["slik","kool","zap","lj","yo","sup","homi"]
POSTFIX = ["rapper","dude","gangsta","dawg"]
VOWELS = ["a", "e", "i", "o", "u"]
CONSONANTS = [chr(i+97) for i in range(26)] + ["", ""]
# those last two spaces are in the consonants list so that
# the program can generate words with consecutive vowels

def rand_postfix():
    postfix = random.choice(POSTFIX)
    return postfix

def rand_prefix():
    prefix = random.choice(PREFIX)
    return prefix

def rand_vowel():
    letter = random.choice(VOWELS)
    return letter

def rand_consanant():
    consonant = random.choice(CONSONANTS)
    return consonant

def decorate(word):
    deco = []
    for c in word:
        if c == 'e':
            deco += '3'
        elif c == 'a':
            deco += '7'
        else:
            deco += c
    deco = "".join(str(x) for x in deco)
    return deco

def rand_word():
    word = []
    rand_range = 2 #random.randint(3,4)
    #print "rand: {0}".format(rand_range)
    prefix = rand_prefix()
    postfix = rand_postfix()
    for i in range(rand_range):
        letter = rand_consanant()
        word += letter
        letter = rand_vowel()
        word += letter
    #to convert the list to string
    if hacker:
        word = decorate(word)
    word = prefix+" "+"".join(str(x) for x in word)+" "+postfix
    return word #returns a random word

while True:
    print("word: {0}").format(rand_word())
    #print(rand_word())
    time.sleep(1)

