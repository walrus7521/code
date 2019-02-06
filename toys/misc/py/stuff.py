#!/usr/bin/env python

import subprocess

all_threads = [1, 2, 4, 8, 16, 32, 64, 128]
all_runtimes = []
# Launch pipeline on each number of threads
for t in all_threads:
  cmd = './pipe --threads {}'.format(t) # note pipe is any executable
  # Use the subprocess module to fetch the return output
  p = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
  output = p.communicate()[0]  # wat
  print output
  all_runtimes.append(output)


