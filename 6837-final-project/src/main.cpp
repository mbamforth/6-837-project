// 6.837 Final Project
// Miren Bamforth - Fall 2013

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "extra.h"
#include "modelerapp.h"
#include "ModelerView.h"

using namespace std;

int main( int argc, char* argv[] )
{
    if( argc > 1 )
    {
	cout << "You don't need to load a data file with this implementation." << endl;
	return -1;
    }

    // Initialize the controls. Has a ModelerControl for each light as opposed to
    // a controller for each joint as in assignment #2 previously.
    // "You have to define a ModelerControl
    // for every variable name that you define in the enumeration."

    // The constructor for a ModelerControl takes the following arguments:
    // - text label in user interface
    // - minimum slider value
    // - maximum slider value
    // - step size for slider
    // - initial slider value

    // think about whether this should be a constant 
    // Change with UI, commandline, or keyboard? Change in ModelerApplication?
    const int NUM_LIGHTS = 8;

    ModelerControl controls[ NUM_LIGHTS*8 ];
    string lightNames[NUM_LIGHTS]={ "Light0", "Light1", "Light2", "Light3", "Light4", "Light5", "Light6", "Light7"};
    for(unsigned int i = 0; i < NUM_LIGHTS; i++)
    {
	char buf[255];
	sprintf(buf, "%s color", lightNames[i].c_str());
	controls[i*3] = ModelerControl(buf, 0.0, 999.0, 2.5f, 0);
	sprintf(buf, "%s pan", lightNames[i].c_str());
	controls[i*3+1] = ModelerControl(buf, -3.2, 3.2, 0.1f, 0);
	sprintf(buf, "%s tilt", lightNames[i].c_str());
	controls[i*3+2] = ModelerControl(buf, -1.0, 1.0, 0.05f, 0);
    }

    ModelerApplication::Instance()->Init(argc, argv, controls, NUM_LIGHTS*3);

    // Run the modeler application.
    int ret = ModelerApplication::Instance()->Run();

    // This line is reached when you close the program.
    delete ModelerApplication::Instance();

    return ret;
}
