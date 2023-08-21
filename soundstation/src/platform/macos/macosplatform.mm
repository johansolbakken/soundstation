#include "core/platform.h"

#include <Foundation/Foundation.h>
#include <AppKit/AppKit.h>

namespace SoundStation {

    std::string Platform::openFile(const std::string &filter) {
        std::string path;

        NSString *filterString = [NSString stringWithUTF8String:filter.c_str()];

        NSOpenPanel *panel = [NSOpenPanel openPanel];
        [panel setAllowsMultipleSelection:NO];
        [panel setCanChooseDirectories:NO];
        [panel setCanChooseFiles:YES];

        if ([panel runModal] == NSModalResponseOK) {
            NSURL *url = [[panel URLs] objectAtIndex:0];

            // convert path to c string
            path = [[url path] UTF8String];
        }

        return path;
    }

    std::string Platform::saveFile(const std::string &filter) {
        std::string path;

        NSString *filterString = [NSString stringWithUTF8String:filter.c_str()];

        NSSavePanel *panel = [NSSavePanel savePanel];

        if ([panel runModal] == NSModalResponseOK) {
            NSURL *url = [panel URL];
            path = [[url path] UTF8String];
        }

        return path;
    }

}