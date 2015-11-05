#!/usr/bin/perl


$filename = $ARGV[0];

open(FILE1,"$filename");

@lines=<FILE1>;
close(FILE1);



foreach $line(@lines) {
	chomp($line);

	
	$cmd="./fullyExtended -blaPDB ${line}";
	
	system($cmd);
	
	$cmd1="./fullyExtended -hhsearch ${line}";
	
	system($cmd1);
	
}
