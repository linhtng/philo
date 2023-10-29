
<h1 align="center">
	🧠 philo
</h1>
<p align="center">
	<b><i>Threads, Mutexes and Concurrent Programming in C</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/linhtng/philo?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/linhtng/philo?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/linhtng/philo?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/linhtng/philo?color=green" />
</p>

---

## 💡 About the project
For efficiency or by necessity, a program can be concurrent rather than sequential. 
Thanks to its concurrent programming and with its child processes or threads and mutexes, it will be able to perform multiple tasks simultaneously.
This project teaches you about threads and how to deal with the dangers that come with their shared memory with mutexes while solving the classic "Dining Philosophers" problem.

### What is a Thread?
An execution thread is a logical sequence of instructions inside a process that is automatically managed by the operating system’s kernel. 
Modern operating systems allow us to create multiple threads in our programs, all of which run in parallel.
Each one of a process’s threads has its own context: its own ID, its own stack, its own instruction pointer, it’s own processor register. 

Since all of the threads are part of the same process, they share the same virtual memory address space: the same code, the same heap, the same shared libraries and the same open file descriptors.
Any thread can read and write to the same virtual memory, which makes communication between threads much easier than communication between processes. 
The standard interface in C to manipulate threads is POSIX with its <pthread.h> library.
In philo, we will create a separate thread for each philosopher.

### What is data races?
Data races occur when multiple tasks or threads access a shared resource without sufficient protections, leading to undefined or unpredictable behavior. It is impossible to predict if the operating system will choose the correct sequencing for our threads.
So is there a way to stop a thread from reading a value while another one modifies it? Yes, thanks to mutexes!

### Mutex

A mutex (short for “mutual exclusion”) is a synchronization primitive. It is essentially a lock that allows us to regulate access to data and prevent shared resources being used at the same time.

We can think of a mutex as the lock of a bathroom door. One thread locks it to indicate that the bathroom is occupied. 
The other threads will just have to patiently stand in line until the door is unlocked before they can take their turn in the bathroom.
In the context of philo, mutext is used to lock the turn of using forks, so that 2 philosopher will not access the same fork at the same time, for example.

### Deadlocks
Despite its usefulness, mutexes can often provoke deadlocks. It’s a situation in which each thread waits for a resource held by another thread. 
For example, thread T1 acquired mutex M1 and is waiting for mutex M2. Meanwhile thread T2 acquired mutex M2 and is waiting for mutex M1. In this situation, the program stays perpetually pending and must be killed.

In the context of philo, if all philos first pick up the fork on their right (or left), i.e philo 1 picks fork 1, philo 2 picks fork 2,..., philo 5 picks fork 0, then nobody is able to get 2 forks -> circular wait that would cause deadlock.

### Deadlocks prevention
There are several ways to deal with deadlocks like these. Among other things, we can:

* avoid them by imposing a strict order for resource acquisition. This is the solution to our previous example: the threads should both ask for lock_1 first.
* avoid them by forcing a thread to release a resource before asking for new ones, or before renewing its request.

In this programme, I implemented the deadlock prevention by dividing up philo thread routine for

* odd id: eat, sleep, and think, repeat until the sim ends.
* even id: sleep, eat, think, repeat until the sim ends.
By doing this, philosophers with an odd id is able to pick up the forks and starts eating before the even id philos.

Additionally, to avoid deadlock, we impose this strict fork acquisition order: philos with odd id are right-handed, i.e. they always 1st pick up the fork on their right, then pick up the fork on their left. On the contrary, philos with even id are left-handed, they always 1st pick up the fork on their left, then pick up the fork on their right.
For example, philos id 1 picks up fork 1 then picks fork 0, while philos id 2 picks up fork 1 then picks fork 2. 

## Installation

* Clone this repository:

```shell
https://github.com/linhtng/philo.git
```

* Go to the project folder:

```shell
cd philo
```

* To compile:

```shell
make
```
* Usage:
```shell
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```
Examples:

`./philo 1 800 200 200` - Philosopher should not eat and should die. <br>
`./philo 5 800 200 200` - No Philosopher should die. <br>
`./philo 5 800 200 200 7` - No Philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times. <br>
`./philo 4 410 200 200` - No Philosopher should die. <br>
`./philo 4 310 200 100` - One Philosopher should die. 

## References

* [Threads, Mutexes and Concurrent Programming in C](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/)
