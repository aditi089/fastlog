# Task 2: Log Analysis & Performance Profiling 

Welcome to the **Task 2** directory! This phase focuses on extracting meaningful metrics from log files and deeply understanding the real-world performance of our code. 

The primary goal of this task is to build a strong intuition for how fast or slow our C++ code actually runs, especially when dealing with large datasets (100MB and 1GB files).

##  Objectives

This task is divided into three main components: Collaboration, Data Analysis, and Performance Measurement.

### 1. Collaboration & Code Sharing
- All individual codes from the team ("DC") are stored in their respective subfolders within this directory.
- **Peer Review:** Everyone is encouraged to go through each other's code, learn different approaches, and update their own code if they find better optimizations.

### 2. Log Analytics Implementation
After successfully reading and storing the logs in memory, the following analytical functions must be implemented:
1. **Count per Log Level:** Calculate the total occurrences of each log level (e.g., INFO, WARN, ERROR, DEBUG).
2. **Average Latency:** Compute the mean latency across all logged requests/events.
3. **Top 10 Users by Activity:** Identify and rank the top 10 users who generated the most log entries.
4. **95th Percentile Latency:** Calculate the latency value that 95% of the logs fall strictly below.

### 3. Performance Measurement (`std::chrono`)
To understand our code's efficiency, we must measure the time taken to execute the program against large files.
- **Test Datasets:** Run the program against **100MB** and **1GB** log files.
- **Benchmarking:** Measure and print the exact time taken for:
  - `Reading Time` (File I/O)
  - `Processing Time` (Computing the analytics)
- *Note: These two times must be calculated and printed separately.*
