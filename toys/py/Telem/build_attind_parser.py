#!/usr/bin/env python3

import re
import sys
import ap_strs

re_bool_type= "BOOLEAN_Type :(\d+)"
period = "\."

print(ap_strs.ATTIND_PARSER_BEGIN)

offset = 0

try:
    for line in sys.stdin:
        if line:
            line = line.rstrip()
            pair = line.split(',', 3)
            name = pair[0];
            type = pair[1];
            offset = pair[2];
            boolval = re.search(re_bool_type, line)
            if (boolval):
                shift = boolval.group(1)
                full_names = name.split('.')
            else:
                full_names = name.split('.')
                #print("splits: {0} => {1}".format(len(full_names), full_names[-1]))
                str = ""
                num_strs = len(full_names)
                fstr = ""
                if (num_strs > 1):
                    for i in range(num_strs-1):
                        str += full_names[i]
                    fstr = "{0}_{1}".format(str, full_names[-1])
                else:
                    fstr = name
                if ("F32_Type" in type):
                    print("            float {0} = BitConverter.ToSingle(destfoo, {1});".format(fstr, offset))
                elif ("U32_Type" in type):
                    print("            UInt32 {0} = BitConverter.ToUInt32(destfoo, {1});".format(fstr, offset))
                elif ("S16_Type" in type):
                    print("            Int16 {0} = BitConverter.ToInt16(destfoo, {1});".format(fstr, offset))
                elif ("U8_Type" in type):
                    print("            Char {0} = BitConverter.ToChar(destfoo, {1});".format(fstr, offset))


except Exception:
    pass
    #print("error in data")
finally:
    pass

print(ap_strs.ATTIND_PARSER_END)


