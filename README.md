# 🍝 Philosophers

> **"I never thought I'd miss basic loops, but then I met threads."**
> A 42 Network project focused on the basics of process threading, shared memory, and synchronization using **mutexes** to solve the classic Dining Philosophers problem.

---

## 📖 The Problem

The Dining Philosophers problem is a classic synchronization challenge:
* Philosophers sit at a round table with a bowl of spaghetti.
* There are as many **forks** as there are philosophers.
* A philosopher needs **two forks** to eat.
* They must **eat**, **sleep**, and **think** in a loop.
* If a philosopher doesn't start eating within `time_to_die`, they die.



The challenge is to create a simulation where no philosopher dies of starvation, while avoiding **deadlocks** and **data races**.

---

## 🧩 Technical Features

| Feature | Implementation |
| :--- | :--- |
| **Language** | C (C99 Standard) |
| **Library** | `pthread` (POSIX threads) |
| **Synchronization** | `pthread_mutex_t` for fork management and data protection |
| **Multi-threading** | Each philosopher runs in its own thread |
| **Precision** | Custom timestamping for millisecond accuracy |

---
## 🛠️ Usage

### 📥 Installation

1. **Clone the repository:**

   ```bash
   git clone https://github.com/niboukha/philosopher.git
   cd philosopher/philo
2. **Compile the program:

   ```bash
   make

This will create an executable named philo in the philo/ directory

### 🚀 Running the Simulation
  
  The program accepts **4 or 5 arguments** (all in milliseconds):
  
  ```bash
  ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
  ```
---

## 🚦 Safety & Performance

This implementation is designed to be robust and efficient:

* **Race-free:** All shared data (death flags, meal counters, last meal timestamps) are protected by **mutexes** to ensure data integrity.

* **Deadlock-free:** Philosophers pick up forks in a specific order (e.g., asymmetric fork picking) to prevent a circular wait.
* **Efficient:** Uses optimized `usleep` calls with small intervals to monitor state accurately without overloading the CPU.

### Testing for Data Races
To check for race conditions during development, you can compile with the thread sanitizer:

```bash
cc -fsanitize=thread -g *.c -o philo
```
---

### 📂 Project Structure
Plaintext

```.
├── philo/
│   ├── includes/       # Header files (.h)
│   ├── srcs/           # Source files (.c)
│   │   ├── main.c      # Entry point
│   │   ├── init.c      # Initialization logic
│   │   ├── routine.c   # Philosopher cycle (eat/sleep/think)
│   │   ├── utils.c     # Timing and printing helpers
│   │   └── monitor.c   # Death checking logic
│   └── Makefile        # Compilation rules
```
---

### 💡 What I Learned

- Thread Management: Creating and managing multiple threads simultaneously using pthread_create and pthread_join.
- Synchronization: Protecting shared resources with pthread_mutex_lock and pthread_mutex_unlock.
- Avoiding Deadlocks: Solving the classic dining philosophers problem, where everyone holds one fork and waits forever.
- Avoiding Data Races: Ensuring two threads don't write to or read from the same variable simultaneously.
- Accurate Time Management: Using gettimeofday to track philosopher states with millisecond precision.
