#!/usr/bin/env python3

import subprocess

def main():
    print("hello, world")

    with subprocess.Popen(["anal.cmd"], shell=True, stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.PIPE) as p:
        std_out, errors = p.communicate() #(str.encode("utf-8"))
        if std_out:
            out = std_out.splitlines()
            for ln in out:
                if len(ln):
                    print(ln)
        if errors:
            print("Error message: {}".format(error))

main()

