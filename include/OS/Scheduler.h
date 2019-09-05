/* Scheduler class
    Schedules all tasks and updates them iteratively. If tasks are ready,
    the scheduler will activate their functions and restart them if 
    necessary.
*/

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