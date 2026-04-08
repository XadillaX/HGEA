#import <Cocoa/Cocoa.h>
#include "../../include/hge.h"
#include "../hge_impl.h"

// Objective-C++ wrapper for macOS Window delegate
@interface HGEWindowDelegate : NSObject <NSWindowDelegate>
@end

@implementation HGEWindowDelegate
- (BOOL)windowShouldClose:(NSWindow *)sender {
    if (pHGE->procExitFunc) {
        if (!pHGE->procExitFunc()) {
            return NO;
        }
    }
    [NSApp terminate:nil];
    return YES;
}
@end

static HGEWindowDelegate* g_windowDelegate = nil;
static bool g_bQuit = false;

bool CALL HGE_Impl::System_Initiate() {
    // 1. Initialize NSApplication
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    
    // 2. Create Window
    NSRect frame = NSMakeRect(0, 0, nScreenWidth, nScreenHeight);
    NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable;
    
    if (!bWindowed) {
        // TODO: Fullscreen support
        style |= NSWindowStyleMaskFullScreen;
    }
    
    NSWindow* window = [[NSWindow alloc] initWithContentRect:frame
                                                   styleMask:style
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];
    [window setTitle:[NSString stringWithUTF8String:szWinTitle]];
    [window center];
    
    g_windowDelegate = [[HGEWindowDelegate alloc] init];
    [window setDelegate:g_windowDelegate];
    
    hwnd = (void*)window;
    
    // 3. Make window visible
    [window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
    
    bActive = true;
    return true;
}

void CALL HGE_Impl::System_Shutdown() {
    if (hwnd) {
        NSWindow* window = (NSWindow*)hwnd;
        [window close];
        hwnd = nullptr;
    }
    
    if (g_windowDelegate) {
        g_windowDelegate = nil;
    }
    
    bActive = false;
}

bool CALL HGE_Impl::System_Start() {
    if (!hwnd) {
        _PostError("System_Start: Call System_Initiate first.");
        return false;
    }
    
    if (!procFrameFunc) {
        _PostError("System_Start: No frame function defined.");
        return false;
    }
    
    g_bQuit = false;
    
    // Manual event pumping loop to maintain HGE's blocking semantics
    while (!g_bQuit) {
        // 1. Pump OS events
        NSEvent* event;
        while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                           untilDate:[NSDate distantPast]
                                              inMode:NSDefaultRunLoopMode
                                             dequeue:YES])) {
            [NSApp sendEvent:event];
            [NSApp updateWindows];
            
            if ([event type] == NSEventTypeApplicationDefined) {
                // Handle custom quit event if necessary
            }
        }
        
        // 2. Call user FrameFunc
        if (procFrameFunc()) {
            g_bQuit = true;
            break;
        }
        
        // 3. Call user RenderFunc
        if (procRenderFunc) {
            procRenderFunc();
        }
        
        // 4. Yield CPU slightly to prevent 100% CPU lock in this simple loop
        // In a real implementation, Timer/FPS sync should be used here.
        usleep(1000); 
    }
    
    return true;
}
