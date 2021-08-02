
echo "Start @ $(date)"
brix11 run test -- --chrt fifo --prio 90 plan_ndds_exf.config >dds4ccm-fifo-latency-exf.txt 2>&1
echo "End @ $(date)"
