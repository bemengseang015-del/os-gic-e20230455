# Class Activity 2: Processes and Inter-Process Communication (IPC)

**Student Name:** Mengseang  
**Student ID:** e20230455  
**Date:** November 5, 2026

---

# Task 1: Linux Process Creation Using `fork()` and `exec()`

## 1. Compilation and Execution

Compile the C program:

```bash
gcc -o forkchild forkchild.c
```

Run the program and save its output:

```bash
./forkchild > result_forkchild.txt 2>&1
```

The program creates a child process using `fork()`. The child displays its PID and parent PID, waits for 30 seconds, and then executes the `ls -la` command using `execlp()`. The parent waits for the child to finish using `waitpid()`.

## 2. Screenshots

- [Task 1 Compilation and Execution](screenshots/task1_compile_run.png)
- [Task 1 Parent and Child Process Tree](screenshots/task1_process_tree.png)

## 3. Output

Output file: `task1/result_forkchild.txt`

Example output:

```text
Child: PID = 1529172, Parent PID = 1529171

total 36
...

Parent: Child exited with status 0
Parent: done.
```

## 4. Questions and Answers

**Q1. What does `fork()` return to the parent and child processes?**

`fork()` creates a new child process by duplicating the calling process. It returns different values depending on where it executes:

- In the parent process, it returns the PID of the newly created child.
- In the child process, it returns `0`.
- If process creation fails, it returns `-1` to the parent.

**Q2. What happens if `waitpid()` is removed from the parent process?**

Without `waitpid()`, the parent does not wait for the child process to finish. The parent may continue executing or terminate before the child completes. If the child finishes while its parent is still alive but has not collected its exit status, the child can become a zombie process.

**Q3. What does `execlp()` do? Why does the program not print an error when it succeeds?**

`execlp()` replaces the current process image with a new program. In this activity, it replaces the child process with the `ls -la` command.

When `execlp()` succeeds, it does not return to the original program. Therefore, the `perror()` statement after it is executed only if `execlp()` fails.

**Q4. What are the actual parent and child process IDs observed in your execution?**

From the observed process tree:

- Parent PID: `1528305`
- Child PID: `1528307`

The child process is created by the parent using `fork()`.

**Q5. What command was used to observe the process tree? Explain its columns.**

Command:

```bash
ps -ef --forest | grep -E '[f]orkchild'
```

Explanation:

- `ps`: Displays information about running processes.
- `-e`: Shows all processes.
- `-f`: Displays full-format process information.
- `--forest`: Displays processes in a tree structure.
- `grep`: Filters the output to show matching process information.

Important columns:

- `UID`: User who owns the process.
- `PID`: Process ID.
- `PPID`: Parent Process ID.
- `C`: CPU utilization information.
- `STIME`: Process start time.
- `TTY`: Terminal associated with the process.
- `TIME`: CPU time used by the process.
- `CMD`: Command that started the process.

Command history: `task1/command_used_forkchild.txt`

---

# Task 2: Windows Process Creation Using `CreateProcess()`

**Status: Pending Windows virtual machine execution.**

## 1. Compilation and Execution

This task uses the Windows API `CreateProcess()` to create a child process.

The program uses:

- `STARTUPINFO` to specify startup information.
- `PROCESS_INFORMATION` to receive information about the created process and its main thread.
- `GetCurrentProcessId()` to obtain the parent process ID.
- `CreateProcess()` to create the child process.
- `WaitForSingleObject()` to wait for the child process to finish.
- `CloseHandle()` to release process and thread handles.

Compile using MinGW:

```bash
gcc -o winprocess winprocess.c
```

Execute:

```powershell
.\winprocess.exe
```

**Actual compilation output and process IDs:** To be added after running the program in Windows.

## 2. Screenshots

- [Task 2 Compilation and Execution](screenshots/task2_compile_run.png)
- [Task 2 Task Manager Process Tree](screenshots/task2_taskmanager_tree.png)
- [Task 2 Task Manager Details](screenshots/task2_taskmanager_details.png)

*Screenshots will be added after completing the Windows virtual machine task.*

## 3. Output

The expected program output should display:

```text
Parent Process ID: [actual parent PID]
Child Process ID: [actual child PID]
Child Thread ID: [actual child thread ID]
```

Actual output: To be added after execution.

## 4. Questions and Answers

**Q1. What is the difference between Linux `fork()` and Windows `CreateProcess()`?**

Linux `fork()` creates a child process by duplicating the calling process. The child initially receives a copy of the parent's process state.

Windows `CreateProcess()` creates a new process and its primary thread. It can directly specify the executable program to run.

Both functions are used to create processes, but their process creation mechanisms are different.

**Q2. What does `WaitForSingleObject()` do? What is its Linux equivalent?**

`WaitForSingleObject()` makes the calling process wait until a specified object reaches a signaled state. In this activity, the parent waits until the child process finishes.

The Linux equivalent for waiting for a child process is `wait()` or `waitpid()`.

**Q3. Why does the program use `CloseHandle()`? What happens if it is omitted?**

`CloseHandle()` releases the handles associated with the child process and its main thread.

If the handles are not closed, Windows resources can remain allocated unnecessarily. Repeatedly creating processes without closing their handles can cause resource leaks.

**Q4. What are the actual parent PID and child PID?**

To be completed after executing the program in Windows.

- Parent PID: [Actual PID]
- Child PID: [Actual PID]

The child PID should match the process ID displayed for the child application in Task Manager.

**Q5. What is the difference between the Processes tab and Details tab in Windows Task Manager?**

The Processes tab displays running applications and processes in a more user-friendly way. It can show grouped or expanded applications.

The Details tab displays more technical information about individual processes, including their PID and Parent PID when the relevant columns are enabled.

The Processes tab helps visualize running applications, while the Details tab helps verify process relationships using IDs.

---

# Task 3: POSIX Shared Memory IPC

## 1. Compilation and Execution

Compile the producer:

```bash
gcc -o shm-producer shm-producer.c -lrt
```

Compile the consumer:

```bash
gcc -o shm-consumer shm-consumer.c -lrt
```

Run the producer first:

```bash
./shm-producer
```

Run the consumer and save its output:

```bash
./shm-consumer > result-shm-ipc.txt
```

Display the result:

```bash
cat result-shm-ipc.txt
```

The producer writes a message into shared memory named `OS-mengseang`. The consumer opens the same shared memory object, reads the message, and unlinks the shared memory object.

## 2. Screenshot

- [Task 3 Compilation and Execution](screenshots/task3_compile_run.png)

## 3. Output

Output file: `task3_shm/result-shm-ipc.txt`

```text
Consumer: read message: Hello, this is shared memory IPC!

Consumer: shared memory unlinked.
```

The consumer-before-producer test produced:

```text
shm_open: No such file or directory
```

This is expected because the shared memory object had not been created by the producer.

## 4. Questions and Answers

**Q1. What is the difference between `shm_open()` and `open()`?**

`shm_open()` is a POSIX function used to create or open a POSIX shared memory object. It allows multiple processes to access the same shared memory region.

`open()` is commonly used to open regular files in the filesystem.

The main difference is that `shm_open()` specifically manages POSIX shared memory objects, while `open()` is normally used for files.

**Q2. What does `mmap()` do? Why can shared memory be faster than other IPC methods?**

`mmap()` maps a shared memory object into the virtual address space of a process.

Shared memory can be faster because multiple processes can access the same memory region directly. They do not need to repeatedly copy messages through the operating system as with some other IPC methods.

However, processes must coordinate access to shared data to avoid race conditions.

**Q3. Why must the producer and consumer use the same shared memory name?**

Both processes must use the same shared memory name because this name identifies the shared memory object.

If they use different names, they will open different shared memory objects and cannot communicate through the same shared memory region.

**Q4. What does `shm_unlink()` do? What happens if it is not called?**

`shm_unlink()` removes the shared memory object's name from the system.

If it is not called, the shared memory object may remain available after the processes finish. This can waste system resources until it is explicitly removed.

**Q5. What happens if the consumer runs before the producer?**

If the consumer runs before the producer creates the shared memory object, `shm_open()` fails because the object does not exist.

In this activity, the observed error was:

```text
shm_open: No such file or directory
```

Therefore, the producer must create the shared memory object before the consumer can open and read it.

Command history: `task3_shm/command_used_shm.txt`

---

# Task 4: POSIX Message Queue IPC

## 1. Compilation and Execution

Compile the sender:

```bash
gcc -o sender sender.c -lrt
```

Compile the receiver:

```bash
gcc -o receiver receiver.c -lrt
```

Run the sender first:

```bash
./sender
```

Run the receiver and save its output:

```bash
./receiver > result-mq-ipc.txt
```

Display the result:

```bash
cat result-mq-ipc.txt
```

The sender creates a POSIX message queue named `/queue-mengseang` and sends a message. The receiver opens the queue, receives the message, closes the queue, and unlinks it.

## 2. Screenshot

- [Task 4 Compilation and Execution](screenshots/task4_compile_run.png)

## 3. Output

Output file: `task4_mq/result-mq-ipc.txt`

```text
Receiver: received message: Hello from sender! This is message queue IPC.

Receiver: message queue unlinked.
```

The receiver-before-sender test produced:

```text
mq_open: No such file or directory
```

This is expected because the message queue did not exist when the receiver tried to open it.

## 4. Questions and Answers

**Q1. What is the difference between message queue IPC and shared memory IPC? Give examples of when to use each.**

Message queue IPC allows processes to communicate by sending and receiving messages through a queue managed by the operating system.

Shared memory IPC allows multiple processes to access the same memory region directly.

Examples:

- Message queues are useful when processes need to exchange separate messages, commands, or events.
- Shared memory is useful when processes need to share large amounts of data efficiently, such as image or video data.

**Q2. Why must a POSIX message queue name start with `/`?**

A POSIX message queue name must begin with a slash (`/`) and should not contain additional slashes.

For example:

```c
#define QUEUE_NAME "/queue-mengseang"
```

The leading slash follows the POSIX naming convention for identifying a message queue.

**Q3. What does `mq_unlink()` do? What happens if neither process calls it?**

`mq_unlink()` removes the message queue name from the system.

If neither process calls it, the message queue can remain in the system after both processes finish. It may continue using system resources until it is removed.

**Q4. What happens if the receiver runs before the sender?**

If the receiver runs before the sender creates the message queue, `mq_open()` fails because the queue does not exist.

In this activity, the observed error was:

```text
mq_open: No such file or directory
```

Therefore, the sender must create the queue before the receiver can open it.

**Q5. What happens if multiple senders and receivers use the same message queue?**

Multiple senders can send messages to the same message queue. The messages are stored in the queue until receivers retrieve them.

Multiple receivers can also open the same queue. Each received message is removed from the queue and delivered to one receiver, not broadcast to all receivers.

Message priorities can affect the order in which messages are received.

Command history: `task4_mq/command_used_mq.txt`

---

# Reflection

Through this activity, I learned how processes are created and how different processes communicate with each other.

In Task 1, I learned how Linux creates a child process using `fork()` and replaces its program using `exec()`. I also understood why the parent process needs `waitpid()`.

In Task 2, I learned the purpose of the Windows `CreateProcess()` API and how it differs from Linux process creation. This task will be completed after running the program in a Windows virtual machine.

In Task 3, I learned how POSIX shared memory allows multiple processes to access the same memory region. I also understood the importance of using the same shared memory name and removing it with `shm_unlink()`.

In Task 4, I learned how POSIX message queues allow processes to exchange messages using a sender and receiver. I also learned why the sender must create the queue before the receiver can open it.

Overall, this activity helped me understand process creation, parent-child relationships, and the differences between shared memory and message queue communication. It also gave me practical experience compiling, executing, testing, and debugging C programs in Linux.

ø
