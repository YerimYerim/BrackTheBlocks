
#import "GLView.h"
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES3/gl.h>
#import "mach/mach_time.h"
#import <OpenGLES/ES3/glext.h>
@implementation GLView

+ (Class) layerClass{
    return [CAEAGLLayer class];
}

- (id) initWithFrame:(CGRect)frame{
    if (self = [super initWithFrame:frame]) {
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*) super.layer;
        eaglLayer.opaque =YES;
        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES3;
        m_context = [[EAGLContext alloc] initWithAPI:api];
        [EAGLContext setCurrentContext:m_context];
        
        scene = new SceneManager(CGRectGetWidth(frame), CGRectGetHeight(frame));
        
        [m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable: eaglLayer];

        [self drawView: nil];
        CADisplayLink* displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        
    }
    return self;
}
- (void) drawView:(CADisplayLink*) displayLink{
    
    scene->updateScene();
    
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}
- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint location = [touch locationInView:self];
    scene->input(true, location.x, location.y);
    }
- (void) touchesEnded:(NSSet*)touches withEvent:(UIEvent *)event{
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint location = [touch locationInView:self];
    scene->input(false, location.x, location.y);
}
- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint location = [touch locationInView:self];
    scene->input(true, location.x, location.y);
}
@end
