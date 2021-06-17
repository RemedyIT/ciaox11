#---------------------------------------------------------------------
# @file   run_test.pl
# @author Martin Corino
#
# @copyright Copyright (c) Remedy IT Expertise BV
#---------------------------------------------------------------------
eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# -*- perl -*-

use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::TestTarget;

my $status = 0;

my $receiver = PerlACE::TestTarget::create_target(2) || die "Create target 2 failed\n";
$receiver->AddLibPath ('../lib');

my $sender = PerlACE::TestTarget::create_target(3) || die "Create target 3 failed\n";
$sender->AddLibPath ('../lib');

$sender->DeleteFile ('TEST_MANUAL_EVENT');

my $RV = $receiver->CreateProcess ('../lib/receiver');
my $SR = $sender->CreateProcess ('../lib/sender');
my $receiver_status = $RV->Spawn ();

if ($receiver_status != 0) {
    print STDERR "ERROR: server returned $receiver_status\n";
    exit 1;
}

my $sender_status = $SR->Spawn ($sender->ProcessStartWaitInterval());

if ($sender_status != 0) {
    print STDERR "ERROR: sender returned $sender_status\n";
    $status = 1;
}

print "Waiting for Sender to complete\n";
while ($SR->TimedWait(1) == -1) {
}
$SR->Kill();

$receiver_status = $RV->WaitKill ($receiver->ProcessStopWaitInterval());

if ($receiver_status != 0) {
    print STDERR "ERROR: receiver returned $receiver_status\n";
    $status = 1;
}

$receiver->DeleteFile ('TEST_MANUAL_EVENT');

exit $status;
