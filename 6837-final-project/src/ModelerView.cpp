#include "ModelerView.h"
#include "camera.h"
#include "modelerapp.h"

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include "extra.h"
#include "SetDesign.h"
#include "Light.h"
#include <cstdio>
#include <math.h>

// Accessing the values of sliders is a very lengthy function call.
// We use a macro VAL() to shorten it.
#define VAL(x) ( static_cast< float >( ModelerApplication::Instance()->GetControlValue( x ) ) )

ModelerView::ModelerView(int x, int y, int w, int h,
			 const char *label):Fl_Gl_Window(x, y, w, h, label)
{
    m_camera = new Camera();	

    m_camera->SetDimensions( w, h );
    m_camera->SetDistance( 35 );
    m_camera->SetCenter( Vector3f( 0.5, 0.5, 0.5 ) );

    houseLightOn = true;

    // set up house/ambient lighting
    GLfloat Lt0color[] = {1.0,1.0,1.0,1.0};
    GLfloat Lt0pos[] = {0.0,-2.0,10.0,1.0};
    GLfloat Lt0dir[] = {0.0, 0.0, -4.0};
    GLfloat Lt0cutoff[] = {180.0};
    HouseLight house0 = HouseLight(Lt0color, Lt0pos, Lt0dir, Lt0cutoff);
    houseLights.push_back(house0);

    GLfloat Lt1color[] = {1.0,1.0,1.0,1.0};
    GLfloat Lt1pos[] = {-10.0,15.0,25.0,1.0};
    GLfloat Lt1dir[] = {5.0, 1.0, -1.0};
    GLfloat Lt1cutoff[] = {120.0};
    HouseLight house1 = HouseLight(Lt1color, Lt1pos, Lt1dir, Lt1cutoff);
    houseLights.push_back(house1);

    GLfloat Lt2color[] = {1.0,1.0,1.0,1.0};
    GLfloat Lt2pos[] = {0.0,5.0,-5.0,1.0};
    GLfloat Lt2dir[] = {0.0, -1.0, 1.0};
    GLfloat Lt2cutoff[] = {180.0};
    HouseLight house2 = HouseLight(Lt2color, Lt2pos, Lt2dir, Lt2cutoff);
    houseLights.push_back(house2);

    GLfloat Lt3color[] = {1.0,1.0,1.0,1.0};
    GLfloat Lt3pos[] = {10.0,15.0,25.0,1.0};
    GLfloat Lt3dir[] = {-5.0, 1.0, -1.0};
    GLfloat Lt3cutoff[] = {120.0};
    HouseLight house3 = HouseLight(Lt3color, Lt3pos, Lt3dir, Lt3cutoff);
    houseLights.push_back(house3);

    // set up spots/washes
    // frontlight
    GLfloat Lt4color[] = {1.0,1.0,1.0,1.0};
    GLfloat Lt4pos[] = {0.0,0.0,10.0,1.0};
    GLfloat Lt4dir[] = {0.0, 0.2, -1.0};
    GLfloat Lt4cutoff[] = {36.0};
    EllipsoidalLight spot0 = EllipsoidalLight(Lt4color, Lt4pos, Lt4dir, Lt4cutoff);
    spotLights.push_back(spot0);

    GLfloat Lt5color[] = {1.0,1.0,1.0,1.0};
    GLfloat Lt5pos[] = {-2.0,-3.0,10.0,1.0};
    GLfloat Lt5dir[] = {0.3, 0.2, -1.0};
    GLfloat Lt5cutoff[] = {36.0};
    EllipsoidalLight spot1 = EllipsoidalLight(Lt5color, Lt5pos, Lt5dir, Lt5cutoff);
    spotLights.push_back(spot1);

    GLfloat Lt6color[] = {1.0,1.0,1.0,1.0};
    GLfloat Lt6pos[] = {2.0,-3.0,10.0,1.0};
    GLfloat Lt6dir[] = {-0.3, 0.2, -1.0};
    GLfloat Lt6cutoff[] = {36.0};
    EllipsoidalLight spot2 = EllipsoidalLight(Lt6color, Lt6pos, Lt6dir, Lt6cutoff);
    spotLights.push_back(spot2);

    // backlight
    GLfloat Lt7color[] = {1.0,1.0,1.0,1.0};
    GLfloat Lt7pos[] = {0.0, 5.0, 0.0,1.0};
    GLfloat Lt7dir[] = {0.0, -0.1, 1.0};
    GLfloat Lt7cutoff[] = {50.0};
    EllipsoidalLight backlight0 = EllipsoidalLight(Lt7color, Lt7pos, Lt7dir, Lt7cutoff);
    spotLights.push_back(backlight0);

    GLfloat Lt8color[] = {1.0,1.0,1.0,1.0};
    GLfloat Lt8pos[] = {-2.0, 3.0,-5.0,1.0};
    GLfloat Lt8dir[] = {0.3, -0.2, 1.0};
    GLfloat Lt8cutoff[] = {50.0};
    EllipsoidalLight backlight1 = EllipsoidalLight(Lt8color, Lt8pos, Lt8dir, Lt8cutoff);
    spotLights.push_back(backlight1);

    GLfloat Lt9color[] = {1.0,1.0,1.0,1.0};
    GLfloat Lt9pos[] = {2.0,5.0,-5.0,1.0};
    GLfloat Lt9dir[] = {-0.3, -0.2, 1.0};
    GLfloat Lt9cutoff[] = {50.0};
    EllipsoidalLight backlight2 = EllipsoidalLight(Lt9color, Lt9pos, Lt9dir, Lt9cutoff);
    spotLights.push_back(backlight2);

    // toplight
    GLfloat Lt10color[] = {1.0,1.0,1.0,1.0};
    GLfloat Lt10pos[] = {6.0, 5.0, 0.0,1.0};
    GLfloat Lt10dir[] = {0.0, -1.0, 0.2};
    GLfloat Lt10cutoff[] = {50.0};
    EllipsoidalLight toplight0 = EllipsoidalLight(Lt10color, Lt10pos, Lt10dir, Lt10cutoff);
    spotLights.push_back(toplight0);

    GLfloat Lt11color[] = {1.0, 1.0, 1.0,1.0};
    GLfloat Lt11pos[] = {-6.0, 5.0, 0.0,1.0};
    GLfloat Lt11dir[] = {0.0, -1.0, 0.2};
    GLfloat Lt11cutoff[] = {50.0};
    EllipsoidalLight toplight1 = EllipsoidalLight(Lt11color, Lt11pos, Lt11dir, Lt11cutoff);
    spotLights.push_back(toplight1);
}

ModelerView::~ModelerView()
{
    delete m_camera;
}

// passes some things to the SetDesign
void ModelerView::loadModel(int argc, char* argv[]) {
    model.load(argc, argv);

    argcc = argc;
    argvv = argv;
}

// keyboard and mouse handlers
int ModelerView::handle( int event )
{
    unsigned eventCoordX = Fl::event_x();
    unsigned eventCoordY = Fl::event_y();
    unsigned eventButton = Fl::event_button();
    unsigned eventState  = Fl::event_state();	

    switch( event )
    {
	case FL_PUSH:
	{
	    switch (eventButton)
	    {
		case FL_LEFT_MOUSE:
		    m_camera->MouseClick( Camera::LEFT, eventCoordX, eventCoordY );
		    break;

		case FL_MIDDLE_MOUSE:
		    m_camera->MouseClick( Camera::MIDDLE, eventCoordX, eventCoordY );
		    break;

		case FL_RIGHT_MOUSE:
		    m_camera->MouseClick( Camera::RIGHT, eventCoordX, eventCoordY );
		    break;
	     }
	}
	break;

	case FL_DRAG:
	{
	    m_camera->MouseDrag(eventCoordX, eventCoordY);
	}
	break;

        case FL_RELEASE:
	{
            m_camera->MouseRelease(eventCoordX, eventCoordY);
	}
	break;	

        case FL_KEYUP:
        {
	    unsigned key = Fl::event_key();
    	    if (key == 'l') {
		// turn off/on the theatrical light and turn on/off the ambient house light
		houseLightOn = !houseLightOn;
		cout << "houseLightOn is now: " << houseLightOn << endl;
	    } else if (key == 'h') {
		// turns on/off houselights
		// if house are on, all others are off
		// when turned off, turns back previously on lights
		houseLightOn = !houseLightOn;
	    } else if (key == '0') {
		// turns on/off spot0
		spotLights[0].toggleOn();
		if(spotLights[0].isOn()) {
		    glEnable( GL_LIGHT4 );
		} else {
		    glDisable( GL_LIGHT4 );
		}
	    } else if (key == '1') {
		// turns on/off spot1
		spotLights[1].toggleOn();
		if(spotLights[1].isOn()) {
		    glEnable( GL_LIGHT5 );
		} else {
		    glDisable( GL_LIGHT5 );
		}
	    } else if (key == '2') {
		// turns on/off spot2
		spotLights[2].toggleOn();
		if(spotLights[2].isOn()) {
		    glEnable( GL_LIGHT6 );
		} else {
		    glDisable( GL_LIGHT6 );
		}
	    } else if (key == '3') {
		// turns on/off backlight0
		spotLights[3].toggleOn();
		if(spotLights[3].isOn()) {
		    glEnable( GL_LIGHT7 );
		} else {
		    glDisable( GL_LIGHT7 );
		}
	    } else if (key == '4') {
		// turns on/off backlight1
		spotLights[4].toggleOn();
		if(spotLights[4].isOn()) {
		    glEnable( GL_LIGHT2 );
		} else {
		    glDisable( GL_LIGHT2 );
		}
	    } else if (key == '5') {
		// turns on/off backlight1
		spotLights[5].toggleOn();
		if(spotLights[5].isOn()) {
		    glEnable( GL_LIGHT3 );
		} else {
		    glDisable( GL_LIGHT3 );
		}
	    } else if (key == '6') {
		// turns on/off backlight1
		spotLights[6].toggleOn();
		if(spotLights[6].isOn()) {
		    glEnable( GL_LIGHT1 );
		} else {
		    glDisable( GL_LIGHT1 );
		}
	    } else if (key == '7') {
		// turns on/off backlight1
		spotLights[7].toggleOn();
		if(spotLights[7].isOn()) {
		    glEnable( GL_LIGHT0 );
		} else {
		    glDisable( GL_LIGHT0 );
		}
	    }
    	}
	break;

        default:
	    return 0;
    }

    // why is this redraw and not draw???
    redraw();
    return 1;
}

void ModelerView::update()
{
    // update the lights from sliders
    updateLights();

    // not sure if these are necessary
    //model.draw( m_camera->viewMatrix());
    //drawAxes();
}

// rewrite this to get 
void ModelerView::updateLights()
{
    for(unsigned int lightNo = 0; lightNo < 8; lightNo++)
    {
	float color = VAL( lightNo * 3 );
	float pan = VAL( lightNo * 3 + 1 );
	float tilt = VAL( lightNo * 3 + 2 );

	vector<float> col;

	float red = fmod(color, 10);
	col.push_back(red);
	color = color / 10.0;
	float green = fmod(color, 10);
	col.push_back(green);
	color = color / 10.0;
	float blue = fmod(color, 10);
	col.push_back(blue);

	col.push_back(1.0); // required for GLfloat array of length 4
	spotLights[lightNo].setSpotColor(col);
	spotLights[lightNo].setSpotDir(pan, tilt);
    }
}


// Call the draw function of the parent.  This sets up the
// viewport, projection, and camera position, as well as some
// default lighting parameters.
void ModelerView::draw()
{
    // Window is !valid() upon resize
    // FLTK convention has you initializing rendering here.
    if( !valid() )
    {
        // Setup opengl
        glShadeModel( GL_SMOOTH );
        glEnable( GL_DEPTH_TEST );
        glEnable( GL_LIGHTING );
        glEnable( GL_NORMALIZE );
        
        m_camera->SetDimensions(w(),h());
        m_camera->SetViewport(0,0,w(),h());
        m_camera->ApplyViewport();
        
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        m_camera->SetPerspective( 50.0f );
        glLoadMatrixf( m_camera->projectionMatrix() );
    }
        
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Load the camera view matrix
    glLoadMatrixf( m_camera->viewMatrix() );

    // Note that IF the lighting is applied *before* applying the camera
    // transform, THEN the light appears fixed on the camera.   

    // actually turn on lights
    // can't figure out how to make this be a loop...
    if (houseLightOn) {
	// first house light
	glEnable( GL_LIGHT0 );
	glLightfv(GL_LIGHT0, GL_AMBIENT, houseLights[0].getColor());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, houseLights[0].getColor());
	glLightfv(GL_LIGHT0, GL_SPECULAR, houseLights[0].getColor());
        glLightfv(GL_LIGHT0, GL_POSITION, houseLights[0].getPos());
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, houseLights[0].getSpotCutoff());
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, houseLights[0].getSpotDir());

	// second house light
	glEnable( GL_LIGHT1 );
	glLightfv(GL_LIGHT1, GL_AMBIENT, houseLights[1].getColor());
	glLightfv(GL_LIGHT1, GL_DIFFUSE, houseLights[1].getColor());
	glLightfv(GL_LIGHT1, GL_SPECULAR, houseLights[1].getColor());
        glLightfv(GL_LIGHT1, GL_POSITION, houseLights[1].getPos());
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, houseLights[1].getSpotCutoff());
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, houseLights[1].getSpotDir());

	// third house light
	glEnable( GL_LIGHT2 );
	glLightfv(GL_LIGHT2, GL_AMBIENT, houseLights[2].getColor());
	glLightfv(GL_LIGHT2, GL_DIFFUSE, houseLights[2].getColor());
	glLightfv(GL_LIGHT2, GL_SPECULAR, houseLights[2].getColor());
        glLightfv(GL_LIGHT2, GL_POSITION, houseLights[2].getPos());
	glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, houseLights[2].getSpotCutoff());
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, houseLights[2].getSpotDir());

	// fourth house light
	glEnable( GL_LIGHT3 );
	glLightfv(GL_LIGHT3, GL_AMBIENT, houseLights[3].getColor());
	glLightfv(GL_LIGHT3, GL_DIFFUSE, houseLights[3].getColor());
	glLightfv(GL_LIGHT3, GL_SPECULAR, houseLights[3].getColor());
        glLightfv(GL_LIGHT3, GL_POSITION, houseLights[3].getPos());
	glLightfv(GL_LIGHT3, GL_SPOT_CUTOFF, houseLights[3].getSpotCutoff());
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, houseLights[3].getSpotDir());

	// disable spots and washes
	glDisable( GL_LIGHT4 );
	glDisable( GL_LIGHT5 );
	glDisable( GL_LIGHT6 );
	glDisable( GL_LIGHT7 );
    } else {
	// turn off house
	glDisable( GL_LIGHT0 );
	glDisable( GL_LIGHT1 );
	glDisable( GL_LIGHT2 );
	glDisable( GL_LIGHT3 );

	// turn on the other lights that are on
	if (spotLights[0].isOn()) {
	    cout << "0 on, ";
	    glEnable( GL_LIGHT4 );
	    glLightfv(GL_LIGHT4, GL_AMBIENT, spotLights[0].getColor());
	    glLightfv(GL_LIGHT4, GL_DIFFUSE, spotLights[0].getColor());
	    glLightfv(GL_LIGHT4, GL_SPECULAR, spotLights[0].getColor());
            glLightfv(GL_LIGHT4, GL_POSITION, spotLights[0].getPos());
	    glLightfv(GL_LIGHT4, GL_SPOT_CUTOFF, spotLights[0].getSpotCutoff());
	    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spotLights[0].getSpotDir());
	}
	if (spotLights[1].isOn()) {
	    cout << "1 on, ";
	    glEnable( GL_LIGHT5 );
	    glLightfv(GL_LIGHT5, GL_AMBIENT, spotLights[1].getColor());
	    glLightfv(GL_LIGHT5, GL_DIFFUSE, spotLights[1].getColor());
	    glLightfv(GL_LIGHT5, GL_SPECULAR, spotLights[1].getColor());
            glLightfv(GL_LIGHT5, GL_POSITION, spotLights[1].getPos());
	    glLightfv(GL_LIGHT5, GL_SPOT_CUTOFF, spotLights[1].getSpotCutoff());
	    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spotLights[1].getSpotDir());
	}
	if (spotLights[2].isOn()) {
	    cout << "2 on, ";
	    glEnable( GL_LIGHT6 );
	    glLightfv(GL_LIGHT6, GL_AMBIENT, spotLights[2].getColor());
	    glLightfv(GL_LIGHT6, GL_DIFFUSE, spotLights[2].getColor());
	    glLightfv(GL_LIGHT6, GL_SPECULAR, spotLights[2].getColor());
            glLightfv(GL_LIGHT6, GL_POSITION, spotLights[2].getPos());
	    glLightfv(GL_LIGHT6, GL_SPOT_CUTOFF, spotLights[2].getSpotCutoff());
	    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spotLights[2].getSpotDir());
	}
	if (spotLights[3].isOn()) {
	    cout << "3 on, ";
	    glEnable( GL_LIGHT7 );
	    glLightfv(GL_LIGHT7, GL_AMBIENT, spotLights[3].getColor());
	    glLightfv(GL_LIGHT7, GL_DIFFUSE, spotLights[3].getColor());
	    glLightfv(GL_LIGHT7, GL_SPECULAR, spotLights[3].getColor());
            glLightfv(GL_LIGHT7, GL_POSITION, spotLights[3].getPos());
	    glLightfv(GL_LIGHT7, GL_SPOT_CUTOFF, spotLights[3].getSpotCutoff());
	    glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, spotLights[3].getSpotDir());
	}
	if (spotLights[4].isOn()) {
	    cout << "4 on, ";
	    glEnable( GL_LIGHT2 );
	    glLightfv(GL_LIGHT2, GL_AMBIENT, spotLights[4].getColor());
	    glLightfv(GL_LIGHT2, GL_DIFFUSE, spotLights[4].getColor());
	    glLightfv(GL_LIGHT2, GL_SPECULAR, spotLights[4].getColor());
            glLightfv(GL_LIGHT2, GL_POSITION, spotLights[4].getPos());
	    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spotLights[4].getSpotCutoff());
	    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotLights[4].getSpotDir());
	}
	if (spotLights[5].isOn()) {
	    cout << "5 on, ";
	    glEnable( GL_LIGHT3 );
	    glLightfv(GL_LIGHT3, GL_AMBIENT, spotLights[5].getColor());
	    glLightfv(GL_LIGHT3, GL_DIFFUSE, spotLights[5].getColor());
	    glLightfv(GL_LIGHT3, GL_SPECULAR, spotLights[5].getColor());
            glLightfv(GL_LIGHT3, GL_POSITION, spotLights[5].getPos());
	    glLightfv(GL_LIGHT3, GL_SPOT_CUTOFF, spotLights[5].getSpotCutoff());
	    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotLights[5].getSpotDir());
	}
	if (spotLights[6].isOn()) {
	    cout << "6 on, ";
	    glEnable( GL_LIGHT1 );
	    glLightfv(GL_LIGHT1, GL_AMBIENT, spotLights[6].getColor());
	    glLightfv(GL_LIGHT1, GL_DIFFUSE, spotLights[6].getColor());
	    glLightfv(GL_LIGHT1, GL_SPECULAR, spotLights[6].getColor());
            glLightfv(GL_LIGHT1, GL_POSITION, spotLights[6].getPos());
	    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spotLights[6].getSpotCutoff());
	    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotLights[6].getSpotDir());
	}
	if (spotLights[7].isOn()) {
	    cout << "7 on";
	    glEnable( GL_LIGHT0 );
	    glLightfv(GL_LIGHT0, GL_AMBIENT, spotLights[7].getColor());
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, spotLights[7].getColor());
	    glLightfv(GL_LIGHT0, GL_SPECULAR, spotLights[7].getColor());
            glLightfv(GL_LIGHT0, GL_POSITION, spotLights[7].getPos());
	    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spotLights[7].getSpotCutoff());
	    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotLights[7].getSpotDir());
	}
	cout << endl;
	cout.flush();
    }


    // These are just some default material colors
    GLfloat diffColor[] = {0.4f, 0.4f, 0.4f, 1.f};
    GLfloat specColor[] = {0.6f, 0.6f, 0.6f, 1.f};
    GLfloat shininess[] = {20.0f};
    
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColor );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specColor );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, shininess );



    model.draw( m_camera->viewMatrix());
    //drawAxes();
}

// used for testing
void ModelerView::drawAxes()
{
	glDisable( GL_LIGHTING );
	glBegin( GL_LINES );

	glColor3f( 1, 0, 0 );
	glVertex3f( 0, 0, 0 );
	glVertex3f( 1, 0, 0 );

	glColor3f( 0, 1, 0 );
	glVertex3f( 0, 0, 0 );
	glVertex3f( 0, 1, 0 );

	glColor3f( 0, 0, 1 );
	glVertex3f( 0, 0, 0 );
	glVertex3f( 0, 0, 1 );

	glEnd();
	glEnable( GL_LIGHTING );
}

