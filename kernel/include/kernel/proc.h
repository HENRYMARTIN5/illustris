typedef struct _process process;
typedef struct _task task;

int proc_create(); // Returns new pid, or -1 on error
int proc_vaporize(int pid); // returns 0 on success, -1 on error

void *proc_get_storage(int pid); // returns pointer to proc storage
void proc_set_storage(int pid, void *data, int size); // copes data from pointer passed to storage
void proc_read_storage(int pid, void *data, int size); // copies data from storage to pointer passed
void *proc_request_storage(int pid, int size); // returns pointer to new, expanded storage - data is also copied during expansion

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
    void *storage;
};

struct _task {
    int tid;
    void (*func)();
    task *next;
};