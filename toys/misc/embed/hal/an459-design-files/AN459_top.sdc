create_clock	-name "clkin"				-period "50MHz" [ get_ports clkin ]
create_clock	-name "altera_reserved_tck"	-period "10MHz" [ get_ports altera_reserved_tck ]

set_clock_groups	-exclusive	-group [get_clocks clkin ]	-group [get_clocks altera_reserved_tck ]

set_false_path -from [ get_ports reset_n ] -to *

set_min_delay -from * -to [ get_ports uart_tx ] 2
set_max_delay -from * -to [ get_ports uart_tx ] 10

set_min_delay -from [ get_ports uart_rx ] -to * 2
set_max_delay -from [ get_ports uart_rx ] -to * 10

set_input_delay		-clock [ get_clocks altera_reserved_tck ] 10 [get_ports altera_reserved_tdi]
set_input_delay		-clock [ get_clocks altera_reserved_tck ] 10 [get_ports altera_reserved_tms]
set_output_delay	-clock [ get_clocks altera_reserved_tck ] 10 [get_ports altera_reserved_tdo]
