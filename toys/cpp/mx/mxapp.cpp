#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>

using namespace std;

enum class USER_OPTION_TASK
{
    Quit_MX_App = 1,
    Write_Config_File,
    Read_Config_File,
    Verify_Config_File,
    Start_Standard_Telemetry,
    Start_Raw_Telemetry,
    Stop_Telemetry,
    Read_System_State,
    Read_Event_Log,
    Clear_System_State,
    Clear_Event_Log,
    Display_Version_Number,
    Run_Alarm_POST,
    Run_Magnetometer_POST,
    Run_Miscellaneous_POST,
    Run_Actuator_Test,
    Run_ADP_POST,
    Run_Hall_POST,
    Read_Main_Board_Serial_Number,
    Write_Main_Board_Serial_Number,
    Read_Mag_Config_File,
    Write_Mag_Config_File,
    Verify_Mag_Config_File,
    Do_Installation_Calibration
};

map<string, USER_OPTION_TASK> usr_opts = {
    {"Quit_MX_App",                     USER_OPTION_TASK::Quit_MX_App},
    {"Write_Config_File",               USER_OPTION_TASK::Write_Config_File},
    {"Read_Config_File",                USER_OPTION_TASK::Read_Config_File},
    {"Verify_Config_File",              USER_OPTION_TASK::Verify_Config_File},
    {"Start_Standard_Telemetry",        USER_OPTION_TASK::Start_Standard_Telemetry},
    {"Start_Raw_Telemetry",             USER_OPTION_TASK::Start_Raw_Telemetry},
    {"Stop_Telemetry",                  USER_OPTION_TASK::Stop_Telemetry},
    {"Read_System_State",               USER_OPTION_TASK::Read_System_State},
    {"Read_Event_Log",                  USER_OPTION_TASK::Read_Event_Log},
    {"Clear_System_State",              USER_OPTION_TASK::Clear_System_State},
    {"Clear_Event_Log",                 USER_OPTION_TASK::Clear_Event_Log},
    {"Display_Version_Number",          USER_OPTION_TASK::Display_Version_Number},
    {"Run_Alarm_POST",                  USER_OPTION_TASK::Run_Alarm_POST},
    {"Run_Magnetometer_POST",           USER_OPTION_TASK::Run_Magnetometer_POST},
    {"Run_Miscellaneous_POST",          USER_OPTION_TASK::Run_Miscellaneous_POST},
    {"Run_Actuator_Test",               USER_OPTION_TASK::Run_Actuator_Test},
    {"Run_ADP_POST",                    USER_OPTION_TASK::Run_ADP_POST},
    {"Run_Hall_POST",                   USER_OPTION_TASK::Run_Hall_POST},
    {"Read_Main_Board_Serial_Number",   USER_OPTION_TASK::Read_Main_Board_Serial_Number},
    {"Write_Main_Board_Serial_Number",  USER_OPTION_TASK::Write_Main_Board_Serial_Number},
    {"Read_Mag_Config_File",            USER_OPTION_TASK::Read_Mag_Config_File},
    {"Write_Mag_Config_File",           USER_OPTION_TASK::Write_Mag_Config_File},
    {"Verify_Mag_Config_File",          USER_OPTION_TASK::Verify_Mag_Config_File},
    {"Do_Installation_Calibration",     USER_OPTION_TASK::Do_Installation_Calibration},
};


enum class USER_OPTION_PROCESSOR
{
    MCPA = 1,
    MCPB,
    MCPC,
    ADP
};

map<string, USER_OPTION_PROCESSOR> cpu_opts = {
    {"MCPA", USER_OPTION_PROCESSOR::MCPA},
    {"MCPB", USER_OPTION_PROCESSOR::MCPB},
    {"MCPC", USER_OPTION_PROCESSOR::MCPC},
    {"ADP",  USER_OPTION_PROCESSOR::ADP},
};

enum class CONFIG_FILE_SEGMENT_TYPE
{
    All = 1,
    Binary,
    Manufacturing,
    Installation,
    Coefficients
};

map<string, CONFIG_FILE_SEGMENT_TYPE> seg_opts = {
    {"All",           CONFIG_FILE_SEGMENT_TYPE::All},
    {"Binary",        CONFIG_FILE_SEGMENT_TYPE::Binary},
    {"Manufacturing", CONFIG_FILE_SEGMENT_TYPE::Manufacturing},
    {"Installation",  CONFIG_FILE_SEGMENT_TYPE::Installation},
    {"Coefficients",  CONFIG_FILE_SEGMENT_TYPE::Coefficients},
};



void File_Selection(std::string & filename)
{
    std::cout << "Please enter a file name:" << std::endl;
    std::cin >> filename;
}


void Serial_Number(std::string & serialnumber)
{
    std::cout << "Please enter the serial number:" << std::endl;
    std::cin >> serialnumber;
}


void Config_File_Segment_Selection(CONFIG_FILE_SEGMENT_TYPE & segmentType)
{
    std::cout << "Which segment(s)? " << std::endl;;
    std::cout << (uint32_t)CONFIG_FILE_SEGMENT_TYPE::All           << ". All" << std::endl;
    std::cout << (uint32_t)CONFIG_FILE_SEGMENT_TYPE::Binary        << ". Binary" << std::endl;
    std::cout << (uint32_t)CONFIG_FILE_SEGMENT_TYPE::Manufacturing << ". Manufacturing" << std::endl;
    std::cout << (uint32_t)CONFIG_FILE_SEGMENT_TYPE::Installation  << ". Installation" << std::endl;
    std::cout << (uint32_t)CONFIG_FILE_SEGMENT_TYPE::Coefficients  << ". Coefficients" << std::endl;

    uint32_t temp;
    std::cin >> temp;
    segmentType = (CONFIG_FILE_SEGMENT_TYPE)temp;
}

#if 0
bool Process_User_Option(USER_OPTION_TASK & user_option,
                         USER_OPTION_PROCESSOR & processor_option,
                         std::string & file_option,
                         std::string & serial_number,
                         bool & collectTelemetryForAllProcessors,
                         CONFIG_FILE_SEGMENT_TYPE & segmentType)
{
    return false;
}
#endif

bool Parse_Options(vector<string> options,
                         USER_OPTION_TASK & user_option,
                         USER_OPTION_PROCESSOR & processor_option,
                         std::string & file_option,
                         std::string & serial_number,
                         bool & collectTelemetryForAllProcessors,
                         CONFIG_FILE_SEGMENT_TYPE & segmentType)
{
    bool return_val = true; // flag indicating validity of the user input

    // initialize all parameters to defaults
    user_option = (USER_OPTION_TASK) 0;
    processor_option = (USER_OPTION_PROCESSOR) 0;
    file_option = "";
    serial_number = "";
    collectTelemetryForAllProcessors = false;
    segmentType = (CONFIG_FILE_SEGMENT_TYPE) 0;


    user_option = usr_opts[options[0]];
    processor_option = cpu_opts[options[1]];

    // The switch statement checks the validity of the processor choice, so the valid cases flow through 
    // the next caes until there is a break. 
    switch (processor_option)
    {
    case USER_OPTION_PROCESSOR::MCPA:
    case USER_OPTION_PROCESSOR::MCPB:
    case USER_OPTION_PROCESSOR::MCPC:
    case USER_OPTION_PROCESSOR::ADP:
        break;

    default:
        {
            // invalid processor
            std::cout << "Invalid Processor" << std::endl;
            //std::cin.clear();
            //std::cin.ignore(1000, '\n');
            return_val = false;
        }
        break;

    } // switch 

    if(return_val)
    {
        std::string yes_no_str;

        // The switch statement asks for additional inputs according to command types.
        // Depending on types of commands that require same set of inputs, the cases are designed
        // to flow through. 
        switch(user_option)
        {
        case USER_OPTION_TASK::Write_Config_File:
        case USER_OPTION_TASK::Read_Config_File:
            file_option = options[2];
            segmentType = seg_opts[options[3]];
            break;

        case USER_OPTION_TASK::Read_Event_Log:
        case USER_OPTION_TASK::Read_System_State:
            //File_Selection(file_option);
            file_option = options[2];
            break;

        case USER_OPTION_TASK::Start_Standard_Telemetry:
            if (options[2] == "ALL" )
            {
                collectTelemetryForAllProcessors = true;
            }
            break;
        case USER_OPTION_TASK::Start_Raw_Telemetry:
            if (options[2] == "ALL" )
            {
                collectTelemetryForAllProcessors = true;
            }
            break;
        case USER_OPTION_TASK::Stop_Telemetry:
            if (options[2] == "ALL" )
            {
                collectTelemetryForAllProcessors = true;
            }
            break;

        case USER_OPTION_TASK::Verify_Config_File:
        case USER_OPTION_TASK::Clear_Event_Log:
        case USER_OPTION_TASK::Clear_System_State:
        case USER_OPTION_TASK::Run_Alarm_POST:
        case USER_OPTION_TASK::Run_Magnetometer_POST:
        case USER_OPTION_TASK::Run_Miscellaneous_POST:
        case USER_OPTION_TASK::Run_Actuator_Test:
        case USER_OPTION_TASK::Run_ADP_POST:
        case USER_OPTION_TASK::Run_Hall_POST:
        case USER_OPTION_TASK::Display_Version_Number:
        case USER_OPTION_TASK::Quit_MX_App:
        case USER_OPTION_TASK::Read_Main_Board_Serial_Number:
        case USER_OPTION_TASK::Verify_Mag_Config_File:
        case USER_OPTION_TASK::Do_Installation_Calibration:
            break;
        case USER_OPTION_TASK::Write_Main_Board_Serial_Number:
            serial_number = options[2];
            break;
        case USER_OPTION_TASK::Write_Mag_Config_File:
        case USER_OPTION_TASK::Read_Mag_Config_File:
            file_option = options[2];
            break;
        default:
            printf("Incorrect option number.\n");
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            return_val = false;
            break;

        } // switch 

    } // if return_val true
    else
    {
        // do nothing
    }

    return return_val;

} // MXUserInterface::Process_User_Option()

vector<string> split(const string& s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;
    while (i != s.size()) {
        while (i != s.size() && isspace(s[i]))
            ++i;
        string_size j = i;
        while (j != s.size() && !isspace(s[j]))
            ++j;
        if (i != j) {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

void xref(istream& in,
            vector<string> find_words(const string&) = split)
{
    string line;
    int line_number = 0;

    while (getline(in, line)) {
        ++line_number;

        vector<string> options = find_words(line);
        if (options.size() > 0) 
        {
            USER_OPTION_TASK user_option;
            USER_OPTION_PROCESSOR processor_option;
            std::string file_option;
            std::string serial_number;
            bool collectTelemetryForAllProcessors;
            CONFIG_FILE_SEGMENT_TYPE segmentType;

            Parse_Options(options,
                          user_option,
                          processor_option,
                          file_option,
                          serial_number,
                          collectTelemetryForAllProcessors,
                          segmentType);

            cout << "user_option: " << (int) user_option << endl;
            cout << "proc_option: " << (int) processor_option << endl;
            cout << "file_option: " << file_option << endl;
            cout << "serial_num : " << serial_number << endl;
            cout << "collect all: " << collectTelemetryForAllProcessors << endl;
            cout << "segment_typ: " << (int) segmentType << endl;
            cout << endl;

        //if (words.size() > 0) {
        //    mx_ops[words[0]](words);
        //}
        }

    }
}

extern "C" {

    int xrefpy(char *line);
    //Foo* Foo_new(){ return new Foo(); }
    //void Foo_bar(Foo* foo){ foo->bar(); }

};

int xrefpy(char *line)
{
    string s(line);
    vector<string> options = split(s);

    if (options.size() > 0) {

        USER_OPTION_TASK user_option;
        USER_OPTION_PROCESSOR processor_option;
        std::string file_option;
        std::string serial_number;
        bool collectTelemetryForAllProcessors;
        CONFIG_FILE_SEGMENT_TYPE segmentType;

        Parse_Options(options,
                      user_option,
                      processor_option,
                      file_option,
                      serial_number,
                      collectTelemetryForAllProcessors,
                      segmentType);

        cout << "user_option: " << (int) user_option << endl;
        cout << "proc_option: " << (int) processor_option << endl;
        cout << "file_option: " << file_option << endl;
        cout << "serial_num : " << serial_number << endl;
        cout << "collect all: " << collectTelemetryForAllProcessors << endl;
        cout << "segment_typ: " << (int) segmentType << endl;
        cout << endl;

        //for (auto &l : options) {
        //    cout << l << " ";
        //}
        //cout << endl;
    }

    //cout << "xrefpy: " << line << endl;
    return 0;
}

//int main()
//{
//    ifstream myfile;
//    myfile.open ("test.mx");
//    xref(myfile);
//    myfile.close();
//}
