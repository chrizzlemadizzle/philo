# philosophers

An implementation of the classic Dining Philosophers problem in C, written for the 42 curriculum.

Multiple philosophers sit around a round table with a big bowl of spaghetti and one fork between each of them.  
They spend their lives **eating**, **sleeping**, and **thinking** — trying very hard not to starve.

---

## Features

- Configurable number of philosophers and time settings
- Accurate timing in **milliseconds**
- Each philosopher cycles between:
  - thinking
  - taking forks
  - eating
  - sleeping
- The simulation stops when:
  - a philosopher dies of starvation **or**
  - (optional) everyone has eaten a minimum number of times
- Properly formatted, non-overlapping log output with timestamps
- No global variables (as required by the subject)

- ## Program Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
