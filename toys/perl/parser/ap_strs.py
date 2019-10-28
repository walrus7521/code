#!/usr/bin/env python3


MCP_PARSER_BEGIN = """
static Parser_Alias * Create_MCP_Telemetry_Parser(const std::string & filename)
{
    Parser<TELEMETRY_LOG_STRUCT> * parser = new Parser<TELEMETRY_LOG_STRUCT>(filename);
	int column = -1;

    parser->Duplicate_To_Combined_File(true);

    // Set the max number of lines per file. When this limit is reached, a new file is created.
    parser->Set_Lines_Per_File(25000);

    // Uncomment this to enable a combined file which has all data (in addition to the files that are split apart
    // based on the number of lines).
    // parser->Duplicate_To_Combined_File(true);

    // Set up the format for the output CSV file. These are the order of the arguments and what they do:
    //
    // First arg: The column number in the CSV file. Column numbers start at zero (first column is 0, second column is 1, etc.)
    // Second arg: The header for the column that will be printed out in the first row of the CSV file
    // Third arg: The structure that was saved via CANDEMUX. This will usually be a telemetry structure or something similar.
    // Fourth arg: The variable inside the structure (from the third arg) that will be saved in this column.
    // Fifth arg: The type of the variable (the fourth arg) -- F32, U32, BOOLEAN, etc.
"""

MCP_PARSER_END = """
    return parser;
}
"""

ADP_PARSER_BEGIN = """
static Parser_Alias * Create_ADP_Telemetry_Parser(const std::string & filename)
{    
    Parser<TELEMETRY_LOG_STRUCT_ADP> * parser = new Parser<TELEMETRY_LOG_STRUCT_ADP>(filename);
	int column = -1;

    parser->Duplicate_To_Combined_File(true);

    parser->Set_Lines_Per_File(25000);

"""

ADP_PARSER_END = """
    return parser;
}
"""

ATTIND_PARSER_BEGIN = """
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;

namespace IndicatorCommon
{

    public partial class MCPSerialPortListener
    {
        public struct ParsedData
        {
            public int datatype;
            public UInt32 frame;
            public double phi;
            public double theta;
            public double psi;
            public double accel_z;
            public double ias;
            public double tas;
            public double alt;
            public int str_idx;
            public string name;
            public int saturation;
            public int crc;
        }

        private void ParserReportData(ref ParsedData data, byte[] destfoo)
        {
            int offset = 0;
"""

ATTIND_PARSER_END = """
            data.frame   = framenumber;
            data.phi     = eulers_phi;
            data.theta   = eulers_theta;
            data.psi     = eulers_psi;
            data.accel_z = 0.0; // accels_z;
            data.ias     = IAS;
            data.tas     = 0.0; // tas;
            data.alt     = baro_altitude;

        }
    }
}

"""

CCC_CODE_START = """
#include <stdio.h>

void dump_coeffs(MCP_COEFF_STRUCT *coeff);

int main()
{
    char buffer[8000];

    dump_coeffs((MCP_COEFF_STRUCT *) buffer);
{

void dump_coeffs(MCP_COEFF_STRUCT *coeff)
{
"""

CCC_CODE_END = """
}    
"""

FLAGSDISP_DEFS_MCP_PARSER_BEGIN = """
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;

namespace FlagsDisplay
{
    partial class Form1
    {"""

FLAGSDISP_DEFS_MCP_PARSER_END = """
    } // partial class Form1

} // namespace FlagsDisplay

"""

FLAGSDISP_ARRAY_MCP_PARSER_BEGIN = """
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;

namespace FlagsDisplay
{

    public partial class Form1
    {
        private void InitializeCheckboxenArray()
        {"""

FLAGSDISP_ARRAY_MCP_PARSER_END = """
        } // InitializeCheckboxenArray()

    } // partial class Form1

} // FlagsDisplay()

"""

FLAGSDISP_INIT_MCP_PARSER_BEGIN = """
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;

namespace FlagsDisplay
{

    public partial class Form1
    {
        private void InitializeCheckboxen()
        {"""

FLAGSDISP_INIT_MCP_PARSER_END = """
        } // InitializeCheckboxen()

    } // partial class Form1

} // FlagsDisplay()

"""

FLAGSDISP_DATA_MCP_PARSER_BEGIN = """
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;

namespace IndicatorCommon
{

    public partial class MCPSerialPortListener
    {
        public class ParsedData
        {
            public int datatype;
            public UInt32 framenumber;
            public bool[] sys_flags;
            public bool[] claw_flags;
            public int crc;
            public ParsedData()
            {
                sys_flags = new bool[32];
                claw_flags = new bool[32];
            }
        }

        private void ParserReportData(ref ParsedData data, byte[] destfoo)
        {
"""

FLAGSDISP_DEFS_ADP_PARSER_BEGIN = """
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;

namespace FlagsDisplay
{
    partial class Form1
    {"""

FLAGSDISP_DEFS_ADP_PARSER_END = """
    } // partial class Form1

} // namespace FlagsDisplay

"""

FLAGSDISP_ARRAY_ADP_PARSER_BEGIN = """
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;

namespace FlagsDisplay
{

    public partial class Form1
    {
        private void InitializeCheckboxenArrayADP()
        {"""

FLAGSDISP_ARRAY_ADP_PARSER_END = """
        } // InitializeCheckboxenArrayADP()

    } // partial class Form1

} // FlagsDisplay()

"""

FLAGSDISP_INIT_ADP_PARSER_BEGIN = """
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;

namespace FlagsDisplay
{

    public partial class Form1
    {
        private void InitializeCheckboxenADP()
        {"""

FLAGSDISP_INIT_ADP_PARSER_END = """
        } // InitializeCheckboxenADP()

    } // partial class Form1

} // FlagsDisplay()

"""

FLAGSDISP_DATA_ADP_PARSER_BEGIN = """
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;

namespace IndicatorCommon
{

    public partial class ADPSerialPortListener
    {
        public class ParsedData
        {
            public int datatype;
            public UInt32 framenumber;
            public bool[] flags;
            public int crc;
            public ParsedData()
            {
                flags = new bool[32];
            }
        }

        private void ParserReportData(ref ParsedData data, byte[] destfoo)
        {
"""

FLAGSDISP_DATA_PARSER_END = """

        }
    }
}

"""

