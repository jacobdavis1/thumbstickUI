/* WindowManager class
    Converts input from external sources into interaction with and navigation
    through the current menu.
*/

#include "UI/Program.h"
#include "UI/Menu.h"

class WindowManager
{
public:
    WindowManager();
    ~WindowManager();

    void update();
    void draw();

    void changeMenu(String newMenuName);
    void activateSelection();

private:
    Program program;
    Menu* currentMenu;
    Widget* currentSelection;
};