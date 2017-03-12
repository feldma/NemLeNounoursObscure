#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(20);
	m_camera.setGlobalPosition(0, 0, 0);
	m_lookAt = m_camera.getLookAtDir();
	m_backgroundAllowed = false;

	ofBoxPrimitive box;

	box.set(20,20,20);
	box.setPosition(0,0,0);	
	m_scene.push_back(box);

	m_gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	m_gui->addButton("Ouvrir image");
	m_gui->addFolder("Images disponibles:", ofColor::white);
	m_gui->addButton("Prendre un screenshot");
	std::vector<std::string> opts = { "3D", "Dessin", "Primitives" };
	m_gui->addDropdown("Options", opts);
	m_gui->onButtonEvent(this, &ofApp::buttonEvent);
	m_gui->onDropdownEvent(this, &ofApp::dropdownEvent);
	m_hideMenu = true;
	m_3d = true;
	m_dessin = false;
	m_primitive = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	m_camera.lookAt(m_lookAt);
}

//--------------------------------------------------------------
void ofApp::draw(){
	m_camera.begin();
	if (m_backgroundAllowed)
		m_background.draw(0,0);
	for (std::vector<of3dPrimitive>::iterator it = m_scene.begin(); it != m_scene.end(); it++)
		it->draw();
	m_camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	std::cout << "event : " << key << std::endl;
	switch (key)
	{
	case OF_KEY_UP:
		m_camera.setPosition(m_camera.getPosition().x, m_camera.getPosition().y, m_camera.getPosition().z - 5);
		m_lookAt.z -= 5;
		break;
	case OF_KEY_DOWN:
		m_camera.setPosition(m_camera.getPosition().x, m_camera.getPosition().y, m_camera.getPosition().z + 5);
		m_lookAt.z += 5;
		break;
	case OF_KEY_LEFT:
		m_camera.setPosition(m_camera.getPosition().x - 5, m_camera.getPosition().y, m_camera.getPosition().z);
		m_lookAt.x -= 5;
		break;
	case OF_KEY_RIGHT:
		m_camera.setPosition(m_camera.getPosition().x + 5, m_camera.getPosition().y, m_camera.getPosition().z);
		m_lookAt.x += 5;
		break;
	case 'h':
		m_hideMenu = !m_hideMenu;
		m_gui->setVisible(m_hideMenu);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (button == 2)
	{
		if (x > m_lastMouse.x)
		{
			m_lookAt.x += 10;
		}
		else
		{
			std::cout << "moins" << std::endl;
			m_lookAt.x -= 10;
		}
	}
	if (button == 0)
	{
		if (y > m_lastMouse.y)
		{
			m_lookAt.y += 10;
		}
		else
		{
			m_lookAt.y -= 10;
		}
		m_lastMouse.x = x;
		m_lastMouse.y = y;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == 0 && m_primitive)
		m_lastMouseForDrawing = ofVec2f(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (button == 0 && m_primitive)
	{
		ofSetHexColor(0xff0000);
		ofFill();
		ofRect(m_lastMouseForDrawing.x, m_lastMouseForDrawing.y, x - m_lastMouseForDrawing.x, y - m_lastMouseForDrawing.y);
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	draw();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::loadImage()
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = "Text Files\0*.txt\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select a File, yo!";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn))
	{
		std::cout << "You chose the file \"" << filename << "\"\n";
		ofImage img;
		img.load(filename);
		m_imagesOpen.push_back(img);
		m_images.push_back(filename);
		m_gui->getFolder("Images disponibles:")->addButton(filename);
	}
}

void ofApp::buttonEvent(ofxDatGuiButtonEvent e)
{
	if (e.target->getLabel() == "Ouvrir image")
		loadImage();
	else if (e.target->getLabel() == "Prendre un screenshot")
	{
		ofImage tmp;

		tmp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
		tmp.save("export.png");
	}
	else
	{
		std::cout << "text" << std::endl;
		m_background.load(m_images[0]);
		m_backgroundAllowed = true;
		ofTexture tex;
		tex.loadData(m_imagesOpen[0].getPixels());
		m_scene[0].mapTexCoordsFromTexture(tex);
	}
}

void ofApp::dropdownEvent(ofxDatGuiDropdownEvent e)
{
	if (e.target->getLabel() == "3D")
	{
		m_3d = true;
		m_dessin = false;
		m_primitive = false;
	}
	if (e.target->getLabel() == "Dessin")
	{
		m_3d = false;
		m_dessin = true;
		m_primitive = false;
	}
	if (e.target->getLabel() == "Primitive")
	{
		m_3d = false;
		m_dessin = false;
		m_primitive = true;
	}
}