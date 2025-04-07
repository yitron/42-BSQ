#!/usr/bin/perl
use warnings;
use strict;

# Check arguments
die "Usage: $0 x y density\n" unless scalar(@ARGV) == 3;

# Assign arguments
my ($x, $y, $density) = @ARGV;

# Define filename
my $filename = "${x}x${y}_${density}.map";

# Open file for writing
open(my $fh, '>', $filename) or die "Cannot open $filename: $!";

# Write map header
print $fh "$y.ox\n";

# Generate map
for (my $i = 0; $i < $y; $i++) {
    for (my $j = 0; $j < $x; $j++) {
        if (int(rand($y) * 2) < $density) {
            print $fh "o";
        } else {
            print $fh ".";
        }
    }
    print $fh "\n";
}

close $fh;
print "Map written to $filename\n";

