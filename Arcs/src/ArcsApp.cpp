#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"

#include "TriLUT.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ArcsApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    
    CameraPersp				mCam;
    params::InterfaceGlRef	mParams;
    Quatf					mObjOrientation;
    
    TriLUT triLUT;
    
    void arc(float x,float y, float rad,float w);
    int lengthLUT;
};

void ArcsApp::setup()
{
    lengthLUT =  int(math<float>::min (90 / triLUT.getPrecision(), triLUT.getLenght() - 1));
    console()<<lengthLUT<<std::endl;
    console()<<triLUT.getCOS(0)<<" "<<triLUT.getCOS(90)<<std::endl;
    console()<<triLUT.getSIN(0)<<" "<<triLUT.getSIN(90)<<std::endl;
    
    mCam.lookAt( Vec3f( 0, -1, -30 ), Vec3f::zero() );
    
    // Setup the parameters
	mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( Vec2i( 200, 400 ) ) );
	mParams->addParam( "Cube Rotation", &mObjOrientation );
}

void ArcsApp::mouseDown( MouseEvent event )
{
}

void ArcsApp::update()
{
}

void ArcsApp::draw()
{
	// clear out the window with black
    gl::enableDepthRead();
    gl::enableDepthWrite();
	gl::clear( Color( 1.0, 1.0, 1.0 ) );
    
    //gl::translate(getWindowWidth()/2, getWindowHeight()/2.0);
    
    gl::setMatrices( mCam );
	gl::rotate( mObjOrientation );
    gl::color(0.0, 0.0, 0.0);
    arc(0, 0, 3.5, 2);
    
    gl::color(0.0, 0.0, 0.0);
    arc(1, 1, 6.5, 2);
    
    
    
    gl::color(0.5f, 0.5f, 0.5f);
    gl::drawSphere(ci::Vec3f::zero(), 1);
    
    mParams->draw();
}

void ArcsApp::arc(float x, float y, float rad,float w) {
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < lengthLUT; i++) {
        glVertex3f(triLUT.getCOS(i)*(rad) + x,   triLUT.getSIN(i)*(rad) + y, 0);
        glVertex3f(triLUT.getCOS(i)*(rad + w) + x, triLUT.getSIN(i)*(rad + w) + y, 0);
    }
    glEnd();
    
}

CINDER_APP_NATIVE( ArcsApp, RendererGl )
