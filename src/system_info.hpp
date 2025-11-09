#pragma once
#include "process.hpp"
#include <vector>

/**
 * SystemInfo handles reading of /proc and computing CPU/memory usage.
 */
class SystemInfo {
public:
    SystemInfo();
    ~SystemInfo() = default;

    // update internal samples (should be called periodically)
    void sample();

    // get current process list (after last sample)
    std::vector<ProcessInfo> processes() const;

    // total CPU percent (0-100)
    double total_cpu_percent() const;

    // total memory percent (0-100)
    double total_mem_percent() const;

private:
    // helpers
    unsigned long long read_total_cpu_ticks() const;
    unsigned long long last_total_cpu_ticks;
    unsigned long long last_idle_ticks;
    unsigned long long last_sample_time_ms;

    double total_cpu_pct;
    double total_mem_pct;

    unsigned long long mem_total_kb;
    std::vector<ProcessInfo> proc_list;

    void update_mem_total();
};
