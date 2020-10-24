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

$program->SetEnv ("X11_LOG_OUTPUT", "FILE=output,,,T");
$program->SetEnv ("TZ", "GMT");

$PROG = $program->CreateProcess ("ddsx11_log_formatters_test", "");
$program_status = $PROG->SpawnWaitKill ($program->ProcessStartWaitInterval());

if ($program_status != 0) {
    print STDERR "ERROR: log_formatters_test returned $program_status\n";
    exit 1;
}

$exit_status = $PROG->WaitKill ($program->ProcessStopWaitInterval());

if ($exit_status != 0) {
    print STDERR "ERROR: log_formatters_test returned $exit_status\n";
    exit 1;
}

if ($program->GetFile ('output.log') == -1) {
    print STDERR "ERROR: cannot retrieve file <output.log>\n";
    exit 1;
}
$log_test_res = system("perl log_check.pl output.log");
if ($log_test_res != 0) {
    print STDERR "ERROR: log_check returned $log_test_res\n";
    exit 1;
}

exit 0;
