#!/usr/bin/env python3

#from time import sleep

# https://psutil.readthedocs.io/en/latest/

import psutil
#from psutil import cpu_percent, net_io_counters

#import smtplib
import string


c = psutil.net_io_counters()
#print(c)
p = psutil.cpu_percent()
print(p)
n = psutil.cpu_count()
print(n)
print("cpu freq: ", psutil.cpu_freq())
print("partitions: ", psutil.disk_partitions())

TO = "bartb@gmail.com"
FROM = "bartb@gmail.com"
SUBJECT = "your domain is out of memory!"
text = "go fix your server!"
#BODY = ("From: %s" %FROM,"To: %s" %TO,"Subject: %s" %SUBJECT, "",text)], ["\r\n"]) 
#server = smtplib.SMTP('127.0.0.1') 
#server.sendmail(FROM, [TO], BODY)
#server.quit()

