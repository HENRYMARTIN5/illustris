#include <stdlib.h>
#include <stdio.h>
#include <kernel/proc.h>

int next_pid = 0;
process *proc_main = NULL;

int proc_create()
{
    process *new_proc = malloc(sizeof(process));
    new_proc->storage = malloc(1024); // allocate 1 KiB of storage
    if (new_proc == NULL)
    {
        return -1;
    }
    new_proc->pid = next_pid;
    new_proc->tasks = NULL;
    new_proc->current_tid = -1;
    if (proc_main == NULL){
        proc_main = new_proc;
    } else {
        process *proc = proc_main;
        while (proc->next != NULL)
        {
            proc = proc->next;
        }
        proc->next = new_proc;
    }
    next_pid++;
    return new_proc->pid;
}

int proc_vaporize(int pid)
{
    process *proc = proc_main;
    process *prev_proc = NULL;
    while (proc != NULL)
    {
        if (proc->pid == pid)
        {
            if (prev_proc == NULL)
            {
                proc_main = proc->next;
            } else {
                prev_proc->next = proc->next;
            }
            free(proc);
            return 0;
        }
        prev_proc = proc;
        proc = proc->next;
    }
    return -1;
}

int task_create(int pid, void (*func)(void *))
{
    process *proc = proc_main;
    while (proc != NULL)
    {
        if (proc->pid == pid)
        {
            task *new_task = malloc(sizeof(task));
            if (new_task == NULL)
            {
                return -1;
            }
            new_task->tid = proc->current_tid + 1;
            new_task->func = func;
            new_task->next = NULL;
            if (proc->tasks == NULL)
            {
                proc->tasks = new_task;
            } else {
                task *task = proc->tasks;
                while (task->next != NULL)
                {
                    task = task->next;
                }
                task->next = new_task;
            }
            proc->current_tid++;
            return new_task->tid;
        }
        proc = proc->next;
    }
    return -1;
}

int task_vaporize(int pid, int tid) {
    process *proc = proc_main;
    while (proc != NULL)
    {
        if (proc->pid == pid)
        {
            task *task = proc->tasks;
            task *prev_task = NULL;
            while (task != NULL)
            {
                if (task->tid == tid)
                {
                    if (prev_task == NULL)
                    {
                        proc->tasks = task->next;
                    } else {
                        prev_task->next = task->next;
                    }
                    free(task);
                    return 0;
                }
                prev_task = task;
                task = task->next;
            }
            return -1;
        }
        proc = proc->next;
    }
    return -1;
}

int proc_forcenext(int pid)
{
    // Moves the given pid to the front of the process queue and moves the current process one step back.
    process *proc = proc_main;
    process *prev_proc = NULL;
    while (proc != NULL)
    {
        if (proc->pid == pid)
        {
            if (prev_proc == NULL)
            {
                return 0;
            }
            prev_proc->next = proc->next;
            proc->next = proc_main;
            proc_main = proc;
            return 0;
        }
        prev_proc = proc;
        proc = proc->next;
    }
    return -1;
}

void proc_tick()
{
    process *proc = proc_main;
    while (proc != NULL)
    {
        // We only want to execute the first task in the queue for each of the processes. 
        if (proc->tasks != NULL)
        {
            proc->tasks->func();
            task_vaporize(proc->pid, proc->tasks->tid);
        }
        proc = proc->next;
    }
}

void *proc_get_storage(int pid)
{
    process *p = get_process(pid);
    return p->storage;
}

void proc_set_storage(int pid, void *data, int size)
{
    process *p = get_process(pid);
    memcpy(p->storage, data, size);
}

void proc_read_storage(int pid, void *data, int size)
{
    process *p = get_process(pid);
    memcpy(data, p->storage, size);
}

void *proc_request_storage(int pid, int size)
{
    process *p = get_process(pid);
    p->storage = realloc(p->storage, size);
    return p->storage;
}