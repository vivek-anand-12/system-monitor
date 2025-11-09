# 🖥️ System Monitor

A lightweight **C++ system monitoring tool** that provides real-time insights into CPU usage, memory consumption, running processes, and other system metrics.  
Built with **modern C++**, **CMake**, and optional **Docker** support for easy deployment.

---

## 📂 Project Structure

```
system-monitor/
├── CMakeLists.txt        # Build configuration
├── Makefile              # Alternative build script
├── Dockerfile            # Containerization setup
├── src/                  # Source code
│   ├── main.cpp
│   ├── system_info.cpp / .hpp
│   ├── process.cpp / .hpp
│   ├── utils.cpp / .hpp
├── include/              # Header files (if used separately)
├── bin/                  # Compiled executables
├── screenshots/          # Optional screenshots or UI demos
└── README.md             # Project documentation
```

---

## ⚙️ Features

- 🧠 Fetches real-time CPU and memory usage  
- 🧾 Lists and monitors active processes  
- 🧮 Calculates system load averages  
- ⚡ Fast and lightweight (no external dependencies besides STL)  
- 🐳 Optional Docker image for containerized monitoring  

---

## 🚀 Getting Started

### 1️⃣ Prerequisites
- **C++17** or later  
- **CMake ≥ 3.10**  
- **g++ / clang** compiler  
- *(Optional)* Docker installed

---

### 2️⃣ Build and Run (CMake)

```bash
git clone https://github.com/yourusername/system-monitor.git
cd system-monitor/system-monitor
mkdir build && cd build
cmake ..
make
./bin/system-monitor
```

---

### 3️⃣ Build and Run (Makefile)

```bash
cd system-monitor/system-monitor
make
./bin/system-monitor
```

---

### 4️⃣ Run with Docker

```bash
docker build -t system-monitor .
docker run --rm -it system-monitor
```

---

## 🧩 Code Overview

| File | Description |
|------|--------------|
| `main.cpp` | Entry point of the program |
| `system_info.cpp/hpp` | Gathers system metrics (CPU, memory, etc.) |
| `process.cpp/hpp` | Retrieves process information |
| `utils.cpp/hpp` | Utility and helper functions |

---

## 🖼️ Screenshots

![System Monitor Preview](./screenshots/1.jpg)

---

## 🧰 Future Enhancements

- [ ] Add network usage monitoring  
- [ ] Support JSON/CSV data export  
- [ ] Add web dashboard frontend  
- [ ] Windows and macOS support  

---

## 👨‍💻 Author

**Vivek Anand**  
🔗 [GitHub](https://github.com/vivek-anand-12) 

---


> ⚡ *System Monitor — Simple, fast, and efficient insight into your system’s heartbeat.*
