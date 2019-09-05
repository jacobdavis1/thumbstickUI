#include <list>
#include <chrono>
#include "OS/Task.h"
#include "OS/Scheduler.h"

Scheduler::Scheduler()
{
    ticksPerSecond = 100;
}

Scheduler::~Scheduler()
{

}

void Scheduler::scheduleTask(int timerLengthMilliseconds, bool repeat, taskFunc func)
{
   taskList.push_back(Task(timerLengthMilliseconds*ticksPerSecond, repeat, func));
}

void Scheduler::updateTickRatio()
{
    static std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    static int ticks = 0;

    std::chrono::high_resolution_clock::time_point rn = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds>(rn - start).count() > 0)
    {
        ticksPerSecond = ticks;
        ticks = 0;
        start = rn;
    }
    else ++ticks;
}

void Scheduler::update()
{
    updateTickRatio();
    
    for (std::list<Task>::iterator it = taskList.begin(); it != taskList.end(); ++it)
    {
        it->updateTickDelta();

        if (it->ready())
        {
            it->deliverPayload();

            if (it->doesRepeat())
                it->reset();
            else
                it = taskList.erase(it);
        }
    }
}

double Scheduler::getTicksPerSecond()
{
    return ticksPerSecond;
}