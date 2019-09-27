#---------------------------------------------------------------------
# @file   run_test_snl.pl
# @author Martin Corino
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#---------------------------------------------------------------------
eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::TestTarget;
use File::Basename;

$TAO_ROOT = "$ENV{'TAO_ROOT'}";
$DANCEX11_ROOT = "$ENV{'DANCEX11_ROOT'}";
$DANCEX11_BIN_FOLDER = $ENV{'DANCEX11_BIN_FOLDER'} || 'bin';

$daemons_running = 0;

$sleep_time = 15;

$nr_daemon = 2;
@ports = ( 60001, 60002 );
@nodenames = ( 'SenderNode', 'ReceiverNode' );

#  Processes
$SP = 0;
@DEAMONS = 0;

# targets
@tg_daemons = 0;
$tg_splitter = 0;

$status = 0;

if ($#ARGV == -1) {
    opendir(DIR, ".");
    @files = grep(/\.(cdp|config)$/,readdir(DIR));
    closedir(DIR);
}
else {
    @files = @ARGV;
}

sub create_targets {
    #   daemon
    for ($i = 0; $i < $nr_daemon; ++$i) {
        $tg_daemons[$i] = PerlACE::TestTarget::create_target ($i+2) || die "Create target for daemon $i failed\n";
        $tg_daemons[$i]->AddLibPath ('../lib');
    }
    #   splitter (split_plan)
    $tg_splitter = PerlACE::TestTarget::create_target (1) || die "Create target for splitter failed\n";
}

sub kill_node_daemon {
    for ($i = 0; $i < $nr_daemon; ++$i) {
        $DEAMONS[$i]->Kill (); $DEAMONS[$i]->TimedWait (1);
    }
}

sub kill_open_processes {
    if ($daemons_running == 1) {
        kill_node_daemon ();
    }

    # in case shutdown did not perform as expected
    for ($i = 0; $i < $nr_daemon; ++$i) {
      $tg_daemons[$i]->KillAll ('dancex11_deployment_manager');
    }
}

sub run_node_daemons($) {
    my $filename = shift;
    for ($i = 0; $i < $nr_daemon; ++$i) {
        $port = $ports[$i];
        $nodename = $nodenames[$i];
        $dancex11_root = $tg_daemons[$i]->LocalEnvDir("$DANCEX11_ROOT");

        $d_cmd = "$DANCEX11_ROOT/$DANCEX11_BIN_FOLDER/dancex11_deployment_manager";
        $d_param = '';
        if ($plan_fmt eq 'cdp') {
            $d_param = "-c $dancex11_root/bin/nodemanager_with_cdp.config ";
        }
        $d_param = $d_param . "--handler dancex11_node_dm_handler -p $port -f cdr -l $nodename" . "-" . $filename . '.cdr';

        print "Run dancex11_deployment_manager with $d_param\n";

        $DEAMONS[$i] = $tg_daemons[$i]->CreateProcess ($d_cmd, $d_param);
        $tg_status = $DEAMONS[$i]->Spawn ();

        if ($tg_status != 0) {
            print STDERR "ERROR: Unable to execute the dancex11_deployment_manager $d_param\n";
            return -1;
        }
    }
    return 0;
}

sub stop_node_daemons {
    for ($i = 0; $i < $nr_daemon; ++$i) {
        $port = $ports[$i];
        $nodename = $nodenames[$i];

        $d_cmd = "$DANCEX11_ROOT/$DANCEX11_BIN_FOLDER/dancex11_deployment_manager";
        $d_param = "-p $port -x";

        print "Run dancex11_deployment_manager with $d_param\n";

        $node_stopper = $tg_daemons[$i]->CreateProcess ($d_cmd, $d_param);
        $tg_status = $node_stopper->SpawnWaitKill (
                $PerlACE::Process::WAIT_DELAY_FACTOR * $tg_daemons[$i]->ProcessStartWaitInterval ());

        if ($tg_status != 0) {
            print STDERR "ERROR: Unable to execute the dancex11_deployment_manager $d_param\n";
            return -1;
        }
    }
    return 0;
}

foreach $file (@files) {
    if ($file =~ /NoFailure/) {
      next;
    }

    ($filename,$dir,$ext) = fileparse($file, qr/\.[^.]*/);

    create_targets ();

    # Invoke plan splitter.
    print "Invoking $DANCEX11_ROOT/$DANCEX11_BIN_FOLDER/dancex11_split_plan with -i ". $tg_splitter->LocalFile ($file) . "\n";

    $SP = $tg_splitter->CreateProcess ("$DANCEX11_ROOT/$DANCEX11_BIN_FOLDER/dancex11_split_plan", "-i ". $tg_splitter->LocalFile ($file));
    $sp_status = $SP->SpawnWaitKill ($PerlACE::Process::WAIT_DELAY_FACTOR * $tg_splitter->ProcessStartWaitInterval ());

    if ($sp_status != 0) {
        print STDERR "ERROR: Unable to execute dancex11_split_plan\n";
        kill_open_processes ();
        exit 1;
    }

    if ($tg_splitter->WaitForFileTimed ($nodenames[0]."-".$filename . '.cdr',
                                        $tg_splitter->ProcessStartWaitInterval ()) == -1) {
        print STDERR
          "ERROR: The split node plan could not be found\n";
        kill_open_processes ();
        exit 1;
    }

    # copy split subplans to nodes
    for ($i = 0; $i < $nr_daemon; ++$i) {
        $tg_splitter->GetFile ($nodenames[$i]."-".$filename . '.cdr');
        $tg_daemons[$i]->PutFile ($nodenames[$i]."-".$filename . '.cdr');
    }

    # Launch nodes.
    print "Launching nodes\n";
    $status = run_node_daemons ($filename);

    if ($status != 0) {
        print STDERR "ERROR: Unable to execute the node daemon\n";
        kill_open_processes ();
        exit 1;
    }

    $daemons_running = 1;

    $corrected_sleep_time = ($sleep_time * $PerlACE::Process::WAIT_DELAY_FACTOR) + $tg_daemons[0]->ProcessStartWaitInterval ();
    print "Sleeping $corrected_sleep_time seconds to allow task to complete\n";
    sleep ($corrected_sleep_time);

    # Stop nodes.
    print "Stopping nodes\n";
    $status = stop_node_daemons ();

    print "Shutting down rest of the processes.\n";

    kill_open_processes ();
}

exit $status;
