/**  ========================================================================
    Copyright (c) 2014-2015 HeliTrak, Inc.  

    All rights reserved.  This file contains confidential information, Trade secrets and other proprietary
    information of HeliTrak.  Any use, Disclosure, reproduction, modification, performance, display or transfer of
    this file or any part of its contents is prohibited, except with the Express written authorization of HeliTrak.

    Rights in this program belong to:

        HeliTrak Inc.
        1620 26th Ave NW
        Gig Harbor, WA 98335

    Project   : HAP1
    Subsystem : Tools

    \File main.cpp

    Description:

        This file parses the PCI-, Magnetometer-, GPS-, Accelerometer-, Gyro, Euler Angles, and Inner-Loop
		data from MCP- and ADP Flight-Test telemetry binary input files and outputs the results to comma-delimited 
		ascii files. The frame number and the salient data items are output to facilitate plotting and 
		data reduction.

    Design Details and Explanations:

    Implementation Notes:

    Revision History:

    Version # (1,2, ... N):
    Changed By:
    Date:
    Reason/Description/PR#:
    ======================================================================== */
#include <iostream>
#include <cstring>

#include "Version.h"

#include "Parser.h"
#include "FileReader.h"

#define DEBUG (1)

#include "Telemetry_Log.h"
#include "Telemetry_Log_ADP.h"

static Parser_Alias * Create_MCP_Telemetry_Parser(const std::string & filename);
static Parser_Alias * Create_MCP_Telemetry_Parser(const std::string & filename);
static Parser_Alias * Create_ADP_Telemetry_Parser(const std::string & filename);
static Parser_Alias * Create_ADP_Telemetry_Parser(const std::string & filename);

// This project is used for parsing telemetry packets from a file. The file may contain different kinds of telemetry
// packets.
//
// To parse a file, first create a File_Reader object. The File_Reader object will open the file and look for valid packets.
//
// To parse individual packets, create a Parser, one for each kind of packet. These individual parsers can be added to
// the File_Reader by using the Add_Parser() method.
//
// Parsers need to be told how to parse! They are able to search through a packet, locate the variables in the packet, and
// save those variables in a CSV format. A variable (i.e. a new column in the CSV file) can be added to the parser by using
// the Set_Column function. This function specifies the column number, column header (found in the first row of the CSV file),
// the packet structure, the variable inside the packet structure, and the type of said variable. This function should be called
// for each variable/CSV column.
void main(int argc, char *argv[])
{
    // Make sure that the number of arguments is correct. The input parameters are in pairs, and the first parameter is always the
    // executable file location itself, so there should be an odd number of parameters that is greater than 3.

    if (argc == 2 && strcmp(argv[1], "-version") == 0)
    {
        std::cout << "FlightDataParser " << FLIGHT_DATA_PARSER_VERSION_NUMBER << std::endl;

        return;
    }
    else if (argc % 2 != 1 || argc < 3)
    {
        // Wrong number of arguments, so print out a usage message.
        std::cout << "Usage:" << std::endl;
        std::cout << "| " << std::endl;
        std::cout << "| " << "-version" << std::endl;
        std::cout << "| " << std::endl;
        std::cout << "| " << "Single File:" << std::endl;
        std::cout << "| " << "-- " << "FileTestParser <input_filename> <output_filename_without_extension>" << std::endl;
        std::cout << "| " << "-- " << "Example: FileTestParser Data_Input_File.csv Data_Output_File" << std::endl;
        std::cout << "| " << std::endl;
        std::cout << "| " << "Multiple Files:" << std::endl;
        std::cout << "| " << "-- " << "FileTestParser <input_filename_1> <output_filename_without_extension_1> <input_filename_2> <output_filename_without_extension_2> ..." << std::endl;
        std::cout << "| " << "-- " << "Example: FileTestParser Data_Input_File_1.csv Data_Output_File_1 Data_Input_File_2.csv Data_Output_File_2" << std::endl;

        return;
    }

    // For each file that was specified.
    for (S32 i = 1; i < argc; i += 2)
    {
        // Base file name prefix for all the files
        std::string base_file_name(argv[i + 1]);

        // Create a file reader for that file.
        File_Reader reader(argv[i]);

        // Create the file parsers for the MCP and ADP telemetry packets.
        Parser_Alias * mcp_parser = Create_MCP_Telemetry_Parser(base_file_name);
        Parser_Alias * adp_parser = Create_ADP_Telemetry_Parser(base_file_name);

        // Tell the file reader which packets these parsers will parse.
        reader.Add_Parser(TELEMETRY_MCP_STD_PKT_TAG, mcp_parser);
        reader.Add_Parser(TELEMETRY_ADP_STD_PKT_TAG, adp_parser);

        // Read the file to begin parsing.
        reader.Read();

        // All done!
        delete mcp_parser;
        delete adp_parser;
    }
}


