Logging test with environment variables.

In this test logging macro's of CIAOX11 are used.
The priority mask determine which macro's are enabled .
The verbosity mask  determine the format of the output of the macro's .

Different settings of the priority masks and verbosity masks of CIAOX11_LOGGER are used
after each other.
For this the environment variables CIAOX11_LOG_MASK, X11_LOG_MASK, X11_VERBOSE and
CIAOX11_VERBOSE  are set in the script run_test.pl and the setter operations of the
priority_mask and verbosity_mask are used in the application self.
If X11_LOG_MASK and CIAOX11_LOG_MASK are set, CIAOX11_LOG_MASK overwrite the priority-mask set with X11_LOG_MASK.
If X11_VERBOSE and CIAOX11_VERBOSE are set, CIAOX11_VERBOSE overwrite the verbosity_mask set with X11_VERBOSE.
If in the application the setter operation are used, these will in turn overwrite the priority-mask
and verbosity-mask values again.

We check automatically the right output of the macro's in the script $TAOX11_ROOT/tao/x11/logger/log_check.pl
The script expected a blocks of code in a special order.  This is described in
$TAOX11_ROOT/tao/x11/logger/readme.txt
