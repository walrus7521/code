#!/usr/bin/python

#Parsed Telemetry Excel column numbers
#these should be detected from the column headers, but here as constants for now
fieldnames = [
        'raw_rates_0_X',
        'raw_rates_0_Y',
        'raw_rates_0_Z',
        'raw_rates_1_X',
        'raw_rates_1_Y',
        'raw_rates_1_Z',
        'raw_rates_2_X',
        'raw_rates_2_Y',
        'raw_rates_2_Z',
        'raw_rates_3_X',
        'raw_rates_3_Y',
        'raw_rates_3_Z',
        'raw_accels_0_X',
        'raw_accels_0_Y',
        'raw_accels_0_Z',
        'raw_accels_1_X',
        'raw_accels_1_Y',
        'raw_accels_1_Z',
        'raw_accels_2_X',
        'raw_accels_2_Y',
        'raw_accels_2_Z',
        'raw_accels_3_X',
        'raw_accels_3_Y',
        'raw_accels_3_Z',
        'raw_mags_X',
        'raw_mags_Y',
        'raw_mags_Z',
        'rate_samples',
        'accel_samples',
        'eulers_phi',
        'eulers_theta',
        'eulers_psi',
        'Down_Error_X',
        'Down_Error_Y',
        'Down_Error_Z',
        'North_Error_X',
        'North_Error_Y',
        'North_Error_Z',
        'Adaptive_Control',
        'Adaptive_Gain',
        'IAS',
        'diffp',
        'baro_altitude',
        'statp',
        'framenumber',
        'latest_fault',
]
