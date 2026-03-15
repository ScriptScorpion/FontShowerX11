#include <X11/Xlib.h>
#include <fontconfig/fontconfig.h>
#include <X11/Xft/Xft.h>
#include <string>
#include <cmath>

#define FontPath "/usr/share/fonts/truetype/cloister-black/CloisterBlack.ttf"
const std::string Text = "Hello";


int main() {
    Display* MainDisplay = XOpenDisplay(0);
    Window RootWindow = XDefaultRootWindow(MainDisplay);
    
    const float ScreenWidth = XDisplayWidth(MainDisplay, DefaultScreen(MainDisplay));
    const float ScreenHeight = XDisplayHeight(MainDisplay, DefaultScreen(MainDisplay));
    
    const int WindowX = 0;
    const int WindowY = 0;
    const int WindowWidth = ScreenWidth;
    const int WindowHeight = ScreenHeight;
    const int BorderWidth = 0;
    const int WindowDepth = CopyFromParent;
    const int WindowClass = CopyFromParent;
    Visual* WindowVisual = CopyFromParent;

    const int AttributeValueMask = CWBackPixel | CWBorderPixel;
    XSetWindowAttributes WindowAttributes = {};
    WindowAttributes.background_pixel = 0xffffff;

    Window MainWindow = XCreateWindow(MainDisplay, RootWindow, 
            WindowX, WindowY, WindowWidth, WindowHeight,
            BorderWidth, WindowDepth, WindowClass, WindowVisual,
            AttributeValueMask, &WindowAttributes);

    XSizeHints SizeHints; 
    SizeHints.flags = PMinSize | PMaxSize;
    SizeHints.min_width = WindowWidth;
    SizeHints.max_width = WindowWidth;
    SizeHints.min_height = WindowHeight;
    SizeHints.max_height = WindowHeight; 
    XSetWMNormalHints(MainDisplay, MainWindow, &SizeHints);
    
    XStoreName(MainDisplay, MainWindow, "Secret window");

    XMapWindow(MainDisplay, MainWindow);
    
    FcPattern *Pattern = FcPatternBuild(0, FC_FILE, FcTypeString, FontPath, FC_PIXEL_SIZE, FcTypeDouble, 72.0, NULL);

    XftFont *Font = XftFontOpenPattern(MainDisplay, Pattern);
    XftDraw *Draw = XftDrawCreate(MainDisplay, MainWindow, DefaultVisual(MainDisplay, DefaultScreen(MainDisplay)), DefaultColormap(MainDisplay, DefaultScreen(MainDisplay)));
    
    XftColor TextColor;
    XRenderColor RTextColor;
    RTextColor.red = 0x0000;
    RTextColor.green = 0x0000;
    RTextColor.blue = 0x0000;
    RTextColor.alpha = 0xffff;
    XftColorAllocValue(MainDisplay, DefaultVisual(MainDisplay, DefaultScreen(MainDisplay)), DefaultColormap(MainDisplay, DefaultScreen(MainDisplay)), &RTextColor, &TextColor);

    XftDrawStringUtf8(Draw, &TextColor, Font, std::floor((ScreenWidth - Text.length()) / 2.0), ScreenHeight / 2, reinterpret_cast<const XftChar8*>(Text.c_str()), Text.length());
    while (true) {
        XEvent GeneralEvent = {};
        XNextEvent(MainDisplay, &GeneralEvent);
    }

    XftDrawDestroy(Draw);
    XftFontClose(MainDisplay, Font);
    XDestroyWindow(MainDisplay, MainWindow);
    XCloseDisplay(MainDisplay);
}
