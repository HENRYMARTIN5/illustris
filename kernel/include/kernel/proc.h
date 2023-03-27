typedef struct _process process;
typedef struct _task task;

int proc_create(); // Returns new pid, or -1 on error
int proc_vaporize(int pid); // returns 0 on success, -1 on error

int task_create(int pid, void (*func)(void *)); // Returns new tid, or -1 on error
int task_vaporize(int pid, int tid); // returns 0 on success, -1 on error

void proc_tick();
int proc_forcenext(int pid);

struct _process
{
    int pid;
    task *tasks;
    process *next;
    int current_tid;
};

struct _task
{
    // A task is a single operation that a process performs. These tasks are gone through in order, and when a task is finished, the next one is started.
    // These are blocking and should be executed as quickly as possible.
    int tid;
    void (*func)(void *);
    task *next;
};