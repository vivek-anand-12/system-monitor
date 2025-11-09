// src/main.cpp
// System Monitor - main
// Provides a simple console UI to display process info and system usage.

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <csignal>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>    // select()
#include <sys/types.h>
#include <sys/time.h>

#include <iomanip>         // setw, setprecision, left, fixed
#include <algorithm>       // sort

#include "system_info.hpp"
#include "process.hpp"

using namespace std;

static struct termios orig_termios;
void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON); // no echo, non-canonical
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

volatile sig_atomic_t stop_requested = 0;
void handle_sigint(int) { stop_requested = 1; }

void clear_screen() {
    // ANSI clear
    cout << "\033[2J\033[H";
}

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string sort_mode = "cpu"; // or "mem"
    int refresh_ms = 2000;

    // parse args: --sort=cpu|mem  --interval=ms
    for (int i=1;i<argc;i++){
        string a(argv[i]);
        if (a.rfind("--sort=",0)==0) sort_mode = a.substr(7);
        if (a.rfind("--interval=",0)==0) refresh_ms = stoi(a.substr(11));
    }

    signal(SIGINT, handle_sigint);
    enable_raw_mode();

    SystemInfo sys;
    // initial sample
    sys.sample();

    while (!stop_requested) {
        auto start = chrono::steady_clock::now();
        sys.sample();

        clear_screen();
        cout << "System Monitor Tool (C++) — Sort by [" << sort_mode << "]  |  Press 'c' to sort by CPU, 'm' by MEM, 'q' to quit\n";
        cout << "Total CPU: " << fixed << setprecision(2) << sys.total_cpu_percent() << "%   ";
        cout << "Total MEM: " << fixed << setprecision(2) << sys.total_mem_percent() << "%\n";
        cout << "---------------------------------------------------------------------------\n";
        cout << left << setw(8) << "PID" << setw(24) << "NAME" << setw(10) << "CPU%" << setw(10) << "MEM%" << setw(12) << "RSS(kB)" << "\n";
        cout << "---------------------------------------------------------------------------\n";

        vector<ProcessInfo> procs = sys.processes();
        if (sort_mode == "cpu") {
            sort(procs.begin(), procs.end(), [](const ProcessInfo &a, const ProcessInfo &b){
                return a.cpu_percent > b.cpu_percent;
            });
        } else {
            sort(procs.begin(), procs.end(), [](const ProcessInfo &a, const ProcessInfo &b){
                return a.mem_percent > b.mem_percent;
            });
        }

        int displayed = 0;
        for (const auto &p : procs) {
            if (displayed++ >= 30) break; // show top 30
            cout << setw(8) << p.pid
                 << setw(24) << (p.name.size() > 22 ? p.name.substr(0,21) + "…" : p.name)
                 << setw(10) << fixed << setprecision(2) << p.cpu_percent
                 << setw(10) << fixed << setprecision(2) << p.mem_percent
                 << setw(12) << p.rss_kb << "\n";
        }
        cout << "---------------------------------------------------------------------------\n";
        cout << "Controls: c=CPU sort | m=MEM sort | q=quit\n";

        // non-blocking check stdin for key
        fd_set set;
        struct timeval tv;
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        int rv = select(STDIN_FILENO+1, &set, NULL, NULL, &tv);
        if (rv > 0 && FD_ISSET(STDIN_FILENO, &set)) {
            char ch;
            if (read(STDIN_FILENO, &ch, 1) > 0) {
                if (ch == 'q') break;
                else if (ch == 'c') sort_mode = "cpu";
                else if (ch == 'm') sort_mode = "mem";
            }
        }

        auto elapsed = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count();
        int to_sleep = refresh_ms - (int)elapsed;
        if (to_sleep > 0) this_thread::sleep_for(chrono::milliseconds(to_sleep));
    }

    disable_raw_mode();
  cout << "\nExisting system monitor\n";
  return 0;
}