#!/bin/python
import sys

def un_camel(x):
    final = ''
    count = 0
    for item in x:
        if item.isupper():
            final += "_"+item.lower()
            count += 1
        else:
            final += item
    if final[0] == "_":
        final = final[1:]
    print count+1
    return final


def count_camels(x):
    count = 0
    for item in x:
        if item.isupper():
            count += 1
    print count+1

def to_camel_case(snake_str):
    components = snake_str.split('_')
    # We capitalize the first letter of each component except the first one
    # with the 'title' method and join them together.
    return components[0] + "".join(x.title() for x in components[1:])



s = raw_input().strip()
#print s
count_camels(s)

#print to_camel_case('snake_case')
#count_camels('whatsUpDudeManBearPig')
#s = "Java";
#s.length(); // len = 4
#char c0 = s.charAt(0); // c0 = 'J'
#char c2 = s.charAt(2); // c2 = 'v'
#print s[0],s[1]
