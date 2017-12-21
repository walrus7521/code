module AN459_top (
		input		clkin,
		input		reset_n,
		output	uart_tx,
		input		uart_rx
);

system system_inst (
	// 1) global signals:
	.clk_clk					(clkin),
	.reset_reset_n			(reset_n),
	.uart_txd				(uart_tx),
	.uart_rxd				(uart_rx)
);

endmodule
