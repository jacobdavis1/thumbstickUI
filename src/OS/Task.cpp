#include "OS/Task.h"

Task::Task(int timerLength, bool newRepeat, payloadFunc func) : tickGoal(timerLength), repeat(newRepeat), payload(func)
{
    reset();
}

Task::~Task()
{

}

bool Task::ready()
{
    return (tickGoal <= tickDelta);
}

bool Task::doesRepeat()
{
    return repeat;
}

int Task::getTickDelta()
{
    return tickDelta;
}

void Task::updateTickDelta()
{
    ++tickDelta;
}

void Task::deliverPayload()
{
    payload();
}

void Task::reset()
{
    tickDelta = 0;
}