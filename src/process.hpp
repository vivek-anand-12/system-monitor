#pragma once

#include <string>
#include <vector>

/**
 * ProcessInfo: holds parsed per-process data read from /proc/<pid>
 */
struct ProcessInfo {
    int pid;
    std::string name;
    unsigned long long utime_ticks; // user time (clock ticks)
    unsigned long long stime_ticks; // system time (clock ticks)
    unsigned long long total_time_ticks() const { return utime_ticks + stime_ticks; }
    long rss_kb; // resident set size in KB
    double cpu_percent;
    double mem_percent;
};

/**
 * Read process info for pid into p.
 * Returns true if the process info was successfully read (process exists and files parse).
 */
bool read_process_info(int pid, ProcessInfo &p);

/**
 * List numeric PIDs under /proc.
 * Returns vector of ints (pids).
 */
std::vector<int> list_pids();