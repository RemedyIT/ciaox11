#---------------------------------------------------------------------
# @file   log_check.pl
# @author Marcel Smit
#
# @copyright Copyright (c) Remedy IT Expertise BV
#---------------------------------------------------------------------
eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# -*- perl -*-

$status = 0;

$found = 0;
$expected = 6;

sub check_readinfo
{
    my $line = shift;
    print $line;
    if ($line =~ "0X10203,0X4050607,0X8090A0B,0XC0D0E0F" &&
        $line =~ /1970-01-01 0[0-9]:00:16/ &&
        $line =~ "FRESH_INFO" &&
        $line =~ "INSTANCE_FILTERED_IN")
    {
      return 1;
    }
  return 0;
}

print "Log output:\n";
print ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
open (FILE, "<", @ARGV[0]);
while (my $line = <FILE>)
{
    print $line;
    if ($line =~ "Logging AccessStatus")
    {
        if ($line =~ "ALREADY_SEEN")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in AccessStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging InstanceStatus")
    {
        if ($line =~ "INSTANCE_UPDATED")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in InstanceStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging ReadInfoSeq")
    {
        $start_found = $found;
        $found=$found+check_readinfo($line);
        $found=$found+check_readinfo($line);
        $found=$found+check_readinfo($line);
        if ($start_found+3 != $found)
        {
            print "ERROR: Error in ReadInfoSeq logging detected\n";
        }
    }
    elsif ($line =~ "Logging ReadInfo") # AFTER ReadInfoSeq
    {
        $start_found = $found;
        $found=$found+check_readinfo($line);
        if ($start_found+1 != $found)
        {
            print "ERROR: Error in ReadInfoSeq logging detected\n";
        }
    }
}
print "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";

print "\nExpected to find <$expected> - found <$found>\n";
if ($found == $expected) {
    print "OK: Found all expected keywords in the log output.\n"
} else {
    print "ERROR: Expected to find <$expected> keywords but found <$found> keywords.\n";
    $status = 1;
}

exit $status;
