#!/usr/bin/perl -w
#===============================================================================
#
#         FILE:  csourceparser.pl
#
#        USAGE:  ./csourceparser.pl [Option] ... File ...
#
#
#  DESCRIPTION:  Parse and extract specified elements from source-code
#                                written in the C language
#
#      OPTIONS:  ---
# REQUIREMENTS:  Perl Version >= 5.8.0, Parse::RecDescent, Getopt::Long, Pod::Usage
#         BUGS:  ---
#        NOTES:  ---
#       AUTHOR:  <hendrik.sirges(at)fh-swf.de>
#      COMPANY:  FH-SWF
#      VERSION:  0.1.0
#      CREATED:  07/10/05 12:34:53 CEST
#     REVISION:  ---
#===============================================================================
 
require 5.008000;
use strict;
 
use Parse::RecDescent;
use Getopt::Long;
use Pod::Usage;
 
# use Data::Dumper 'Dumper';
 
#$::RD_HINT             = 1;                                    # Print hints on errors
#$::RD_ERRORS           = 1;                                    # Print errors
#$::RD_WARN             = 1;
#$::RD_TRACE            = 1;                                    # Print tracecode to STDERR
#$::RD_AUTOSTUB         = 1;
 
###############################################################
# Grammar used to find and remove comments from C source code #
###############################################################
my $decomment_grammar = <<'END_OF_DECOMMENT';
 
program : <skip:''> { @{$thisparser}{qw(code)} = () }
          part(s)
          {@{$thisparser}{code};}
 
part    : comment               { $thisparser->{code}                .= " "; }
        | C_code                { $thisparser->{code}        .= $item[1]; }
        | string                { $thisparser->{code}        .= qq("$item[1]"); }
 
C_code  : m{(
              [^"/]+    # one or more non-delimiters
              (                 # then (optionally)...
               /                # a potential comment delimiter
               [^*/]    # which is not an actual delimiter
              )?                #
            )+                  # all repeated once or more
           }x
 
string  : m{"           # a leading delimiter
            ((                  # zero or more...
              \\.               # escaped anything
              |                 # or
              [^"]              # anything but a delimiter
             )*
            )
            "}x
                { $return =  $1 }
 
 
comment : m{\s*                         # optional whitespace
            //                                  # comment delimiter
            [^\n]*                              # anything except a newline
            \n                                  # then a newline
            }x
 
        | m{\s*                                 # optional whitespace
            /\*                                 # comment opener
            (?:[^*]+|\*(?!/))*  # anything except */
            \*/                         # comment closer
        ([ \t]*)?               # trailing blanks or tabs
            }x
END_OF_DECOMMENT
 
######################################################################################
# Grammar used to parse C source code (without comments and preprocessor directives) #
# ####################################################################################
my $Cgrammar = <<'END_OF_C_GRAMMAR';
 
        translation_unit:
                external_declaration(s)
        |       <error>
 
        external_declaration:
                function_definition
        |       declaration
        |       <resync>
                {
                        if ($::opt_SKIPPEDLINES || (defined $::opt_VERBOSE and $::opt_VERBOSE >= 1 ))
                        {
                                print "Skipping line $thisline\n"       # Try next line if possible...
                        }
                 }
 
        function_definition:
                declaration_specifiers(?) declarator declaration_list(?) compound_statement
                {
                        if($::opt_FUNCTIONS)
                        {
                                $::functions_output .= ::flatten_list($item[1]);
                                $::functions_output .= ::flatten_list($item[2]);
                                $::functions_output .= ::flatten_list($item[3]) . ";\n";
                        }
                }
 
        declaration:
                declaration_specifiers init_declarator_list(?) ';'
                {
            if($::opt_DECLARATIONS)
            {
                                $::declarations_output .= ::flatten_list($item[1]);
                                $::declarations_output .= ::flatten_list($item[2]);
                                $::declarations_output .= ::flatten_list($item[3]) . "\n";
            }
        }
 
        declaration_list:
                declaration(s)
 
        declaration_specifiers:
                type_qualifier                  declaration_specifiers(?)
        |       storage_class_specifier declaration_specifiers(?)
        |       type_specifier                  declaration_specifiers(?)
 
        storage_class_specifier:
                  'auto'
                | 'register'
                | 'static'
                | 'extern'
                | 'typedef'
 
        type_specifier:
                  'int'
                | 'double'
                | 'void'
                | 'char'
                | 'long'
                | 'float'
                | 'signed'
                | 'unsigned'
                | 'short'
                | struct_or_union_specifier
                | enum_specifier
                | typedef_name ...typedef_name_lookahead { [$item[1] ] }
 
        typedef_name_lookahead:
                declarator
#       |       pointer
#       |       ',' ...parameter_type_list
#       |       ')'
 
        type_qualifier:
                  'const'
                | 'volatile'
 
        struct_or_union_specifier:
                  struct_or_union IDENTIFIER(?) '{' struct_declaration_list(?) '}'
          {
                        if($::opt_STRUCTS){
                                $::structs_output .= ::flatten_list($item[1]) . " ";
                                $::structs_output .= ::flatten_list($item[2]);
                                $::structs_output .= ::flatten_list($item[3]) . "\n";
                                $::structs_output .= ::flatten_list_beautified($item[4]);
                                $::structs_output .= ::flatten_list($item[5]) . ";\n\n";
                        }
          }
                | struct_or_union IDENTIFIER
 
        struct_or_union:
                  'struct'
                | 'union'
 
 
        struct_declaration_list:
                struct_declaration(s)
 
        init_declarator_list:
                init_declarator(s /(,)/)
 
        init_declarator:
                declarator '=' initializer
        |       declarator
 
        struct_declaration:
                specifier_qualifier_list struct_declarator_list ';'
 
        specifier_qualifier_list:
                type_specifier specifier_qualifier_list(?)
        |       type_qualifier specifier_qualifier_list(?)
 
        struct_declarator_list:
                struct_declarator(s /(,)/)
 
        struct_declarator:
                declarator(?) ':' constant_expression
        |       declarator
 
        enum_specifier:
                'enum' IDENTIFIER(?) '{' enumerator_list '}'
          {
                        if($::opt_STRUCTS){
                                $::structs_output .= ::flatten_list($item[1]) . " ";
                                $::structs_output .= ::flatten_list($item[2]);
                                $::structs_output .= ::flatten_list($item[3]) . "\n";
                                $::structs_output .= ::flatten_list_beautified($item[4]);
                                $::structs_output .= ::flatten_list($item[5]) . ";\n\n";
                        }
          }
        |       'enum' IDENTIFIER
 
        enumerator_list:
                enumerator(s /(,)/)
 
        enumerator:
                IDENTIFIER ('=' constant_expression)(?)
 
        declarator:
                pointer(?) direct_declarator
 
        function_signature:
                '[' constant_expression(?) ']'
        |       '(' parameter_type_list ')'
        |       '(' identifier_list(?) ')'
 
        direct_declarator:
                IDENTIFIER function_signature(s?)
        |       '(' declarator ')' function_signature(s?)
 
 
        pointer:
          '*' type_qualifier_list(?) pointer(?)
 
        type_qualifier_list:
                type_qualifier(s)
 
        parameter_type_list:
                parameter_list (',' '...')(?)
 
        parameter_list:
                parameter_declaration(s /(,)/)
 
        parameter_declaration:
                declaration_specifiers declarator
        |       declaration_specifiers abstract_declarator(?)
 
        identifier_list:
                IDENTIFIER(s /(,)/)
 
        initializer:
                assignment_expression
        |       '{' initializer_list (',')(?) '}'
 
        initializer_list:
                initializer(s /(,)/)
 
        type_name:
                specifier_qualifier_list abstract_declarator(?)
 
        abstract_declarator:
                pointer(?) direct_abstract_declarator
        |       pointer
 
        abstract_type:
                '[' constant_expression(?) ']'
        |       '(' parameter_type_list(?) ')'
 
        direct_abstract_declarator:
                '(' abstract_declarator ')' abstract_type(s?)
        |       abstract_type(s)
 
        typedef_name:
                IDENTIFIER
 
        statement:
                selection_statement
        |       expression_statement
        |       iteration_statement
        |       compound_statement
        |       jump_statement
        |       labeled_statement
 
 
        labeled_statement:
                'case' constant_expression ':' statement
        |       IDENTIFIER ':' statement
        |       'default' ':' statement
 
        expression_statement:
                expression(?) ';'
 
        compound_statement:
                '{' declaration_list(?) statement_list(?) '}'
 
        statement_list:
                statement(s)
 
        selection_statement:
                'if'      '(' expression  ')' statement ('else' statement)(?)
        |       'switch'  '(' expression  ')' statement
 
        iteration_statement:
                'for'   '(' expression(?) ';' expression(?) ';' expression(?) ')' statement
        |       'while' '(' expression ')' statement
        |       'do' statement 'while' '(' expression ')'
 
        jump_statement:
                'return' expression(?) ';'
        |       'break' ';'
        |       'continue' ';'
        |       'goto' IDENTIFIER ';'
 
        expression:
                assignment_expression(s /(,)/)
 
        assignment_expression:
                unary_expression ASSIGNMENT_OPERATOR assignment_expression
        |       conditional_expression
 
 
        conditional_expression:
                 logical_OR_expression  ('?' expression ':' conditional_expression)(?)
 
        constant_expression:
                conditional_expression
 
        logical_OR_expression:
                logical_AND_expression(s /(\|\|)/)
 
        logical_AND_expression:
                inclusive_OR_expression(s /(&&)/)
 
        inclusive_OR_expression:
                exclusive_OR_expression(s /(\|)/)
 
        exclusive_OR_expression:
                AND_expression(s /(\^)/)
 
        AND_expression:
                equality_expression(s /(&)/)
 
        equality_expression:
                relational_expression(s /(==|!=)/)
 
        relational_expression:
                shift_expression(s /(<=|>=|<|>)/)
 
        shift_expression:
                additive_expression(s /(<<|>>)/)
 
        additive_expression:
                multiplicative_expression(s /(\+|-)/)
 
        multiplicative_expression:
                cast_expression(s /(\*|\/|%)/)
 
        cast_expression:
                unary_expression
        |       '(' type_name ')' cast_expression
 
        unary_expression:
                postfix_expression
        |       '++'  unary_expression
        |       '--'  unary_expression
        |       'sizeof' '(' type_name ')'
        |   UNARY_OPERATOR cast_expression
        |       'sizeof'        unary_expression
 
 
        postfix_expression:
                primary_expression postfix_expression_token(s?)
 
 
        postfix_expression_token:
          '[' expression ']'
                | '(' argument_expression_list(?)')'
                | '.'  IDENTIFIER
                | '->' IDENTIFIER
                | '++'
                | '--'
 
 
        primary_expression:
                IDENTIFIER
        |       constant
        |       STRING
        |       '(' expression ')'
 
        argument_expression_list:
                assignment_expression(s /(,)/)
 
        constant:
                CHARACTER_CONSTANT
        |       FLOATING_CONSTANT
        |       INTEGER_CONSTANT
        |       ENUMERATION_CONSTANT
 
 
###     TERMINALS
 
 
        INTEGER_CONSTANT:
                /(?:0[xX][\da-fA-F]+)                                   # Hexadecimal
                 |(?:0[0-7]*)                                                   # Octal or Zero
                 |(?:[1-9]\d*)                                                  # Decimal
                 [uUlL]?                                                                # Suffix
                 /x
 
        CHARACTER_CONSTANT:
                /'([^\\'"]                                                      # None of these
                 |\\['\\ntvbrfa'"]                              # or a backslash followed by one of those
                 |\\[0-7]{1,3}|\\x\d+)'                 # or an octal or hex constant
                /x
 
        FLOATING_CONSTANT:
                /(?:\d+|(?=\.\d+))                                      # No leading digits only if '.moreDigits' follows
                 (?:\.|(?=[eE]))                                                # There may be no floating point only if an exponent is present
                 \d*                                                                    # Zero or more floating digits
                 ([eE][+-]?\d+)?                                                # expontent
                 [lLfF]?                                                                # Suffix
                /x
 
        ENUMERATION_CONSTANT:
                INTEGER_CONSTANT
 
        STRING:
                /"(([^\\'"])                                                    # None of these
                |(\\[\\ntvbrfa'"])                                      # or a backslash followed by one of those
                |(\\[0-7]{1,3})|(\\x\d+))*"/x           # or an octal or hex
 
        IDENTIFIER:
                /(?!(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto              # LOOKAHEAD FOR KEYWORDS
                        |if|int|long|register|return|signed|sizeof|short|static|struct|switch|typedef                   # NONE OF THE KEYWORDS
                        |union|unsigned|void|volatile|while)[^a-zA-Z_])                                                                                 # SHOULD FULLY MATCH!
                        (([a-zA-Z]\w*)|(_\w+))/x                                                                                                                                # Check for valid identifier
 
        ASSIGNMENT_OPERATOR:
                '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '<<=' | '>>=' | '&=' | '^=' | '|='
 
        UNARY_OPERATOR:
                '&' | '*' | '+' | '-' | '~' | '!'
 
END_OF_C_GRAMMAR
 
 
#===  FUNCTION  ================================================================
#         NAME:  flatten_list
#  DESCRIPTION:  Extracts values from a recursive list. Double whitespaces will
#                                be reduced
# PARAMETER  1:  Array Reference
#===============================================================================
 
sub flatten_list {
    ( my $tokens = join ' ', map { ref($_) ? flatten_list(@$_) : ($_) } @_ ) =~ s/\s+/ /g;
    $tokens;
}
 
#===  FUNCTION  ================================================================
#         NAME:  flatten_list_beautified
#  DESCRIPTION:  Like flatten_list but inserts a newline after each semicolon
# PARAMETER  1:  Array Reference
#===============================================================================
 
sub flatten_list_beautified {
    ( my $tokens = join ' ', map { ref($_) ? flatten_list(@$_) : ($_) } @_ ) =~ s/\s+/ /g;
    $tokens =~ s/;/;\n/g;
        $tokens =~ s/^\s*/\t/mg;
    $tokens;
}
 
#--------------------------------------------------------------------------#
#  Parsing variables                                                                                                       #
#--------------------------------------------------------------------------#
 
my $decommentParser;          # Parser using decomment grammar
my $Cparser;                  # Parser using C grammar
my $C_source;                 # C source code
my $decommented_C_source;     # C source code without comments
my $preprocessed_C_source;    # C source code without preprocessor directives
    # preprocessor directives are just removed, not evalued
 
#--------------------------------------------------------------------------#
#  Command line options                                                                                                    #
#--------------------------------------------------------------------------#
 
our $opt_HELP         = '';
our $opt_SKIPPEDLINES = '';
our $opt_ERRORS       = '';
our $opt_TRACE        = '';
our $opt_CODE         = '';
our $opt_VERBOSE      = 0;
our $opt_PRECOMPILE   = '';
 
our $opt_FUNCTIONS    = '';
our $opt_DECLARATIONS = '';
our $opt_STRUCTS          = '';
 
Getopt::Long::Configure("bundling");    # Enables option bundling
 
GetOptions(                             # Parse command line options
    'help|h'         => \$opt_HELP,            # --help -h
    'skippedlines|s' => \$opt_SKIPPEDLINES,    # --skippedlines -s
    'errors|e'       => \$opt_ERRORS,          # --errors -e
    'trace|t'        => \$opt_TRACE,           # --trace -t
    'code|c'         => \$opt_CODE,            # --code -c
    'verbose|v+'     => \$opt_VERBOSE,         # --verbose -v
    'functions|f'    => \$opt_FUNCTIONS,       # --functions -f
    'declarations|d' => \$opt_DECLARATIONS,    # --declarations -d
    'precompile|p'   => \$opt_PRECOMPILE,      # --precompile -p
        'structs|u'              =>  \$opt_STRUCTS              # --structs -u
);
 
# variables for parser output
our $functions_output    = '';
our $declarations_output = '';
our $structs_output      = '';
 
$opt_HELP and pod2usage( -verbose => 2 );
 
# Set error reporting
if ($opt_ERRORS) {
    $::RD_HINT   = 1;                          # Print hints on errors
    $::RD_ERRORS = 1;                          # Print errors
    open( Parse::RecDescent::ERROR, ">errfile" )
      or die "Can't open errfile: $!";
}
# Die if no input files present
@ARGV or pod2usage( -message => "Error: More arguments required.", -verbose => 0 );
 
{
    local $/;
    $C_source = <>;
}
 
# Set trace level
if ( $opt_TRACE || ( $opt_VERBOSE >= 3 ) ) {
    $::RD_TRACE = 1;
}
 
# Generate precompiled parser modules
if($opt_PRECOMPILE) {
        print("\nCreating precompiled parsers...  \n");
        Parse::RecDescent->Precompile( $decomment_grammar,"CSourceParser::DecommentGrammar" );
        Parse::RecDescent->Precompile( $Cgrammar, "CSourceParser::Cgrammar" );
        print("Done\n\n");
}
 
 
#--------------------------------------------------------------------------#
#  Parse Level 1 (removes comments)                                                                                #
#--------------------------------------------------------------------------#
 
if ( -e "DecommentGrammar.pm" ) {
    require DecommentGrammar;
    $decommentParser = new CSourceParser::DecommentGrammar
      or die "Malformed Decomment grammar!\n";
}
else {
    $decommentParser = new Parse::RecDescent($decomment_grammar)
      or die "Malformed Decomment grammar!\n";
}
 
defined( $decommented_C_source = $decommentParser->program($C_source) )
  or die "Malformed C code found at parse level 1!\n";
 
#--------------------------------------------------------------------------#
#  Parse Level 2 (Removes preprocessor directives)                                                 #
#--------------------------------------------------------------------------#
 
open( PREPROCESS, "<", \$decommented_C_source )    # open string as filehandle
  or die "Can't open input string for parse level 2: $!";
$preprocessed_C_source = "";
my $skip_line = 0;
 
foreach (<PREPROCESS>) {
 
    # Match preprocessor directives ...
    if (
        m{\s*                                                                                                                                                           # Optional whitespace
                \#                                                                                                                                                                      # Preprocessor opener
                \s*                                                                                                                                                                     # Optional whitespace
                (?:(define|include|undef|ifdef|ifndef|if|endif|else|elif|line|error|pragma)\s)          # Keyword followed by one or more whitespace
                .*                                                                                                                                                                      # anything (optinal)
                }x || $skip_line
      )
    {
        $skip_line = /.*\\[\n]/;    # Ignore this line AND NEXT LINE ALSO
        $preprocessed_C_source .= " ";    # if this line ends with backslash
    }
    else {
        $preprocessed_C_source .= $_;     # OK, parse this line
    }
}
 
if ( $opt_CODE || ( $opt_VERBOSE >= 1 ) ) {  # print sourcecode with linenumbers
    my $i = 1;
    foreach ( split( /\n/, $preprocessed_C_source ) ) {
        print "$i\t$_\n";
        $i++;
    }
}
 
if ( $opt_VERBOSE >= 2 ) {
    $::RD_TRACE = 1;
}
 
#--------------------------------------------------------------------------#
#  Parse Level 3 (parses C code)                                                                                   #
#--------------------------------------------------------------------------#
 
$::RD_AUTOACTION =
  q {  [ @item[1..$#item] ] };    # set default auto-action for grammar rules
 
if ( -e "CGrammar.pm" ) {
    require CGrammar;
    $Cparser = new CSourceParser::CGrammar or die "Malformed C grammar!\n";
}
else {
    $Cparser = new Parse::RecDescent($Cgrammar) or die "Malformed C grammar!\n";
}
 
defined( $Cparser->translation_unit($preprocessed_C_source) )
  or die "Malformed C code found at parse level 3!\n";
 
print "\nDefined Functions:\n\n$functions_output\n\n"
  if defined $functions_output
  and $opt_FUNCTIONS;
print "\nDeclarations:\n\n$declarations_output\n\n"
  if defined $declarations_output
  and $opt_DECLARATIONS;
print "\nStructures:\n\n$structs_output\n\n"
  if defined $structs_output
  and $opt_STRUCTS;
 
__END__
 
 
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#  Application Documentation
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
