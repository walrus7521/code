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

enum class USER_OPTION_PROCESSOR
{
    MCPA = 1,
    MCPB,
    MCPC,
    ADP
};

enum class CONFIG_FILE_SEGMENT_TYPE
{
    All = 1,
    Binary,
    Manufacturing,
    Installation,
    Coefficients
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

bool Process_User_Option(USER_OPTION_TASK & user_option,
                         USER_OPTION_PROCESSOR & processor_option,
                         std::string & file_option,
                         std::string & serial_number,
                         bool & collectTelemetryForAllProcessors,
                         CONFIG_FILE_SEGMENT_TYPE & segmentType)
{
    return false;
}

bool Process_User_Option(istream& in,
                         USER_OPTION_TASK & user_option,
                         USER_OPTION_PROCESSOR & processor_option,
                         std::string & file_option,
                         std::string & serial_number,
                         bool & collectTelemetryForAllProcessors,
                         CONFIG_FILE_SEGMENT_TYPE & segmentType)
{
    bool return_val = true; // flag indicating validity of the user input
    uint32_t processor_option_temp = 0;
    std::cout << "please enter a processor ID (1-> MCPA; 2-> MCPB; 3-> MCPC; 4-> ADP)" << std::endl;
    std::cin >> processor_option_temp;
    processor_option = (USER_OPTION_PROCESSOR)processor_option_temp;
    collectTelemetryForAllProcessors = false;

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
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            return_val = false;
        }
        break;

    } // switch 

    if(return_val)
    {
        std::cout << "MAINTENANCE MODE options: " << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Quit_MX_App              << ". Quit Maintenance App" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Write_Config_File        << ". Write config file" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Read_Config_File         << ". Read config file" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Verify_Config_File       << ". Verify config file" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Start_Standard_Telemetry << ". Collect standard telemetry data" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Start_Raw_Telemetry      << ". Collect raw telemetry data" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Stop_Telemetry           << ". Stop collecting telemetry data" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Read_System_State        << ". Read System state data" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Read_Event_Log           << ". Read Event log data" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Clear_System_State       << ". Clear system state data" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Clear_Event_Log          << ". Clear event log data" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Display_Version_Number   << ". Display software version number" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Run_Alarm_POST           << ". Run Alarm POST" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Run_Magnetometer_POST    << ". Run Magnetometer POST" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Run_Miscellaneous_POST   << ". Run Miscellaneous POST" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Run_Actuator_Test        << ". Run Actuator Test" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Run_ADP_POST             << ". Run ADP POST" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Run_Hall_POST            << ". Run Hall POST" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Read_Main_Board_Serial_Number  << ". Read Main Board Serial Number" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Write_Main_Board_Serial_Number << ". Write Main Board Serial Number" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Read_Mag_Config_File     << ". Read Magnetometer config file" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Write_Mag_Config_File    << ". Write Magnetometer config file" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Verify_Mag_Config_File   << ". Verify Magnetometer config file" << std::endl;
        std::cout << (uint32_t)USER_OPTION_TASK::Do_Installation_Calibration << ". Do installation calibration" << std::endl;

        std::cout << "Please enter a valid option:" << std::endl;
        
        uint32_t user_option_temp = 0;
        std::cin >> user_option_temp;
        user_option = (USER_OPTION_TASK)user_option_temp;

        std::string yes_no_str;

        // The switch statement asks for additional inputs according to command types.
        // Depending on types of commands that require same set of inputs, the cases are designed
        // to flow through. 
        switch(user_option)
        {
        case USER_OPTION_TASK::Write_Config_File:
        case USER_OPTION_TASK::Read_Config_File:
            File_Selection(file_option);
            Config_File_Segment_Selection(segmentType);
            break;

        case USER_OPTION_TASK::Read_Event_Log:
        case USER_OPTION_TASK::Read_System_State:
            File_Selection(file_option);
            break;

        case USER_OPTION_TASK::Start_Standard_Telemetry:
            std::cout << "Collect standard telemetry on all processors? (y/n)" << std::endl;
            std::cin >> yes_no_str;
            if (yes_no_str == "y" || yes_no_str == "Y")
            {
                collectTelemetryForAllProcessors = true;
            }
            break;
        case USER_OPTION_TASK::Start_Raw_Telemetry:
            std::cout << "Collect raw telemetry on all processors? (y/n)" << std::endl;
            std::cin >> yes_no_str;
            if (yes_no_str == "y" || yes_no_str == "Y")
            {
                collectTelemetryForAllProcessors = true;
            }
            break;
        case USER_OPTION_TASK::Stop_Telemetry:
            std::cout << "Stop telemetry on all processors? (y/n)" << std::endl;
            std::cin >> yes_no_str;
            if (yes_no_str == "y" || yes_no_str == "Y")
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
            Serial_Number(serial_number);
            break;
        case USER_OPTION_TASK::Write_Mag_Config_File:
        case USER_OPTION_TASK::Read_Mag_Config_File:
            File_Selection(file_option);
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

int Quit_MX_App(vector<string>& vs) {
    cout << "Quit_MX_App" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0; 
}
int Write_Config_File(vector<string>& vs) {
    cout << "Write_Config_File" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0; 
}
int Read_Config_File(vector<string>& vs) {
    cout << "Read_Config_File" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0; 
}
int Verify_Config_File(vector<string>& vs) {
    cout << "Verify_Config_File" << endl; 
    // none
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Start_Standard_Telemetry(vector<string>& vs) {
    cout << "Start_Standard_Telemetry" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Start_Raw_Telemetry(vector<string>& vs) {
    cout << "Start_Raw_Telemetry" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Stop_Telemetry(vector<string>& vs) {
    cout << "Stop_Telemetry" << endl; 
    return 0;
}
int Read_System_State(vector<string>& vs) {
    cout << "Read_System_State" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Read_Event_Log(vector<string>& vs) {
    cout << "Read_Event_Log" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Clear_System_State(vector<string>& vs) {
    cout << "Clear_System_State" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Clear_Event_Log(vector<string>& vs) {
    cout << "Clear_Event_Log" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Display_Version_Number(vector<string>& vs) {
    cout << "Display_Version_Number" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Run_Alarm_POST(vector<string>& vs) {
    cout << "Run_Alarm_POST" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Run_Magnetometer_POST(vector<string>& vs) {
    cout << "Run_Magnetometer_POST" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Run_Miscellaneous_POST(vector<string>& vs) {
    cout << "Run_Miscellaneous_POST" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Run_Actuator_Test(vector<string>& vs) {
    cout << "Run_Actuator_Test" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Run_ADP_POST(vector<string>& vs) {
    cout << "Run_ADP_POST" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0;
}
int Run_Hall_POST(vector<string>& vs) { 
    cout << "Run_Hall_POST" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0; 
}
int Read_Main_Board_Serial_Number(vector<string>& vs) { 
    cout << "Read_Main_Board_Serial_Number" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0; 
}
int Write_Main_Board_Serial_Number(vector<string>& vs){ 
    cout << "Write_Main_Board_Serial_Number" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0; 
}
int Read_Mag_Config_File(vector<string>& vs) { 
    cout << "Read_Mag_Config_File" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0; 
}
int Write_Mag_Config_File(vector<string>& vs) { 
    cout << "Write_Mag_Config_File" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0; 
}
int Verify_Mag_Config_File(vector<string>& vs) { 
    cout << "Verify_Mag_Config_File" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0; 
}
int Do_Installation_Calibration(vector<string>& vs) { 
    cout << "Do_Installation_Calibration" << endl; 
    for (auto& s : vs) {
        cout << s << endl;
    }
    return 0; 
}

template<typename T, typename V> using ifun = T(V);
using ifunx = ifun<int, vector<string>&>;

map<string, function<ifunx>> mx_ops = {
    {"Quit_MX_App",                     Quit_MX_App},
    {"Write_Config_File",               Write_Config_File},
    {"Read_Config_File",                Read_Config_File},
    {"Verify_Config_File",              Verify_Config_File},
    {"Start_Standard_Telemetry",        Start_Standard_Telemetry},
    {"Start_Raw_Telemetry",             Start_Raw_Telemetry},
    {"Stop_Telemetry",                  Stop_Telemetry},
    {"Read_System_State",               Read_System_State},
    {"Read_Event_Log",                  Read_Event_Log},
    {"Clear_System_State",              Clear_System_State},
    {"Clear_Event_Log",                 Clear_Event_Log},
    {"Display_Version_Number",          Display_Version_Number},
    {"Run_Alarm_POST",                  Run_Alarm_POST},
    {"Run_Magnetometer_POST",           Run_Magnetometer_POST},
    {"Run_Miscellaneous_POST",          Run_Miscellaneous_POST},
    {"Run_Actuator_Test",               Run_Actuator_Test},
    {"Run_ADP_POST",                    Run_ADP_POST},
    {"Run_Hall_POST",                   Run_Hall_POST},
    {"Read_Main_Board_Serial_Number",   Read_Main_Board_Serial_Number},
    {"Write_Main_Board_Serial_Number",  Write_Main_Board_Serial_Number},
    {"Read_Mag_Config_File",            Read_Mag_Config_File},
    {"Write_Mag_Config_File",           Write_Mag_Config_File},
    {"Verify_Mag_Config_File",          Verify_Mag_Config_File},
    {"Do_Installation_Calibration",     Do_Installation_Calibration},
};


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

        vector<string> words = find_words(line);
        if (words.size() > 0) {
            mx_ops[words[0]](words);
        }

    }
}

int main()
{
    ifstream myfile;
    myfile.open ("test.mx");
    xref(myfile);
    myfile.close();
}
