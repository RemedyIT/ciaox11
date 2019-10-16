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

use File::Copy;
use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::TestTarget;

$TAO_ROOT = "$ENV{'TAO_ROOT'}";
$DANCEX11_ROOT = "$ENV{'DANCEX11_ROOT'}";
$DANCEX11_BIN_FOLDER = $ENV{'DANCEX11_BIN_FOLDER'} || 'bin';

$nr_daemon = 1;
@ports = ( 60001 );
@iorbases = ( 'Component.ior' );
@nodenames = ( 'ComponentNode' );

$daemons_running = 0;
$em_running = 0;
$ns_running = 0;

@iorfiles = 0;

# ior files other than daemon
$ior_nsbase = 'ns.ior';
$ior_nsfile = 0;
$ior_embase = 'em.ior';
$ior_emfile = 0;

#  Processes
$E = 0;
$EM = 0;
$NS = 0;
@DEAMONS = 0;

# targets
@tg_daemons = 0;
$tg_naming = 0;
$tg_domain_dep_man = 0;

$status = 0;

if (@ARGV != 3) {
    print STDERR "You need to invoke run_test.pl with <plan file> <incorrect qos file> <qos test input filename>\n";
    exit -1;
}

$plan_file = $ARGV[0];
$qos_file = $ARGV[1];
$test_input = $ARGV[2];

sub create_targets {
    #   naming service
    $tg_naming = PerlACE::TestTarget::create_target (1) || die "Create target for ns failed\n";

    #   daemon
    for ($i = 0; $i < $nr_daemon; ++$i) {
        $tg_daemons[$i] = PerlACE::TestTarget::create_target ($i+2) || die "Create target for daemon $i failed\n";
        $tg_daemons[$i]->AddLibPath ('../lib');
    }
    #   Domain Deployment Manager
    $tg_domain_dep_man = PerlACE::TestTarget::create_target (1) || die "Create target for Domain Deployment Manager failed\n";
}

sub init_ior_files {
    $ior_nsfile = $tg_naming->LocalFile ($ior_nsbase);
    $ior_emfile = $tg_domain_dep_man->LocalFile ($ior_embase);
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
    $tg_naming->DeleteFile ($ior_nsbase);
    $tg_domain_dep_man->DeleteFile ($ior_embase);
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

    if ($ns_running == 1) {
        $NS->Kill (); $NS->TimedWait (1);
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
        $d_param = "--handler dancex11_node_dm_handler -p $port " .
                   "-ORBDottedDecimalAddresses 1 -n $nodename=$iorfile " .
                   "--deployment-nc " . $ENV{'NameServiceIOR'};

        print "Run dancex11_deployment_manager with $d_param\n";

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

sub run_test {
    create_targets ();
    init_ior_files ();

    $my_ip = $tg_naming->IP_Address ();

    # Invoke naming service

    $NS = $tg_naming->CreateProcess ("$TAO_ROOT/orbsvcs/Naming_Service/tao_cosnaming",
                                    " -ORBEndpoint iiop://$my_ip:60003 -o $ior_nsfile");

    $ns_status = $NS->Spawn ();

    if ($ns_status != 0) {
        print STDERR "ERROR: Unable to execute the naming service\n";
        kill_open_processes ();
    }

    print STDERR "Starting Naming Service with  -ORBEndpoint iiop://$my_ip:60003 -o ns.ior\n";

    if ($tg_naming->WaitForFileTimed ($ior_nsbase,
                                      $tg_naming->ProcessStartWaitInterval ()) == -1) {
        print STDERR "ERROR: cannot find naming service IOR file\n";
        $NS->Kill (); $NS->TimedWait (1);
    }

    $ns_running = 1;
    # Set up NamingService environment
    $ENV{'NameServiceIOR'} = "corbaloc:iiop:$my_ip:60003/NameService";

    # Invoke node daemon.
    print "Invoking node daemon\n";
    $status = run_node_daemons ();

    if ($status != 0) {
        print STDERR "ERROR: Unable to execute the node daemon\n";
        kill_open_processes ();
    }

    $daemons_running = 1;

    # Invoke domain deployment manager.
    print "Invoking domain deployment manager " .
      "(dancex11_deployment_manager --handler dancex11_domain_dm_handler) with " .
      "-l $plan_file\n";

    $EM = $tg_domain_dep_man->CreateProcess ("$DANCEX11_ROOT/$DANCEX11_BIN_FOLDER/dancex11_deployment_manager",
                                      "--handler dancex11_domain_dm_handler -l " . $tg_domain_dep_man->LocalFile($plan_file) .
                                      " -n ExecutionManager=$ior_emfile --deployment-nc " .
                                      $ENV{'NameServiceIOR'});
    $em_status = $EM->SpawnWaitKill ($tg_domain_dep_man->ProcessStartWaitInterval ());

    delete_ior_files ();
    kill_open_processes ();
    print "\n\n";
}

sub check_output {
    $found_start = 0;
    $found_internal = 0;
    open FILE, "<output";
    while (my $line = <FILE>)
    {
      #print $line;
      if ($line =~ 'StartError')
      {
        $found_start = 1;
      }
      if ($line =~ 'INTERNAL')
      {
        $found_internal = 1;
      }
    }
    close FILE;
    if ($found_start == 0 || $found_internal == 0) {
        print "ERROR: Incorrect output found.\n";
        open FILE, "<output";
        while (my $line = <FILE>)
        {
          print $line;
        }
        close FILE;
    }
    else {
        print "OK: Correct output found.\n"
    }
}

sub go {
    #Redirect the screen output to the null device.
    open (OLDOUT, ">&STDOUT");
    open (STDOUT, ">" . output);
    open (OLDERR, ">&STDERR");
    open (STDERR, ">&STDOUT");

    # run the test
    run_test ();

    # Redirect the null device output back to the screen
    open (STDOUT, ">&OLDOUT");
    open (STDERR, ">&OLDERR");

    check_output ();
}


print "Copy $qos_file to $test_input used by DDS\n";

# Copy the qos file to the file the DDS vendor will use
copy($qos_file, $test_input) or die "The copy operation failed: $!";

print "Run the test with a wrong QoS profile string\n";

go ();

exit $status;
