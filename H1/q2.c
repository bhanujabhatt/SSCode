/*
=======================================================================================================================================================================================
Name : handsonprog2.c
Author : Bhanuja Bhatt
Description : Write a simple program to execute in an infinite loop at the background. 
	      Go to /proc directory and identify all the process related information in the corresponding proc directory.
Date: 15th Aug, 2024
Sample Output:pid=101022
arch_status  cgroup      coredump_filter     environ  gid_map            limits     mem         net        oom_score      personality  schedstat  smaps_rollup  status          timers
attr         clear_refs  cpu_resctrl_groups  exe      io                 loginuid   mountinfo   ns         oom_score_adj  projid_map   sessionid  stack         syscall         timerslack_ns
autogroup    cmdline     cpuset              fd       ksm_merging_pages  map_files  mounts      numa_maps  pagemap        root         setgroups  stat          task            uid_map
auxv         comm        cwd                 fdinfo   ksm_stat           maps       mountstats  oom_adj    patch_state    sched        smaps      statm         timens_offsets  wchan

==============================================================================================================================================================================================
*/
#include<stdio.h>

int main(){
	for(;;){}
}
