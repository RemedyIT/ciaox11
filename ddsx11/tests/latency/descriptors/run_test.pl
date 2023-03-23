#---------------------------------------------------------------------
# @file   run_test.pl
# @author Martin Corino (mcorino@remedy.nl)
#
# @copyright Copyright (c) Remedy IT Expertise BV
#---------------------------------------------------------------------
eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# -*- perl -*-

use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::TestTarget;
use Getopt::Long;

my $status = 0;

sub print_help {
  my $fd = shift;
  print $fd "\n" .
    "run_test.pl [<options> ...]\n" .
    "\n" .
    "Executes test\n" .
    "\n" .
    "Options:\n" .
    "    --help | -h              Display this help\n" .

    "    --rate RATE              timer frequency in microseconds (default 100)\n" .
    "    --samples COUNT          number of samples to send each iteration (default 10000)\n" .
    "    --samplesize SIZE        size of sample to send (default 1024) in bytes\n" .
    "    --iterations COUNT       number of iterations to run (default 10)\n" .
    "    --domain ID              DDS Domain ID (default \$DDS4CCM_DEFAULT_DOMAIN_ID)\n" .
    "    --readall                read all available samples on data_available\n" .
    "    --readone                read a single sample at a time on data_available (default :readall)\n" .
    "    --chrt SCHEDULER         run using chrt with specified scheduler arg (fifo|rr|other)\n" .
    "    --prio PRIORITY          priority for chrt (default 0)\n\n";
}

# Parse Options
my $help = 0;
my $rate = '';
my $samples = '';
my $samplesize = '';
my $iterations = '';
my $domain_id = '';
my $readall = 0;
my $readone = 0;
my $chrt = '';
my $prio = '0';
my $chrt_cmd = '';
Getopt::Long::Configure('bundling', 'no_auto_abbrev');
my $invalid_arguments = !GetOptions(
    'help|h'       => \$help,
    'rate=s'       => \$rate,
    'samples=s'    => \$samples,
    'samplesize=s' => \$samplesize,
    'iterations=s' => \$iterations,
    'domain=s'     => \$domain_id,
    'readall'      => \$readall,
    'readone'      => \$readone,
    'chrt=s'       => \$chrt,
    'prio=s'       => \$prio
);
if ($invalid_arguments || $help) {
  print_help($invalid_arguments ? *STDERR : *STDOUT);
  exit($invalid_arguments ? 1 : 0);
}

if ($chrt ne '') {
  $chrt_cmd = qx(which chrt);
  $chrt_cmd = "$chrt_cmd";
  chomp($chrt_cmd);
}

my $receiver = PerlACE::TestTarget::create_target(2) || die "Create target 2 failed\n";
$receiver->AddLibPath ('../lib');

my $sender = PerlACE::TestTarget::create_target(3) || die "Create target 3 failed\n";
$sender->AddLibPath ('../lib');

$sender->DeleteFile ('TEST_MANUAL_EVENT');

my $cmd = '../lib/receiver';
my $cmdargs = '';
if ($chrt ne '') {
  $cmdargs = '--' . $chrt . ' ' . $prio . ' ' . $cmd;
  $cmd = $chrt_cmd;
}
if ($domain_id ne '') {
  $cmdargs .= " --domain $domain_id";
}
my $RV = $receiver->CreateProcess ($cmd, $cmdargs);
$cmd = '../lib/sender';
$cmdargs = '';
if ($chrt ne '') {
  $cmdargs = '--' . $chrt . ' ' . $prio . ' ' . $cmd;
  $cmd = $chrt_cmd;
}
if ($domain_id ne '') {
  $cmdargs .= " --domain $domain_id";
}
if ($rate ne '') {
  $cmdargs .= " --rate $rate";
}
if ($samples ne '') {
  $cmdargs .= " --samples $samples";
}
if ($samplesize ne '') {
  $cmdargs .= " --samplesize $samplesize";
}
if ($iterations ne '') {
  $cmdargs .= " --iterations $iterations";
}
if ($readall) {
  $cmdargs .= " --readall";
}
if ($readone) {
  $cmdargs .= " --readone";
}
my $SR = $sender->CreateProcess ($cmd, $cmdargs);
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
$SR->TimedWait(360);
$SR->Kill();

$receiver_status = $RV->WaitKill ($receiver->ProcessStopWaitInterval());

if ($receiver_status != 0) {
    print STDERR "ERROR: receiver returned $receiver_status\n";
    $status = 1;
}

$receiver->DeleteFile ('TEST_MANUAL_EVENT');

exit $status;
