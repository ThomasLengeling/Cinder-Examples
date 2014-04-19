#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "cinder/Camera.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MultiWindowParamApp : public AppNative {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
private:
    WindowRef	 mMainWindow;
    void         drawMain();
    void         shutDown();
    void	     windowManagement();
    
    
   
    void         drawGUIWindow();
    
public:
    
    params::InterfaceGlRef	mParams;
    
    CameraPersp				mCam;
	float					mObjSize;
	Quatf					mObjOrientation;
	Vec3f					mLightDirection;
	ColorA					mColor;
	std::string				mString;
};

void MultiWindowParamApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize(1902, 1080);
    settings->setFrameRate(120.0f);
    settings->setBorderless();
    
}

void MultiWindowParamApp::setup()
{
    
    mMainWindow = getWindow();
	mMainWindow->setTitle("Main");
	mMainWindow->connectDraw(&MultiWindowParamApp::drawMain, this);
    mMainWindow->connectClose(&MultiWindowParamApp::shutdown, this);
    
    WindowRef    mRenderWindow;
    mRenderWindow = createWindow(Window::Format().size(300, 600));
    mRenderWindow->connectDraw(&MultiWindowParamApp::drawGUIWindow, this);
    
    mObjSize = 4;
	mLightDirection = Vec3f( 0, 0, -1 );
	mColor = ColorA( 0.25f, 0.5f, 1.0f, 1.0f );
    
	// setup our default camera, looking down the z-axis
	mCam.lookAt( Vec3f( -20, 0, 0 ), Vec3f::zero() );
    
    // Setup the parameters
	mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( Vec2i( 250, 500 ) ) );
	mParams->addParam( "Cube Size", &mObjSize, "min=0.1 max=20.5 step=0.5 keyIncr=z keyDecr=Z" );
	mParams->addParam( "Cube Rotation", &mObjOrientation );
	mParams->addParam( "Cube Color", &mColor, "" );
	mParams->addSeparator();
	mParams->addParam( "Light Direction", &mLightDirection, "" );
	mParams->addText( "text", "label=`This is a label without a parameter.`" );
	mParams->addParam( "String ", &mString, "" );
}

void MultiWindowParamApp::mouseDown( MouseEvent event )
{
}

void MultiWindowParamApp::update()
{
}

void MultiWindowParamApp::draw()
{
    
}

void MultiWindowParamApp::drawMain()
{
    gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::clear( Color( 0.1f, 0.1f, 0.1f ) );
    
	glLoadIdentity();
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	GLfloat lightPosition[] = { -mLightDirection.x, -mLightDirection.y, -mLightDirection.z, 0.0f };
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
	glMaterialfv( GL_FRONT, GL_DIFFUSE,	mColor );
    
	gl::setMatrices( mCam );
	gl::rotate( mObjOrientation );
	gl::color( mColor );
	gl::drawCube( Vec3f::zero(), Vec3f( mObjSize, mObjSize, mObjSize ) );

}

void MultiWindowParamApp::drawGUIWindow()
{
    gl::clear(Color(0.75, 0.75, 0.75));
    
    mParams->draw();
}

void MultiWindowParamApp::shutDown()
{
    
}

CINDER_APP_NATIVE( MultiWindowParamApp, RendererGl )
