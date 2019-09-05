/* Thumbstick class
    Access thumbstick values.
*/

typedef void(*clickCallback) ();

enum class ThumbstickDirection { NONE, N, NE, E, SE, S, SW, W, NW };

class Thumbstick
{
public:
    Thumbstick(int lPin, int rPin, int uPin, int dPin, int switchPin, clickCallback func);
    ~Thumbstick();

    ThumbstickDirection getDirection();
    bool hasActivity();
    void update();

//private:
    const int THUMBL;
    const int THUMBR;
    const int THUMBU;
    const int THUMBD;
    const int THUMBSW;
    clickCallback onClickFunc;

    bool pressed;

    ThumbstickDirection getX();
    ThumbstickDirection getY();
    bool switchPressed();
    void onClick();
};