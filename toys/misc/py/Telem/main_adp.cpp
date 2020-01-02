static Parser_Alias * Create_ADP_Telemetry_Parser(const std::string & filename)
{    
    int column = -1;
    Parser<TELEMETRY_LOG_STRUCT_ADP> * parser = new Parser<TELEMETRY_LOG_STRUCT_ADP>(filename);
    parser->Duplicate_To_Combined_File(true);

    parser->Set_Lines_Per_File(25000);

#if 0
    parser->Set_Column(++column, "framenumber", TELEMETRY_LOG_STRUCT_ADP, framenumber,  U32_Type);
    parser->Set_Column(++column, "outer_loop_mode", TELEMETRY_LOG_STRUCT_ADP, outer_loop_mode,  U32_Type);
    parser->Set_Column(++column, "annunciator_states", TELEMETRY_LOG_STRUCT_ADP, annunciator_states,  U8_Type);
    parser->Set_Column(++column, "psi_target", TELEMETRY_LOG_STRUCT_ADP, psi_target,  F32_Type);
    parser->Set_Column(++column, "psi_error", TELEMETRY_LOG_STRUCT_ADP, psi_error,  F32_Type);
    parser->Set_Column(++column, "psi_dot_target", TELEMETRY_LOG_STRUCT_ADP, psi_dot_target,  F32_Type);
    parser->Set_Column(++column, "psi_dot_error", TELEMETRY_LOG_STRUCT_ADP, psi_dot_error,  F32_Type);
    parser->Set_Column(++column, "PP_psi_dot_dot", TELEMETRY_LOG_STRUCT_ADP, PP_psi_dot_dot,  F32_Type);
    parser->Set_Column(++column, "SP_psi_dot_dot", TELEMETRY_LOG_STRUCT_ADP, SP_psi_dot_dot,  F32_Type);
#endif

    return parser;
}

