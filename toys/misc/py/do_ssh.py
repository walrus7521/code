#!/usr/bin/env python3

# pip3 install fabric 

import base64
import paramiko

client = paramiko.SSHClient()

client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
client.connect('127.0.0.1', username='thedude', password='wusup')
stdin, stdout, stderr = client.exec_command('ls /dev')
for line in stdout:
    print('... ' + line.strip('\n'))
client.close()

