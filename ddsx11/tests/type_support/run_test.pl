#---------------------------------------------------------------------
# @file   run_test.pl
# @author Marcel Smit
#
# @copyright Copyright (c) Remedy IT Expertise BV
#---------------------------------------------------------------------
eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# -*- perl -*-

use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::TestTarget;

my $program = PerlACE::TestTarget::create_target (2) || die "Create target 2 failed\n";

$PROG = $program->CreateProcess ("typesupport_test", "");
$program_status = $PROG->SpawnWaitKill ($program->ProcessStartWaitInterval());

if ($program_status != 0) {
    print STDERR "ERROR: typesupport_test returned $program_status\n";
    exit 1;
}

$exit_status = $PROG->WaitKill ($program->ProcessStopWaitInterval());

if ($exit_status != 0) {
    print STDERR "ERROR: typesupport_test returned $exit_status\n";
    exit 1;
}

exit 0;
