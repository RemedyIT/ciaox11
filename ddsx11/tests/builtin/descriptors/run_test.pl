#---------------------------------------------------------------------
# @file   run_test.pl
# @author Johnny Willemsen
#
# @copyright Copyright (c) Remedy IT Expertise BV
#---------------------------------------------------------------------
eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# -*- perl -*-

use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::TestTarget;

$sleep_time = 10;
$corrected_sleep_time = $sleep_time * $PerlACE::Process::WAIT_DELAY_FACTOR;

my $status = 0;

my $builtin = PerlACE::TestTarget::create_target(2) || die "Create target 2 failed\n";
$builtin->AddLibPath ('../lib');

# Test builtin
print "Running builtin test\n";
$SV = $builtin->CreateProcess ("../lib/builtin");
$builtin_status = $SV->SpawnWaitKill ($builtin->ProcessStartWaitInterval());
if ($builtin_status != 0) {
    print STDERR "ERROR: builtin returned $builtin_status\n";
    exit 1;
}

# Test dpf_sdqwp
print "Running dpf_sdqwp test\n";
$SV = $builtin->CreateProcess ("../lib/dpf_sdqwp");
$builtin_status = $SV->SpawnWaitKill ($builtin->ProcessStartWaitInterval());
if ($builtin_status != 0) {
    print STDERR "ERROR: dpf_sdqwp returned $builtin_status\n";
    exit 1;
}

# Test double_delete
print "Running double_delete test\n";
$SV = $builtin->CreateProcess ("../lib/double_delete");
$builtin_status = $SV->SpawnWaitKill ($builtin->ProcessStartWaitInterval());
if ($builtin_status != 0) {
    print STDERR "ERROR: double_delete returned $builtin_status\n";
    exit 1;
}

exit $status;
