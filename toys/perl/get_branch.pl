#!/usr/bin/perl

# <Exec Command="svn info | findstr -is URL &gt; Resources\BuildInfo.txt" />

$cmd = "svn info";
@output = `$cmd`;
$owner  = "";
$branch = "";
$url    = "";
$full   = "";
foreach (@output) { 
    if ($_ =~ /URL: (http:\/\/subversion.helitrak.com\/svn\/HAP1-CERT\/branches)\/([a-zA-Z0-9]+)\/([a-zA-Z0-9]+)/ig)  { 
        $url = $1; $owner = $2;  $branch = $3; $full = $_; 
    }
} 
$full = "$url/$owner/$branch";
#print "url: $url, owner: $owner, branch: $branch\n";
print "$full\n";

