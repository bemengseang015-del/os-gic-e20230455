# OS Class Activity 3: Socket Communication & Multithreading

**Student Name:** Mengseang  
**Student ID:** e20230455  
**Course:** Operating Systems  
**Date:** November 16, 2026

---

## 1. Objectives

- Understand TCP socket communication between a client and a server.
- Create and manage threads using POSIX threads in C.
- Understand race conditions and synchronization using mutexes.
- Implement Java multithreading using Thread, Runnable, and ExecutorService.
- Observe user threads and kernel threads in Linux and Windows.
- Understand how operating systems manage concurrent execution.

---

## 2. Task 1: TCP Socket Communication in C

### 2.1 Implementation

Created two C programs:

- `task1_socket/server.c`
- `task1_socket/client.c`

The server uses the following socket functions:

1. `socket()` creates a socket.
2. `setsockopt()` configures socket options.
3. `bind()` assigns an IP address and port.
4. `listen()` waits for incoming connections.
5. `accept()` accepts a client connection.
6. `read()` receives data from the client.
7. `send()` sends a response.
8. `close()` closes the socket.

The client uses `socket()`, `inet_pton()`, `connect()`, `send()`, `read()`, and `close()` to communicate with the server.

### 2.2 Compilation and Execution

The programs were compiled using GCC:

```bash
gcc -Wall -Wextra -o server server.c
gcc -Wall -Wextra -o client client.c
```

The server and client were executed in separate terminals.

**Port configuration:** Port 8080 was already occupied by another service on the shared Linux server. Port 8081 was therefore used for the successful communication test.

### 2.3 Execution Result

The client successfully sent a message to the server, and the server returned a response.

```text
Client: Hello from client!
Server: Hello from server!
```

Detailed output is saved in:

- `task1_socket/result_socket.txt`
- `task1_socket/command_used_socket.txt`

### 2.4 Questions and Answers

**Q1. What is the purpose of `bind()`?**

`bind()` assigns a local IP address and port number to a socket. It allows the server to listen for incoming connections at a specific address.

**Q2. What is the purpose of `accept()`?**

`accept()` waits for an incoming client connection and returns a new socket file descriptor for communicating with that client. The original listening socket remains available.

**Q3. What happens if the client connects before the server starts?**

The connection normally fails because no server is listening at the specified address and port. The client usually receives a connection-refused error.

**Q4. Why do we use `htons()`?**

`htons()` means Host To Network Short. It converts a 16-bit integer from host byte order to network byte order, which uses big-endian format.

**Q5. Describe the TCP communication sequence.**

Server: `socket()` → `bind()` → `listen()` → `accept()` → `read()/send()` → `close()`.

Client: `socket()` → `connect()` → `send()/read()` → `close()`.

---
## 3. Task 2: POSIX Threads in C

### 3.1 Creating Threads and Observing a Race Condition

The file `task2_threads/threads.c` creates four worker threads.

Each thread increments a shared global counter 100,000 times.

The expected final counter is:

```text
Expected counter: 400000
```

One observed execution produced:

```text
Expected counter: 400000
Actual counter: 124051
```

Other executions also produced different actual values.

This happens because multiple threads access and modify the shared counter without synchronization. Some increments are lost when threads execute their operations concurrently.

This demonstrates a race condition.

**Note:** A data race in C is undefined behavior, so the exact result is not guaranteed.

### 3.2 Synchronization Using a Mutex

The file `task2_threads/threads_mutex.c` uses a mutex to protect the shared counter.

Compilation:

```bash
gcc -Wall -Wextra -o threads_mutex threads_mutex.c -pthread
```

Example result:

```text
Expected counter: 400000
Actual counter: 400000
```

The mutex ensures that only one thread at a time can enter the critical section that updates the counter.

### 3.3 Observing Threads in Linux

The file `task2_threads/threads_observe.c` creates four worker threads and keeps them active for observation.

The process contains:

- One main thread.
- Four worker threads.
- Five threads in total.

Linux commands used:

```bash
ps -eLf
ps -T -p PID
cat /proc/PID/status
ls /proc/PID/task/
```

The observed process showed:

```text
Threads: 5
```

Five thread ID directories were also observed under `/proc/PID/task/`.

### 3.4 Questions and Answers

**Q1. What is a race condition?**

A race condition occurs when multiple threads access shared data concurrently and the final result depends on their execution order. Without synchronization, some updates may be lost.

**Q2. What is the purpose of pthread_mutex_lock() and pthread_mutex_unlock()?**

`pthread_mutex_lock()` acquires the mutex and protects the critical section. `pthread_mutex_unlock()` releases the mutex so another thread can access the protected section.

**Q3. What happens if pthread_join() is not used?**

The main thread may finish before worker threads complete. If the process terminates, its remaining threads are also terminated.

**Q4. What is the difference between a process and a thread?**

A process has its own address space and resources. Threads in the same process share memory and many resources, but each thread has its own stack, registers, and execution state.

### 3.5 Task 2 Files

- `task2_threads/threads.c`
- `task2_threads/threads_mutex.c`
- `task2_threads/threads_observe.c`
- `task2_threads/result_threads.txt`
- `task2_threads/result_threads_mutex.txt`
- `task2_threads/result_observe_linux.txt`
- `task2_threads/command_used_threads.txt`

---
## 4. Task 3: Java Multithreading

The Java programs were implemented, compiled, and executed using **JDK 25.0.1 on macOS**. The source files and execution result files were then transferred to the Ubuntu activity directory.

### 4.1 Creating Threads by Extending Thread

File: `task3_java/ThreadDemo.java`

This program creates three threads by extending the `Thread` class.

Each thread counts from 1 to 5 with a short delay between steps.

The program uses:

- `start()` to start each thread.
- `sleep()` to pause execution.
- `join()` to wait for all threads to finish.

The output demonstrates concurrent execution.

### 4.2 Creating Threads by Implementing Runnable

File: `task3_java/RunnableDemo.java`

This program creates three tasks by implementing the `Runnable` interface:

- Download
- Process
- Upload

Each task performs three steps.

The Runnable tasks are executed using separate Thread objects.

### 4.3 Creating a Thread Pool Using ExecutorService

File: `task3_java/PoolDemo.java`

This program uses:

```java id="1zd8t2"
Executors.newFixedThreadPool(2);
```

A fixed thread pool with two worker threads executes six submitted tasks.

Only two tasks can execute concurrently. Other tasks wait until a worker becomes available.

The program uses `shutdown()` and `awaitTermination()` to manage the executor lifecycle.

### 4.4 Questions and Answers

**Q1. What is the difference between extending Thread and implementing Runnable?**

Extending Thread combines the task and the thread object in one class. It also prevents the class from extending another class.

Implementing Runnable separates the task from the thread that executes it. It is more flexible and allows the task to be reused by different threads or executors.

Implementing Runnable is generally preferred.

**Q2. How does a fixed thread pool work?**

A fixed thread pool contains a limited number of worker threads. In this activity, two workers execute six submitted tasks. Tasks wait in a queue until a worker becomes available.

**Q3. What is the purpose of join()?**

`join()` makes the current thread wait until another thread finishes. Without it, the main thread may continue before the worker threads complete.

**Q4. What are the advantages of ExecutorService?**

ExecutorService simplifies concurrent programming by managing thread creation, task execution, task queues, thread reuse, and shutdown.

### 4.5 Task 3 Files

- `task3_java/ThreadDemo.java`
- `task3_java/RunnableDemo.java`
- `task3_java/PoolDemo.java`
- `task3_java/result_thread_demo.txt`
- `task3_java/result_runnable_demo.txt`
- `task3_java/result_pool_demo.txt`
- `task3_java/command_used_java.txt`

---
## 5. Task 4: Observing Threads in Linux and Windows

### 5.1 Observing Threads in Linux

The `threads_observe` program creates four worker threads and one main thread.

The process was observed using Linux commands:

```bash
ps -eLf
ps -T -p PID
cat /proc/PID/status
ls /proc/PID/task/
```

The observation confirmed:

- One main thread and four worker threads.
- Five thread IDs (TIDs) in `/proc/PID/task/`.
- The process status reported `Threads: 5`.
- The main thread TID was the same as the process PID.

**Important Linux terms:**

- PID: Process ID.
- TID: Thread ID.
- LWP: Lightweight Process ID, commonly used by Linux tools to identify threads.
- NLWP: Number of lightweight processes (threads) in a process.
- PSR: The processor number on which a task last ran.

### 5.2 Observing Linux Kernel Threads

Linux kernel threads were examined using:

```bash
ps -o pid,ppid,psr,comm -p 2
ps --ppid 2 -o pid,ppid,psr,comm | head -15
ps -eo pid,ppid,nlwp,comm --forest | head -30
```

The observation showed:

- `kthreadd` has PID 2.
- Its parent PID is 0.
- It manages the creation of kernel threads.
- Examples of kernel threads include `kworker`, `ksoftirqd`, and `rcu_preempt`.

Kernel threads perform background operating-system tasks and are managed by the Linux kernel.

### 5.3 Observing Threads in Windows

**Status: Pending Windows observation.**

The Windows observation should be performed using Windows 11 Task Manager:

1. Open Task Manager with `Ctrl + Shift + Esc`.
2. Select the Details tab.
3. Right-click a column heading and select Select columns.
4. Enable the Threads column.
5. Find the Java process (`java.exe`) and observe its thread count.
6. Capture a screenshot showing the process and Threads column.

The screenshot should be saved as:

`screenshots/task4_taskmanager_threads.png`

### 5.4 Questions and Answers

**Q1. What is the difference between PID and TID?**

PID identifies a process. TID identifies an individual thread. In Linux, the main thread normally has the same PID and TID.

**Q2. What does the Threads field in /proc/PID/status show?**

It shows the total number of threads belonging to the process.

**Q3. What is kthreadd?**

`kthreadd` is a Linux kernel thread with PID 2. It is responsible for creating and managing other kernel threads.

**Q4. Why does a Java process have multiple threads?**

A Java Virtual Machine creates internal threads for activities such as garbage collection, just-in-time compilation, and other runtime operations, in addition to application threads.

**Q5. What is the difference between Linux and Windows thread observation?**

Linux provides detailed thread information through commands such as `ps` and the `/proc` filesystem. Windows Task Manager provides a convenient way to view the thread count of a process.

### 5.5 Task 4 Evidence

- Linux thread observation: `task2_threads/result_observe_linux.txt`
- Linux kernel thread observation: `task2_threads/result_kernel_threads.txt`
- Linux htop screenshots and Windows Task Manager screenshot should be placed in `screenshots/` after they are verified.

---
