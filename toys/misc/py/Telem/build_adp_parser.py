#!/usr/bin/env python3

import re
import sys
import ap_strs

re_bool_type= "BOOLEAN_Type :(\d+)"
re_flag_type= "flag"
period = "\."

print(ap_strs.ADP_PARSER_BEGIN)

try:
    for line in sys.stdin:
        if line:
            line = line.rstrip()
            pair = line.split(',', 2)
            name = pair[0];
            type = pair[1];
            boolval = re.search(re_bool_type, line)
            flagval = re.search(re_flag_type, line)
            if (flagval):
                shift = boolval.group(1)
                full_names = name.split('.')
                print("    parser->Set_Column_Masked(++column, \"{0}\", TELEMETRY_LOG_STRUCT_ADP, {1}.{2}, BOOLEAN_Type, (1 << {3}));".format(full_names[2], full_names[0], full_names[1], shift))
            elif (boolval):
                shift = boolval.group(1)
                full_names = name.split('.')
                print("    parser->Set_Column_Masked(++column, \"{0}\", TELEMETRY_LOG_STRUCT_ADP, {1}.{2}, BOOLEAN_Type, (1 << {3}));".format(full_names[2], full_names[0], full_names[1], shift))
            else:
                print("    parser->Set_Column(++column, \"{0}\", TELEMETRY_LOG_STRUCT_ADP, {1}, {2});".format(name, name, type))
                pass

except Exception:
    print("error in data")
finally:
    pass

print(ap_strs.ADP_PARSER_END)


