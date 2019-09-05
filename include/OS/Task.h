/* Task class
    Encapusulates a single function, a time delta (ticks since issue), and a time goal.
    The idea is the time delta can be used with the goal to prioritize the task
    or know when it is ready to go.

    Maixduino appears to only be able to count down to seconds using <chrono>.
*/

typedef void(*payloadFunc) ();

class Task
{
public:
    Task(int timerLength, bool newRepeat, payloadFunc func);
    ~Task();

    bool ready();
    bool doesRepeat();
    int getTickDelta();
    void updateTickDelta();
    void deliverPayload();
    void reset();

//private:
    int tickDelta, tickGoal;

    bool repeat;
    payloadFunc payload;
};
