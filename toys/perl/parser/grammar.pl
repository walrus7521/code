<<'_EOGRAMMAR_';
    # Terminals (macros that can't expand further)

    NUM       : /[-+]?\d+/      # numbers
    ID        : /[a-z0-9_]+/i   # Identifier or Type
    ALL       : /.*/
    PRIM      : /(f32)/i | /(u|s)32/i | /(u|s)16/i | /(u|s)8/i | /(boolean)/i

    space    : <skip:''>
    indent   : space(s?)
    startcol : '' { $thiscolumn }    # NEED THE '' TO STEP PAST TOKEN SEP
    endcol   :  { $prevcolumn }              

    typedecl : (NUM) ('|') (PRIM) (ID)
              {     my $indent = $itempos[3]{column}{from} - $itempos[2]{column}{to};
                    my $offset = $item[1];
                    my $type   = $item[3];
                    my $id     = $item[4];
                    our $bit_count = 0;
                    my @args = ();
                    push(@args, (0, $indent, $offset, $id, $type, -1, -1));
                    return main::term(@args);
              }
             | (NUM) ('|') (ID) (ID) (ALL)
              {     my $indent = $itempos[3]{column}{from} - $itempos[2]{column}{to};
                    my $offset = $item[1];
                    my $type   = $item[3];
                    my $id     = $item[4];
                    my $rest   = $item[5];
                    my @args = ();
                    push(@args, (0, $indent, $offset, $id, $type, $rest));
                    return main::non_term(@args);
              }
             | (NUM)':'(NUM)'-'(NUM) ('|') (ID) (ID)
              {     my $indent = $itempos[7]{column}{from} - $itempos[6]{column}{to};
                    my $offset    = $item[1];
                    my $bit_start = $item[3];
                    my $bit_end   = $item[5];
                    my $bit_width = abs(int($bit_start) - int($bit_end)) + 1;
                    my $type      = $item[7];
                    my $id        = $item[8];
                    our $bit_count;
                    my @args = ();
                    push(@args, (0, $indent, $offset, $id, $type, $bit_count, $bit_width));
                    my $ret = main::term(@args);
                    $bit_count++;
                    return $ret;
              }
             | (NUM) ('|') (ID)
              {     our @stack = (); # clear path accum stack
                    #print("$item[3]\n"); 
              }

    startrule: typedecl(s)

_EOGRAMMAR_

