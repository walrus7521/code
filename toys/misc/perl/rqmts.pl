#!/usr/bin/perl
#
# http://perlmaven.com/multi-dimensional-hashes
# http://perldoc.perl.org/perldsc.html#HASHES-OF-ARRAYS
# http://search.cpan.org/~jhi/Graph-0.9704/lib/Graph.pod
#
#
# Template:
# # ID::  HAP1-SDD-MCP-2700
# Classification::  REQT, INFO, TABLE, HEADING, FIGURE, DERIVED_REQT, RATIONALE
# RequirementType::  Operational, Safety, Functional, n/a, Flight, General
# ProblemReport::  
# IN::  HAP1-SDD-MCP-2738
#       HAP1-SDD-MCP-2830
#       HAP1-SDD-MCP-Z0Z0
#       HAP1-SDD-MCP-Z2Z2
# OUT:: HAP1-SSRD-MCP-750
# Description::
# The Actuator Management Module shall have the following public functions:
#
# Notes:
# REQTs need OUTs not necessarily INs
# Pseudo-code REQTs will have INs from source code
# Prototypes point up to SDD requirement that points to SSRD 
# INs are consumers of the requirement
# OUTs flow up to higher level requirement
#
#     out -> in     /------------->\
#   Code -> SDD -> SSRD -> SRD -> ARCH -> SYRD
#             \----------->/
#
use Data::Dumper; # qw(Dumper);
use Graph;

#print Dumper(%hash); # much better
#exit;
#foreach (sort keys %hash) {
#    print "$_ : $hash{$_}\n";
#}

%all_rqmts = {};
my $ID='ID::';
my $IN='IN::';
my $OUT='OUT::';
my $CLASS='Classification::';
my $DESC='Description::';
my $state = $ID;

my $id;
my $in;
my $out;
my $class;
my $desc;
my $g = Graph->new; # directed graph
sub filter
{
    my $ret = 0;
    @parms = @_;
    $line = $parms[0];
    if ($line =~ /$ID.*(HAP1-.*)/)  { $ret = 1; goto filter_out; }
    if ($line =~ /$OUT.*(HAP1-.*)/) { $ret = 1; goto filter_out; }
    if ($line =~ /$CLASS(.*)/)      { $ret = 1; goto filter_out; }
    if ($line =~ /$DESC(.*)/)       { $ret = 1; goto filter_out; }
filter_out:
    return $ret;
}

sub get_rqmts
{
    while (<>) {
top:
        if ($_ =~ /$ID.*(HAP1-.*)/)  { $id    = $1;  goto ids; }
        if ($_ =~ /$IN.*(HAP1-.*)/)  { $in    = $1;  goto ins; }
        if ($_ =~ /$OUT.*(HAP1-.*)/) { $out   = $1;  goto outs; }
        if ($_ =~ /$CLASS(.*)/)      { $class = $1;  goto class; }
        if ($_ =~ /$DESC(.*)/)       { $desc  = $1;  goto desc; }
        else { goto resume; }
ids:
        if (!exists($all_rqmts{$id})) {
            $all_rqmts{$id} = $id;
            $g->add_vertex($id);
        }
        goto resume;
ins:
        push @{ $all_rqmts{$id}{in} }, $in;
        $g->add_vertex($in);
        $g->add_edge($in, $id);
        while (<>) {
            if ($_ =~ /$ID.*(HAP1-.*)/)  { $id    = $1; goto ids; }
            if ($_ =~ /$OUT.*(HAP1-.*)/) { $out   = $1; goto outs; }
            if ($_ =~ /$CLASS(.*)/)      { $class = $1; goto class; }
            if ($_ =~ /$DESC(.*)/)       { $desc  = $1; goto desc; }
            if ($_ =~ /(HAP1-.*)/)       { $in    = $1; goto ins; }
            goto resume;
        }
outs:
        push @{ $all_rqmts{$id}{out} }, $out;
        $g->add_vertex($out);
        $g->add_edge($id, $out);
        while (<>) {
            if ($_ =~ /$ID.*(HAP1-.*)/) { $id    = $1; goto ids; }
            if ($_ =~ /$IN.*(HAP1-.*)/) { $in    = $1; goto ins; }
            if ($_ =~ /$CLASS(.*)/)     { $class = $1; goto class; }
            if ($_ =~ /$DESC(.*)/)      { $desc  = $1; goto desc; }
            if ($_ =~ /(HAP1-.*)/)      { $out   = $1; goto outs; }
            goto resume;
        }
class:
        push @{ $all_rqmts{$id}{class} }, $class;
        goto resume;
desc:
        push @{ $all_rqmts{$id}{desc} }, $desc;
        goto resume;
resume:
    }
}

sub show_rqmts
{
    print "\n\nshow requirements\n";
    foreach my $id (sort keys %all_rqmts) {
        print "\nID: $id ($all_rqmts{$id}{class}[0])\n";
        print "Description: $all_rqmts{$id}{desc}[0]\n";
        foreach my $in_out (keys %{ $all_rqmts{$id} }) {
            foreach $i ( 0 .. $#{ $all_rqmts{$id}{$in_out} } ) {
                if ($in_out eq "in") {
                    print "     IN[$i]: $all_rqmts{$id}{$in_out}[$i]\n";
                } elsif ($in_out eq "out") {
                    print "    OUT[$i]: $all_rqmts{$id}{$in_out}[$i]\n";
                }
            }
        }
        print "\n";
    }
    print "\n\nshow graph\n";
    if ($g) {
        #print "graph: $g\n";
        @u = $g->source_vertices();
        foreach $i ( 0 .. @u ) {
            print "SRC[$i]: @u[$i]\n";
        }
        @v = $g->sink_vertices();
        foreach $i ( 0 .. @v ) {
            print "SNK[$i]: @v[$i]\n";
        }
    }
}

get_rqmts;
show_rqmts;
exit;

