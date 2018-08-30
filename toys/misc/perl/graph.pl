#!/usr/bin/perl

use Graph;

# http://search.cpan.org/~jhi/Graph-0.9704/lib/Graph.pod
# cpan get Graph
# cpan install Graph


my $g = Graph->new;             # A directed graph.

$u = "dude";
$v = "rad";
$x = "cindy";
$y = "bart";
#$g->add_vertex($u);
#$g->add_vertex($v);
#$g->add_vertex($x);
#$g->add_vertex($y);
$g->add_edge($u, $v);
$g->add_edge($u, $x);
$g->add_edge($v, $y);

if ($g) { print "The graph is: $g\n" }
@u = $g->source_vertices();
@v = $g->sink_vertices();
print "sources: @u\n";
print "sinks: @v\n";
@verts = $g->vertices;
@n = $g->all_neighbours(@u);
print "source neighbors: @n\n";
@n = $g->all_neighbours(@v);
print "sink neighbors: @n\n";


