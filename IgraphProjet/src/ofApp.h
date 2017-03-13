#pragma once

#include <windows.h>
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxDatGui.h"
#include "ofxAssimpModelLoader.h"

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

	float m_rotateX;
	float m_rotateY;
	float m_rotateZ;
	float m_transformX;
	float m_transformY;
	float m_transformZ;
	float m_scale;

	void applyChanges(of3dPrimitive);
	void applyTransformation(of3dPrimitive);
	void applyRotation(of3dPrimitive);
	void applyScale(of3dPrimitive);

	//camera
	ofCamera m_camera;
	bool m_right;
	bool m_left;
	ofVec3f m_lookAt;
	ofVec2f m_lastMouse;

	//opening files
	std::vector<std::string> m_images;
	ofxAssimpModelLoader m_model;
	void loadImage();
	void loadModel();

	//gui
	ofxDatGui *m_gui;
	ofxDatGui *m_createPrimitive;
	ofxDatGuiScrollView *m_scrollView;
	bool m_hideMenu;

	void buttonEvent(ofxDatGuiButtonEvent e);
	void dropdownEvent(ofxDatGuiDropdownEvent e);
	void sliderEvent(ofxDatGuiSliderEvent e);

	//mode
	bool m_3d;
	bool m_selection;
	bool m_primitive;

	ofVec2f m_lastMouseForDrawing;
};
