
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

    parser->Set_Column(++column, "raw_rates_0.X", TELEMETRY_LOG_STRUCT, raw_rates_0.X,  S16_Type);
    parser->Set_Column(++column, "raw_rates_0.Y", TELEMETRY_LOG_STRUCT, raw_rates_0.Y,  S16_Type);
    parser->Set_Column(++column, "raw_rates_0.Z", TELEMETRY_LOG_STRUCT, raw_rates_0.Z,  S16_Type);
    parser->Set_Column(++column, "raw_rates_1.X", TELEMETRY_LOG_STRUCT, raw_rates_1.X,  S16_Type);
    parser->Set_Column(++column, "raw_rates_1.Y", TELEMETRY_LOG_STRUCT, raw_rates_1.Y,  S16_Type);
    parser->Set_Column(++column, "raw_rates_1.Z", TELEMETRY_LOG_STRUCT, raw_rates_1.Z,  S16_Type);
    parser->Set_Column(++column, "raw_rates_2.X", TELEMETRY_LOG_STRUCT, raw_rates_2.X,  S16_Type);
    parser->Set_Column(++column, "raw_rates_2.Y", TELEMETRY_LOG_STRUCT, raw_rates_2.Y,  S16_Type);
    parser->Set_Column(++column, "raw_rates_2.Z", TELEMETRY_LOG_STRUCT, raw_rates_2.Z,  S16_Type);
    parser->Set_Column(++column, "raw_rates_3.X", TELEMETRY_LOG_STRUCT, raw_rates_3.X,  S16_Type);
    parser->Set_Column(++column, "raw_rates_3.Y", TELEMETRY_LOG_STRUCT, raw_rates_3.Y,  S16_Type);
    parser->Set_Column(++column, "raw_rates_3.Z", TELEMETRY_LOG_STRUCT, raw_rates_3.Z,  S16_Type);
    parser->Set_Column(++column, "raw_accels_0.X", TELEMETRY_LOG_STRUCT, raw_accels_0.X,  S16_Type);
    parser->Set_Column(++column, "raw_accels_0.Y", TELEMETRY_LOG_STRUCT, raw_accels_0.Y,  S16_Type);
    parser->Set_Column(++column, "raw_accels_0.Z", TELEMETRY_LOG_STRUCT, raw_accels_0.Z,  S16_Type);
    parser->Set_Column(++column, "raw_accels_1.X", TELEMETRY_LOG_STRUCT, raw_accels_1.X,  S16_Type);
    parser->Set_Column(++column, "raw_accels_1.Y", TELEMETRY_LOG_STRUCT, raw_accels_1.Y,  S16_Type);
    parser->Set_Column(++column, "raw_accels_1.Z", TELEMETRY_LOG_STRUCT, raw_accels_1.Z,  S16_Type);
    parser->Set_Column(++column, "raw_accels_2.X", TELEMETRY_LOG_STRUCT, raw_accels_2.X,  S16_Type);
    parser->Set_Column(++column, "raw_accels_2.Y", TELEMETRY_LOG_STRUCT, raw_accels_2.Y,  S16_Type);
    parser->Set_Column(++column, "raw_accels_2.Z", TELEMETRY_LOG_STRUCT, raw_accels_2.Z,  S16_Type);
    parser->Set_Column(++column, "raw_accels_3.X", TELEMETRY_LOG_STRUCT, raw_accels_3.X,  S16_Type);
    parser->Set_Column(++column, "raw_accels_3.Y", TELEMETRY_LOG_STRUCT, raw_accels_3.Y,  S16_Type);
    parser->Set_Column(++column, "raw_accels_3.Z", TELEMETRY_LOG_STRUCT, raw_accels_3.Z,  S16_Type);
    parser->Set_Column(++column, "raw_mags.X", TELEMETRY_LOG_STRUCT, raw_mags.X,  S16_Type);
    parser->Set_Column(++column, "raw_mags.Y", TELEMETRY_LOG_STRUCT, raw_mags.Y,  S16_Type);
    parser->Set_Column(++column, "raw_mags.Z", TELEMETRY_LOG_STRUCT, raw_mags.Z,  S16_Type);
    parser->Set_Column(++column, "rate_samples", TELEMETRY_LOG_STRUCT, rate_samples,  U8_Type);
    parser->Set_Column(++column, "accel_samples", TELEMETRY_LOG_STRUCT, accel_samples,  U8_Type);
    parser->Set_Column(++column, "eulers.phi", TELEMETRY_LOG_STRUCT, eulers.phi,  F32_Type);
    parser->Set_Column(++column, "eulers.theta", TELEMETRY_LOG_STRUCT, eulers.theta,  F32_Type);
    parser->Set_Column(++column, "eulers.psi", TELEMETRY_LOG_STRUCT, eulers.psi,  F32_Type);
    parser->Set_Column(++column, "IAS", TELEMETRY_LOG_STRUCT, IAS,  F32_Type);
    parser->Set_Column(++column, "baro_altitude", TELEMETRY_LOG_STRUCT, baro_altitude,  F32_Type);
    parser->Set_Column(++column, "framenumber", TELEMETRY_LOG_STRUCT, framenumber,  U32_Type);
    parser->Set_Column(++column, "latest_fault", TELEMETRY_LOG_STRUCT, latest_fault,  U32_Type);
    parser->Set_Column_Masked(++column, "mag_valid", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 0));
    parser->Set_Column_Masked(++column, "accel_valid", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 1));
    parser->Set_Column_Masked(++column, "gyro_valid", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 2));
    parser->Set_Column_Masked(++column, "oat_valid", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 3));
    parser->Set_Column_Masked(++column, "adc0_valid", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 4));
    parser->Set_Column_Masked(++column, "adc1_valid", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 5));
    parser->Set_Column_Masked(++column, "remote_accel_valid", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 6));
    parser->Set_Column_Masked(++column, "ADAHRS_valid", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 7));
    parser->Set_Column_Masked(++column, "UAR_Mode", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 8));
    parser->Set_Column_Masked(++column, "Pilot_Override", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 9));
    parser->Set_Column_Masked(++column, "Autopilot_Engaged", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 10));
    parser->Set_Column_Masked(++column, "Autopilot_Ready", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 11));
    parser->Set_Column_Masked(++column, "CPD_Input", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 12));
    parser->Set_Column_Masked(++column, "Video_Sync_Light_Output", TELEMETRY_LOG_STRUCT, sys_flags.flags_bf, BOOLEAN_Type, (1 << 13));
    parser->Set_Column_Masked(++column, "Roll_Rate_Fail", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 0));
    parser->Set_Column_Masked(++column, "Roll_ADP_Cmd_Fail", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 1));
    parser->Set_Column_Masked(++column, "Roll_ACT_POS_Fail", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 2));
    parser->Set_Column_Masked(++column, "Roll_ATT_Fail", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 3));
    parser->Set_Column_Masked(++column, "Pitch_Rate_Fail", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 4));
    parser->Set_Column_Masked(++column, "Pitch_ADP_Cmd_Fail", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 5));
    parser->Set_Column_Masked(++column, "Pitch_ACT_Pos_Fail", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 6));
    parser->Set_Column_Masked(++column, "Pitch_ATT_Fail", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 7));
    parser->Set_Column_Masked(++column, "Roll_Servoloop_CurrSatLL", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 8));
    parser->Set_Column_Masked(++column, "Roll_Servoloop_CurrSatUL", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 9));
    parser->Set_Column_Masked(++column, "Roll_Servoloop_PLSat", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 10));
    parser->Set_Column_Masked(++column, "Roll_Servoloop_PLInv", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 11));
    parser->Set_Column_Masked(++column, "Roll_Servoloop_RLSat", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 12));
    parser->Set_Column_Masked(++column, "Pitch_Servoloop_CurrSatLL", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 13));
    parser->Set_Column_Masked(++column, "Pitch_Servoloop_CurrSatUL", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 14));
    parser->Set_Column_Masked(++column, "Pitch_Servoloop_PLSat", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 15));
    parser->Set_Column_Masked(++column, "Pitch_Servoloop_PLInv", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 16));
    parser->Set_Column_Masked(++column, "Pitch_Servoloop_RLSat", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 17));
    parser->Set_Column_Masked(++column, "Combined_Fail_Status", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 18));
    parser->Set_Column_Masked(++column, "Roll_Rate_Limited", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 19));
    parser->Set_Column_Masked(++column, "Pitch_Rate_Limited", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 20));
    parser->Set_Column_Masked(++column, "Roll_Att_Ctrl_Integ_Sat", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 21));
    parser->Set_Column_Masked(++column, "Pitch_Att_Ctrl_Integ_Sat", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 22));
    parser->Set_Column_Masked(++column, "Roll_ADP_Rate_Limit", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 23));
    parser->Set_Column_Masked(++column, "Pitch_ADP_Rate_Limit", TELEMETRY_LOG_STRUCT, claw_flags.flags_bf, BOOLEAN_Type, (1 << 24));
    parser->Set_Column(++column, "button_states", TELEMETRY_LOG_STRUCT, button_states,  U8_Type);

    return parser;
}

