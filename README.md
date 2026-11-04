_This project has been created as part of the 42 curriculum by jfox._

# Philosophers
In this project we will learn the basics of the threading process. I will learn how to create threads and explore the use of mutexes.

## Description
In this project, I will learn the basics of **threading** and **mutexes** by implementing the classic **Dining Philosophers** problem.

One or more philosophers sit around a round table. There is a bowl of spaghetti in the middle and one fork between each pair of philosophers.
Each philosopher alternates between:

* Eating
* Sleeping
* Thinking

To eat, a philosopher needs to pick up both the fork on their left and the fork on their right. Once they have finished eating, they put both forks back and go to sleep.
The simulation continues until a philosopher dies from starvation, unless the optional meal limit is provided.
The main challenge of this project is making all philosophers work concurrently without creating **data races**, while correctly handling shared resources with mutexes.

## Arguments
The program takes the following arguments:

```text
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

* `number_of_philosophers` — Number of philosophers and forks.
* `time_to_die` — Time in milliseconds a philosopher can go without starting a meal before dying.
* `time_to_eat` — Time in milliseconds spent eating. The philosopher must hold two forks during this time.
* `time_to_sleep` — Time in milliseconds spent sleeping.
* `number_of_times_each_philosopher_must_eat` — Optional. If provided, the simulation stops once every philosopher has eaten at least this many times.

## Output
Every state change must be printed in the following format:

```text
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

`timestamp_in_ms` is the time since the beginning of the simulation and `X` is the philosopher's number.
A philosopher's death must be displayed within **10 ms** of their actual death.

You can add this line:
```
	printf("phil %d has eaten %d\n", philo->id, philo->eaten);
```
To the eat function in sim.c to watch live how many meals each philo has eaten.

## Threading & Mutexes
Each philosopher must be represented by a separate thread.
There is one fork between each pair of philosophers, meaning there are as many forks as philosophers.
Each fork must be protected by a **mutex** so that two philosophers cannot use the same fork at the same time.
Shared data must also be properly protected to ensure that the program contains **no data races**.
The special case of a single philosopher must also be handled correctly, as they only have access to one fork and therefore cannot eat.

## Allowed Functions
The project is restricted to the following functions:

```text
memset
printf
malloc
free
write
usleep
gettimeofday

pthread_create
pthread_detach
pthread_join

pthread_mutex_init
pthread_mutex_destroy
pthread_mutex_lock
pthread_mutex_unlock
```

`libft` cannot be used.

## Compilation
```bash
make
```
Then run the program with:

```bash
./philo 5 800 200 200
```
With the optional meal limit:

```bash
./philo 5 800 200 200 5
```

## Resources
* [The Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
* [Git Lab guide](https://42-fran-byte-f94097.gitlab.io/docs/philosophers/philosophers-approach-en/#/)
* [Medium guide](https://medium.com/@denaelgammal/dining-philosophers-problem-42-project-guide-mandatory-part-a20fb8dc530e)
* [Ft_usleep](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)
* `pthread` documentation
* `pthread_mutex` documentation
* `gettimeofday` documentation
* `chatgpt` for guidance and notions of the project implimentation
