#---------------------------------------------------------------------
# @file   run_test_sender.pl
# @author Martin Corino
#
# @copyright Copyright (c) Remedy IT Expertise BV
#---------------------------------------------------------------------
eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::TestTarget;

$TAO_ROOT = "$ENV{'TAO_ROOT'}";
$DANCEX11_ROOT = "$ENV{'DANCEX11_ROOT'}";
$DANCEX11_BIN_FOLDER = $ENV{'DANCEX11_BIN_FOLDER'} || 'bin';

$sleep_time = 5;

$nr_daemon = 1;
@ports = ( 60001 );
@iorbases = ( "Sender.ior" );
@nodenames = ( "SenderNode" );

$daemons_running = 0;
$em_r_running = 0;
$em_s_running = 0;

@iorfiles = 0;

# ior files other than daemon
$ior_sender_embase = "em_sender.ior";
$ior_sender_emfile = 0;

#  Processes
$E_S = 0;
$EM_S = 0;
@DEAMONS = 0;

# targets
@tg_daemons = 0;
$tg_naming = 0;
$tg_exe_man = 0;

$status = 0;

$plan_fmt = "config";

while ($i = shift) {
    if ($i eq '-fmt') {
        $plan_fmt = shift;
    }
}

$sender_plan_file = "plan_sender." . $plan_fmt;

sub create_targets {
    #   naming service
    $tg_naming = PerlACE::TestTarget::create_target (1) || die "Create target for ns failed\n";
    #   daemon
    for ($i = 0; $i < $nr_daemon; ++$i) {
        $tg_daemons[$i] = PerlACE::TestTarget::create_target ($i+3) || die "Create target for daemon $i failed\n";
        $tg_daemons[$i]->AddLibPath ('../lib');
    }
    #   execution manager
    $tg_exe_man = PerlACE::TestTarget::create_target (2) || die "Create target for EM failed\n";
}

sub init_ior_files {
    $ior_sender_emfile = $tg_exe_man->LocalFile ($ior_sender_embase);
    for ($i = 0; $i < $nr_daemon; ++$i) {
        $iorfiles[$i] = $tg_daemons[$i]->LocalFile ($iorbases[$i]);
    }
    delete_ior_files ();
}

# Delete if there are any .ior files.
sub delete_ior_files {
    for ($i = 0; $i < $nr_daemon; ++$i) {
        $tg_daemons[$i]->DeleteFile ($iorbases[$i]);
    }
    $tg_exe_man->DeleteFile ($ior_sender_embase);
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

    if ($em_s_running == 1) {
        $EM_S->Kill (); $EM_S->TimedWait (1);
    }

    # in case shutdown did not perform as expected
    for ($i = 0; $i < $nr_daemon; ++$i) {
      $tg_daemons[$i]->KillAll ('dancex11_deployment_manager');
    }
}

sub run_node_daemons {
    for ($i = 0; $i < $nr_daemon; ++$i) {
        $iorbase = $iorbases[$i];
        $iorfile = $iorfiles[$i];
        $port = $ports[$i];
        $nodename = $nodenames[$i];
        $dancex11_root = $tg_daemons[$i]->LocalEnvDir("$DANCEX11_ROOT");

        $d_cmd = "$DANCEX11_ROOT/$DANCEX11_BIN_FOLDER/dancex11_deployment_manager";
        $d_param = "--handler dancex11_node_dm_handler -p $port -ORBDottedDecimalAddresses 1 -n $nodename=$iorfile --deployment-nc ". $ENV{'NameServiceIOR'};

        print "Run dancex11_deployment_manager with $d_param\n";

        # Set up NamingService environment for node targets (for resolving corbaname references)
        $tg_daemons[$i]->SetEnv ('NameServiceIOR', $ENV{"NameServiceIOR"});

        $DEAMONS[$i] = $tg_daemons[$i]->CreateProcess ($d_cmd, $d_param);
        $DEAMONS[$i]->Spawn ();

        if ($tg_daemons[$i]->WaitForFileTimed($iorbase,
                                        $tg_daemons[$i]->ProcessStartWaitInterval ()) == -1) {
            print STDERR
                "ERROR: The ior $iorfile file of node daemon $i could not be found\n";
            for (; $i >= 0; --$i) {
                $DEAMONS[$i]->Kill (); $DEAMONS[$i]->TimedWait (1);
            }
            return -1;
        }
    }
    return 0;
}

create_targets ();
init_ior_files ();

$my_ip = $tg_naming->IP_Address ();

# Set up NamingService environment
$ENV{"NameServiceIOR"} = "corbaloc:iiop:$my_ip:60003/NameService";

print STDERR "Using Naming Service with at " . $ENV{"NameServiceIOR"} . "\n";

# Invoke node daemon.
print "Invoking node daemon\n";
$status = run_node_daemons ();

if ($status != 0) {
    print STDERR "ERROR: Unable to execute the node daemon\n";
    kill_open_processes ();
    exit 1;
}

$daemons_running = 1;

# Invoke execution manager to deploy sender.
print "Invoking domain deployment manager (dancex11_deployment_manager --handler dancex11_domain_dm_handler) with -l $sender_plan_file\n";
$EM_S = $tg_exe_man->CreateProcess ("$DANCEX11_ROOT/$DANCEX11_BIN_FOLDER/dancex11_deployment_manager",
                                  "--handler dancex11_domain_dm_handler -l " . $tg_exe_man->LocalFile($sender_plan_file) .
                                  " -n ExecutionManager=$ior_sender_emfile --deployment-nc " .
                                  $ENV{'NameServiceIOR'});
$em_status = $EM_S->Spawn ();

if ($em_status != 0) {
    print STDERR "ERROR: dancex11_deployment_manager returned $em_status";
    exit 1;
}

if ($tg_exe_man->WaitForFileTimed ($ior_sender_embase,
                                $tg_exe_man->ProcessStartWaitInterval ()) == -1) {
    print STDERR "ERROR: The ior file of execution manager could not be found\n";
    kill_open_processes ();
    exit 1;
}

$em_s_running = 1;

$corrected_sleep_time = $sleep_time * $PerlACE::Process::WAIT_DELAY_FACTOR;
print "Sleeping $corrected_sleep_time seconds to allow task to complete\n";
sleep ($corrected_sleep_time);

# Invoke executor manager - stop the sender application -.
print "Invoking executor - stop the sender application -\n";
print "by running dancex11_deployment_manager with -n ExecutionManager=$ior_sender_emfile -x\n";

$E_S = $tg_exe_man->CreateProcess ("$DANCEX11_ROOT/$DANCEX11_BIN_FOLDER/dancex11_deployment_manager",
                        "-n ExecutionManager=$ior_sender_emfile -x");
$pl_status = $E_S->SpawnWaitKill ($PerlACE::Process::WAIT_DELAY_FACTOR * $tg_exe_man->ProcessStartWaitInterval ());

if ($pl_status != 0) {
    print STDERR "ERROR: dancex11_deployment_manager returned $pl_status\n";
    kill_open_processes ();
    exit 1;
}
else {
    $EM_S->WaitKill ($tg_exe_man->ProcessStopWaitInterval ());
}

print "Executor returned.\n";
print "Shutting down rest of the processes.\n";

delete_ior_files ();
kill_open_processes ();

exit $status;
