#!/usr/local/bin/octave -qf

printf ("dude: %s", program_name ());
arg_list = argv ();
for i = 1:nargin
  printf (" %s", arg_list{i});
endfor
printf ("\n");
