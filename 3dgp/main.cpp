#include <iostream>
#include <GL/glew.h>
#include <3dgl/3dgl.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

// Include GLM core features
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#pragma comment (lib, "glew32.lib")

using namespace std;
using namespace _3dgl;
using namespace glm;

<<<<<<< HEAD
bool TurnOnlamp1;
bool TurnOnlamp2;

// 3D models 
=======
// 3D models //nice
>>>>>>> parent of dcb7dda (Task4)
C3dglModel camera;
C3dglModel table;
C3dglModel lamp1;
C3dglModel lamp2;
C3dglModel vase;

C3dglBitmap bm;

GLuint oak;
GLuint cloth;
GLuint idTexNone;

// The View Matrix
mat4 matrixView;

// Camera & navigation
float maxspeed = 4.f;	// camera max speed
float accel = 4.f;		// camera acceleration
vec3 _acc(0), _vel(0);	// camera acceleration and velocity vectors
float _fov = 60.f;		// field of view (zoom)

bool init()
{
	// rendering states
	glEnable(GL_DEPTH_TEST);	// depth test is necessary for most 3D scenes
	glEnable(GL_NORMALIZE);		// normalization is needed by AssImp library models
	glShadeModel(GL_SMOOTH);	// smooth shading mode is the default one; try GL_FLAT here!
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// this is the default one; try GL_LINE!

	// setup lighting
	glEnable(GL_LIGHTING);									// --- DEPRECATED
	glEnable(GL_LIGHT0);									// --- DEPRECATED

	// load your 3D models here!
<<<<<<< HEAD
	if (!vertexShader.create(GL_VERTEX_SHADER)) return false;
	if (!vertexShader.loadFromFile("shaders/basic.vert")) return false;
	if (!vertexShader.compile()) return false;

	if (!fragmentShader.create(GL_FRAGMENT_SHADER)) return false;
	if (!fragmentShader.loadFromFile("shaders/basic.frag")) return false;
	if (!fragmentShader.compile()) return false;


	if (!program.create()) return false;
	if (!program.attach(vertexShader)) return false;
	if (!program.attach(fragmentShader)) return false;
	if (!program.link()) return false;
	if (!program.use(true)) return false;

	bm.load("models/oak.bmp", GL_RGBA);
	if (!bm.getBits()) return false;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &oak);
	glBindTexture(GL_TEXTURE_2D, oak);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bm.getWidth(), bm.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bm.getBits());

	bm.load("models/cloth.bmp", GL_RGBA);
	if (!bm.getBits()) return false;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &cloth);
	glBindTexture(GL_TEXTURE_2D, cloth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bm.getWidth(), bm.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bm.getBits());

	// glut additional setup
	glutSetVertexAttribCoord3(program.getAttribLocation("aVertex"));
	glutSetVertexAttribNormal(program.getAttribLocation("aNormal"));

	// prepare vertex data
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// prepare normal data
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);


	// prepare indices array
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


=======
>>>>>>> parent of dcb7dda (Task4)
	if (!table.load("models\\table.obj")) return false;
	if (!lamp1.load("models\\lamp.obj")) return false;
	if (!lamp2.load("models\\lamp.obj")) return false;
	if (!vase.load("models\\vase.obj")) return false;

<<<<<<< HEAD
	
	program.sendUniform("lightAmbient.color", vec3(0.1, 0.1, 0.1));


	program.sendUniform("lightEmissive", vec3(0, 0, 0));

	program.sendUniform("materialAmbient", vec3(1.0, 1.0, 1.0));
	program.sendUniform("lightDir.direction", vec3(1.0, 0.5, 1.0));
	program.sendUniform("lightDir.diffuse", vec3(0.2, 0.2, 0.2)); // dimmed white light

	program.sendUniform("lightPoint1.position", vec3(1.22f, 5.0f, -1.4f));
	program.sendUniform("lightPoint1.diffuse", vec3(0, 0, 0));
	program.sendUniform("lightPoint1.specular", vec3(0, 0, 0));

	program.sendUniform("lightPoint2.position", vec3(4.93f, 5.03f, 1.57f));
	program.sendUniform("lightPoint2.diffuse", vec3(0, 0, 0));
	program.sendUniform("lightPoint2.specular", vec3(0, 0, 0));

	program.sendUniform("materialSpecular", vec3(0, 0, 0));
	program.sendUniform("shininess", 10);


=======
>>>>>>> parent of dcb7dda (Task4)
	// Initialise the View Matrix (initial position of the camera)
	matrixView = rotate(mat4(1), radians(12.f), vec3(1, 0, 0));
	matrixView *= lookAt(
		vec3(0.0, 5.0, 10.0),
		vec3(0.0, 5.0, 0.0),
		vec3(0.0, 1.0, 0.0));

	// setup the screen background colour
	glClearColor(0.18f, 0.25f, 0.22f, 1.0f);   // deep grey background

	cout << endl;
	cout << "Use:" << endl;
	cout << "  WASD or arrow key to navigate" << endl;
	cout << "  QE or PgUp/Dn to move the camera up and down" << endl;
	cout << "  Shift to speed up your movement" << endl;
	cout << "  Drag the mouse to look around" << endl;
	cout << endl;

	return true;
}

void renderScene(mat4& matrixView, float time, float deltaTime)
{
	mat4 m;

<<<<<<< HEAD
	//Pyramid 
	m = matrixView;
	m = translate(m, vec3(1.1f, 4.5f, 1.0f));
	m = rotate(m, radians(180.f), vec3(0.0f, 1.0f, 90.0f));
	m = scale(m, vec3(0.1f, 0.1f, 0.1f));
	program.sendUniform("matrixModelView", m);

	// Get Attribute Locations
	GLuint attribVertex = program.getAttribLocation("aVertex");
	GLuint attribNormal = program.getAttribLocation("aNormal");


	// Enable vertex attribute arrays
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribNormal);


	// Bind (activate) the vertex buffer and set the pointer to it
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 0, 0);


	// Bind (activate) the normal buffer and set the pointer to it
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);


	// Draw triangles � using index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);


	// Disable arrays
	glDisableVertexAttribArray(attribVertex);
	glDisableVertexAttribArray(attribNormal);

	if (TurnOnlamp1)
	{
		cout << "lamp1" << endl;
		program.sendUniform("lightPoint1.diffuse", vec3(1, 1, 1));
		program.sendUniform("lightPoint1.specular", vec3(1.0, 1.0, 1.0));
	}
	else
	{


		program.sendUniform("lightPoint1.diffuse", vec3(0, 0, 0));
		program.sendUniform("lightPoint1.specular", vec3(0, 0, 0));
	}

	if (TurnOnlamp2)
	{
		cout << "lamp2" << endl;
		program.sendUniform("lightPoint2.diffuse", vec3(1, 1, 1));
		program.sendUniform("lightPoint2.specular", vec3(1.0, 1.0, 1.0));
	}
	else
	{

		program.sendUniform("lightPoint2.diffuse", vec3(0, 0, 0));
		program.sendUniform("lightPoint2.specular", vec3(0, 0, 0));
	}


	//bulb
	m = matrixView;
	m = translate(m, vec3(1.22f, 5.0f, -1.4f));
	m = scale(m, vec3(0.09f, 0.09f, 0.09f));
	program.sendUniform("matrixModelView", m);
	glutSolidSphere(1, 32, 32);
=======
	// setup materials - grey
	GLfloat rgbaGrey[] = { 0.6f, 0.6f, 0.6f, 1.0f };		// --- DEPRECATED
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rgbaGrey);	// --- DEPRECATED
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, rgbaGrey);	// --- DEPRECATED
>>>>>>> parent of dcb7dda (Task4)

	m = matrixView;
	m = translate(m, vec3(4.93f, 5.03f, 1.57f));
	m = scale(m, vec3(0.09f, 0.09f, 0.09f));
	program.sendUniform("matrixModelView", m);
	glutSolidSphere(1, 32, 32);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, oak);

	//table
	m = matrixView;
	m = translate(m, vec3(3.0f, 0, 0.0f));
	m = rotate(m, radians(180.f), vec3(0.0f, 1.0f, 0.0f));
	m = scale(m, vec3(0.005f, 0.005f, 0.005f));
	table.render(1,m);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cloth);

	//chairs
	m = matrixView;
	m = translate(m, vec3(3.0f, 0, 0.0f));
	m = rotate(m, radians(180.f), vec3(0.0f, 1.0f, 0.0f));
	m = scale(m, vec3(0.005f, 0.005f, 0.005f));
	table.render(0,m);
	m = matrixView;
	m = translate(m, vec3(3.0f, 0, 0.0f));
	m = rotate(m, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	m = scale(m, vec3(0.005f, 0.005f, 0.005f));
	table.render(0, m);
	m = matrixView;
	m = translate(m, vec3(3.0f, 0, 0.0f));
	m = rotate(m, radians(0.f), vec3(0.0f, 1.0f, 0.0f));
	m = scale(m, vec3(0.005f, 0.005f, 0.005f));
	table.render(0, m);
	m = matrixView;
	m = translate(m, vec3(3.0f, 0, 0.0f));
	m = rotate(m, radians(270.f), vec3(0.0f, 1.0f, 0.0f));
	m = scale(m, vec3(0.005f, 0.005f, 0.005f));
	table.render(0, m);

	glGenTextures(1, &idTexNone);
	glBindTexture(GL_TEXTURE_2D, idTexNone);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	BYTE bytes[] = { 255, 255, 255 };
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_BGR, GL_UNSIGNED_BYTE, &bytes);

	//vase
	m = matrixView;
	m = translate(m, vec3(3.0f, 3.8f, 0.0f));
	m = rotate(m, radians(-20.0f), vec3(0.0f, 1.0f, 0.0f));
	m = scale(m, vec3(0.09f, 0.09f, 0.091f));
	vase.render(m);

	//lamp
	m = matrixView;
	m = translate(m, vec3(5.6f, 3.8f, 1.8f));
	m = rotate(m, radians(-20.0f), vec3(0.0f, 1.0f, 0.0f));
	m = scale(m, vec3(0.02f, 0.02f, 0.02f));
	lamp1.render(m);

	m = matrixView;
	m = translate(m, vec3(0.5f, 3.8f, -1.4f));
	m = rotate(m, radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
	m = scale(m, vec3(0.02f, 0.02f, 0.02f));
	lamp2.render(m);


	// setup materials - blue
	GLfloat rgbaBlue[] = { 0.2f, 0.2f, 0.8f, 1.0f };		// --- DEPRECATED
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rgbaBlue);	// --- DEPRECATED
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, rgbaBlue);	// --- DEPRECATED

	// teapot
	m = matrixView;
	m = translate(m, vec3(5.5f, 4.1f, 0.70f));
	m = rotate(m, radians(120.f), vec3(0.0f, 1.0f, 0.0f));
	m = scale(m, vec3(0.2f, 0.2f, 0.2f));
	// the GLUT objects require the Model View Matrix setup
	glMatrixMode(GL_MODELVIEW);								// --- DEPRECATED
	glLoadIdentity();										// --- DEPRECATED
	glMultMatrixf((GLfloat*)&m);							// --- DEPRECATED
	glutSolidTeapot(2.0);
}

void onRender()
{
	// these variables control time & animation
	static float prev = 0;
	float time = glutGet(GLUT_ELAPSED_TIME) * 0.001f;	// time since start in seconds
	float deltaTime = time - prev;						// time since last frame
	prev = time;										// framerate is 1/deltaTime

	// clear screen and buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup the View Matrix (camera)
	_vel = clamp(_vel + _acc * deltaTime, -vec3(maxspeed), vec3(maxspeed));
	float pitch = getPitch(matrixView);
	matrixView = rotate(translate(rotate(mat4(1),
		pitch, vec3(1, 0, 0)),	// switch the pitch off
		_vel * deltaTime),		// animate camera motion (controlled by WASD keys)
		-pitch, vec3(1, 0, 0))	// switch the pitch on
		* matrixView;

<<<<<<< HEAD
	// setup View Matrix
	program.sendUniform("matrixView", matrixView);

=======
>>>>>>> parent of dcb7dda (Task4)
	// render the scene objects
	renderScene(matrixView, time, deltaTime);

	// essential for double-buffering technique
	glutSwapBuffers();

	// proceed the animation
	glutPostRedisplay();
}

// called before window opened or resized - to setup the Projection Matrix
void onReshape(int w, int h)
{
	float ratio = w * 1.0f / h;      // we hope that h is not zero
	glViewport(0, 0, w, h);
	mat4 matrixProjection = perspective(radians(_fov), ratio, 0.02f, 1000.f);

	// Setup the Projection Matrix
	glMatrixMode(GL_PROJECTION);							// --- DEPRECATED
	glLoadIdentity();										// --- DEPRECATED
	glMultMatrixf((GLfloat*)&matrixProjection);				// --- DEPRECATED
}

// Handle WASDQE keys
void onKeyDown(unsigned char key, int x, int y)
{
	switch (tolower(key))
	{
	case 'w': _acc.z = accel; break;
	case 's': _acc.z = -accel; break;
	case 'a': _acc.x = accel; break;
	case 'd': _acc.x = -accel; break;
	case 'e': _acc.y = accel; break;
	case 'q': _acc.y = -accel; break;
	case '1': if (!TurnOnlamp1) TurnOnlamp1 = true; else if (TurnOnlamp1) TurnOnlamp1 = false; break;
	case '2': if (!TurnOnlamp2) TurnOnlamp2 = true; else if (TurnOnlamp2) TurnOnlamp2 = false; break;
	}
}

// Handle WASDQE keys (key up)
void onKeyUp(unsigned char key, int x, int y)
{
	switch (tolower(key))
	{
	case 'w':
	case 's': _acc.z = _vel.z = 0; break;
	case 'a':
	case 'd': _acc.x = _vel.x = 0; break;
	case 'q':
	case 'e': _acc.y = _vel.y = 0; break;
	}
}

// Handle arrow keys and Alt+F4
void onSpecDown(int key, int x, int y)
{
	maxspeed = glutGetModifiers() & GLUT_ACTIVE_SHIFT ? 20.f : 4.f;
	switch (key)
	{
	case GLUT_KEY_F4:		if ((glutGetModifiers() & GLUT_ACTIVE_ALT) != 0) exit(0); break;
	case GLUT_KEY_UP:		onKeyDown('w', x, y); break;
	case GLUT_KEY_DOWN:		onKeyDown('s', x, y); break;
	case GLUT_KEY_LEFT:		onKeyDown('a', x, y); break;
	case GLUT_KEY_RIGHT:	onKeyDown('d', x, y); break;
	case GLUT_KEY_PAGE_UP:	onKeyDown('q', x, y); break;
	case GLUT_KEY_PAGE_DOWN:onKeyDown('e', x, y); break;
	case GLUT_KEY_F11:		glutFullScreenToggle();
	}
}

// Handle arrow keys (key up)
void onSpecUp(int key, int x, int y)
{
	maxspeed = glutGetModifiers() & GLUT_ACTIVE_SHIFT ? 20.f : 4.f;
	switch (key)
	{
	case GLUT_KEY_UP:		onKeyUp('w', x, y); break;
	case GLUT_KEY_DOWN:		onKeyUp('s', x, y); break;
	case GLUT_KEY_LEFT:		onKeyUp('a', x, y); break;
	case GLUT_KEY_RIGHT:	onKeyUp('d', x, y); break;
	case GLUT_KEY_PAGE_UP:	onKeyUp('q', x, y); break;
	case GLUT_KEY_PAGE_DOWN:onKeyUp('e', x, y); break;
	}
}

// Handle mouse click
void onMouse(int button, int state, int x, int y)
{
	glutSetCursor(state == GLUT_DOWN ? GLUT_CURSOR_CROSSHAIR : GLUT_CURSOR_INHERIT);
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	if (button == 1)
	{
		_fov = 60.0f;
		onReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}
}

// handle mouse move
void onMotion(int x, int y)
{
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);

	// find delta (change to) pan & pitch
	float deltaYaw = 0.005f * (x - glutGet(GLUT_WINDOW_WIDTH) / 2);
	float deltaPitch = 0.005f * (y - glutGet(GLUT_WINDOW_HEIGHT) / 2);

	if (abs(deltaYaw) > 0.3f || abs(deltaPitch) > 0.3f)
		return;	// avoid warping side-effects

	// View = Pitch * DeltaPitch * DeltaYaw * Pitch^-1 * View;
	constexpr float maxPitch = radians(80.f);
	float pitch = getPitch(matrixView);
	float newPitch = glm::clamp(pitch + deltaPitch, -maxPitch, maxPitch);
	matrixView = rotate(rotate(rotate(mat4(1.f),
		newPitch, vec3(1.f, 0.f, 0.f)),
		deltaYaw, vec3(0.f, 1.f, 0.f)), 
		-pitch, vec3(1.f, 0.f, 0.f)) 
		* matrixView;
}

void onMouseWheel(int button, int dir, int x, int y)
{
	_fov = glm::clamp(_fov - dir * 5.f, 5.0f, 175.f);
	onReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

int main(int argc, char **argv)
{
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("3DGL Scene: First Example");

	// init glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		C3dglLogger::log("GLEW Error {}", (const char*)glewGetErrorString(err));
		return 0;
	}
	C3dglLogger::log("Using GLEW {}", (const char*)glewGetString(GLEW_VERSION));

	// register callbacks
	glutDisplayFunc(onRender);
	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecDown);
	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecUp);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	glutMouseWheelFunc(onMouseWheel);

	C3dglLogger::log("Vendor: {}", (const char *)glGetString(GL_VENDOR));
	C3dglLogger::log("Renderer: {}", (const char *)glGetString(GL_RENDERER));
	C3dglLogger::log("Version: {}", (const char*)glGetString(GL_VERSION));
	C3dglLogger::log("");

	// init light and everything � not a GLUT or callback function!
	if (!init())
	{
		C3dglLogger::log("Application failed to initialise\r\n");
		return 0;
	}

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

