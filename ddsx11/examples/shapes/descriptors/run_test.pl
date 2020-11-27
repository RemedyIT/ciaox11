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

my $receiver = PerlACE::TestTarget::create_target(2) || die "Create target 2 failed\n";
$receiver->AddLibPath ('../lib');

my $sender = PerlACE::TestTarget::create_target(3) || die "Create target 3 failed\n";
$sender->AddLibPath ('../lib');

my $RV = $receiver->CreateProcess ('../lib/receiver', "$corrected_sleep_time");
my $SR = $sender->CreateProcess ('../lib/sender');
my $receiver_status = $RV->Spawn ();

if ($receiver_status != 0) {
    print STDERR "ERROR: server returned $receiver_status\n";
    exit 1;
}

my $sender_status = $SR->SpawnWaitKill ($sender->ProcessStartWaitInterval());

if ($sender_status != 0) {
    print STDERR "ERROR: sender returned $sender_status\n";
    $status = 1;
}

print "Sleeping $corrected_sleep_time seconds to allow task to complete\n";
sleep ($corrected_sleep_time);

$receiver_status = $RV->WaitKill ($receiver->ProcessStopWaitInterval());

if ($receiver_status != 0) {
    print STDERR "ERROR: receiver returned $receiver_status\n";
    $status = 1;
}

exit $status;
