/* Scheduler class
    Schedules all tasks and updates them iteratively. If tasks are ready,
    the scheduler will activate their functions and restart them if 
    necessary.
*/

#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <list>

class Task;

typedef void(*taskFunc)();

class Scheduler
{
public:
    Scheduler();
    ~Scheduler();

    void scheduleTask(int timerLengthMilliseconds, bool repeat, taskFunc func);

    void updateTickRatio();
    void update();

    double getTicksPerSecond();

private:
    std::list<Task> taskList;
    Task* tickRatioTask;
    double ticksPerSecond;
};

#endif