# Use official Ubuntu LTS
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y build-essential g++ cmake git procps && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /opt/system-monitor

# Copy project
COPY . /opt/system-monitor

# Build
RUN mkdir -p build && cd build && cmake .. && make

# Default command runs binary with TTY-friendly settings
ENTRYPOINT ["/opt/system-monitor/build/system-monitor"]
