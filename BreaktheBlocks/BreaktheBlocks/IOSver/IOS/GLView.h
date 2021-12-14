
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>
#import "SceneManager.h"

@interface GLView : UIView
{
    EAGLContext  * m_context;
    SceneManager * scene;
}

- (void) drawView: (CADisplayLink*) displayLink;
- (void) didRotate: (NSNotification*) notification;
@end
