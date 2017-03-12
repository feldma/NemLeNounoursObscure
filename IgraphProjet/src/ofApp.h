#pragma once

#include <windows.h>
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
private:
	// scene
	std::vector<of3dPrimitive> m_scene;
	std::vector<ofImage> m_imagesOpen;
	ofImage m_background;
	bool m_backgroundAllowed;

	//camera
	ofCamera m_camera;
	bool m_right;
	bool m_left;
	ofVec3f m_lookAt;
	ofVec2f m_lastMouse;

	//opening files
	std::vector<std::string> m_images;
	void loadImage();

	//gui
	ofxDatGui *m_gui;
	ofxDatGuiScrollView *m_scrollView;
	bool m_hideMenu;

	void buttonEvent(ofxDatGuiButtonEvent e);
	void dropdownEvent(ofxDatGuiDropdownEvent e);

	//mode
	bool m_3d;
	bool m_dessin;
	bool m_primitive;

	ofVec2f m_lastMouseForDrawing;
};
