#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(20);
	m_camera.setGlobalPosition(0, 0, 5);
	m_lookAt = m_camera.getLookAtDir();
	m_backgroundAllowed = false;

	ofBoxPrimitive box;

	box.set(5,5,5);
	box.setPosition(0,0,0);
	m_scene.push_back(box);

	m_gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	m_gui->addButton("Ouvrir image");
	m_gui->addFolder("Images disponibles:", ofColor::white);
	m_gui->addButton("Prendre un screenshot");
	m_gui->addButton("Importer un modele");
	std::vector<std::string> opts = { "3D", "Selection", "Primitives" };
	m_gui->addDropdown("Options", opts);
	m_gui->onButtonEvent(this, &ofApp::buttonEvent);
	m_gui->addSlider("FOV:", 0, 120);
	m_gui->addSlider("FarClip", 0, 1);
	m_gui->addSlider("NearClip", 0, 1);
	m_gui->addSlider("RotationX", 0, 360);
	m_gui->addSlider("RotationY", 0, 360);
	m_gui->addSlider("RotationZ", 0, 360);
	m_gui->addSlider("TransformationX", -200, 200);
	m_gui->addSlider("TranformationY", -200, 200);
	m_gui->addSlider("TransformationZ", -200, 200);
	m_gui->addSlider("Scale", 0, 10);
	m_gui->onSliderEvent(this, &ofApp::sliderEvent);
	std::vector<std::string> optsCamera = { "4:3", "16:9" };
	m_gui->addDropdown("Ratio d'aspect", optsCamera);

	m_gui->onDropdownEvent(this, &ofApp::dropdownEvent);

	m_createPrimitive = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	m_createPrimitive->addTextInput("X:", "");
	m_createPrimitive->addTextInput("Y:", "");
	m_createPrimitive->addTextInput("Z:", "");
	m_createPrimitive->addTextInput("Taille:", "");
	m_createPrimitive->addTextInput("Hauteur (cone):", "");
	std::vector<std::string> optsCreate = { "Cube", "Sphere", "Cone" };
	m_createPrimitive->addDropdown("Ajouter Element", optsCreate);
	m_createPrimitive->onDropdownEvent(this, &ofApp::dropdownEvent);

	m_rotateX = m_rotateY = m_rotateZ = 90;
	m_transformX = m_transformY = m_transformZ = 0;

	m_hideMenu = true;
	m_3d = true;
	m_selection = false;
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
	{
		applyChanges(*it);
		it->draw();
	}
	m_model.draw(OF_MESH_FILL);
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
	if (button == 2 && m_3d)
	{
		if (x > m_lastMouse.x && m_3d)
			m_lookAt.x -= 0.01;
		else
			m_lookAt.x += 0.01;
		m_lastMouse.x = x;
		if (y > m_lastMouse.y)
			m_lookAt.y -= 0.01;
		else
			m_lookAt.y += 0.01;
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
		//ofPushMatrix();
		//ofSetHexColor(0xff0000);
		//ofFill();
		//ofDrawPlane(m_lastMouseForDrawing.x, m_lastMouseForDrawing.y, x - m_lastMouseForDrawing.x, y - m_lastMouseForDrawing.y);
		//ofPopMatrix();
		//ofPlanePrimitive plane;
		//plane.set(x - m_lastMouseForDrawing.x, y - m_lastMouseForDrawing.y);
		//plane.setPosition(x,y, 0);
		//m_scene.push_back(plane);
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
	ofn.lpstrFilter = "Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select a File";
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

void ofApp::loadModel()
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = "Obj file\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select a File";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn))
	{
		m_model.loadModel(filename, true);
		m_model.calculateDimensions();
		m_model.setPosition(0,0,0);
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
	else if (e.target->getLabel() == "Importer un modele")
		loadModel();
	else
	{
		m_background.load(e.target->getLabel());
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
		m_selection = false;
		m_primitive = false;
		m_createPrimitive->setVisible(true);
	}
	if (e.target->getLabel() == "Dessin")
	{
		m_3d = false;
		m_selection = true;
		m_primitive = false;
		m_createPrimitive->setVisible(false);
	}
	if (e.target->getLabel() == "Primitives")
	{
		m_3d = false;
		m_selection = false;
		m_primitive = true;
		m_createPrimitive->setVisible(false);
	}

	if (e.target->getLabel() == "Cube")
	{
		ofBoxPrimitive box;
		std::string x = m_createPrimitive->getTextInput("X:")->getText();
		std::string y = m_createPrimitive->getTextInput("Y:")->getText();
		std::string z = m_createPrimitive->getTextInput("Z:")->getText();
		std::string size = m_createPrimitive->getTextInput("Taille:")->getText();
		if (x != "" && y != "" && z != "")
		{
			box.setPosition(ofToDouble(x), ofToDouble(y), ofToDouble(z));
			if (size != "")
				box.setScale(ofToDouble(size));
			m_scene.push_back(box);
		}
	}
	if (e.target->getLabel() == "Sphere")
	{
		ofSpherePrimitive sphere;
		std::string x = m_createPrimitive->getTextInput("X:")->getText();
		std::string y = m_createPrimitive->getTextInput("Y:")->getText();
		std::string z = m_createPrimitive->getTextInput("Z:")->getText();
		std::string size = m_createPrimitive->getTextInput("Taille:")->getText();
		if (x != "" && y != "" && z != "")
		{
			sphere.setPosition(ofToDouble(x), ofToDouble(y), ofToDouble(z));
			if (size != "")
				sphere.setRadius(ofToDouble(size));
			m_scene.push_back(sphere);
		}
	}
	if (e.target->getLabel() == "Cone")
	{
		ofConePrimitive cone;
		std::string x = m_createPrimitive->getTextInput("X:")->getText();
		std::string y = m_createPrimitive->getTextInput("Y:")->getText();
		std::string z = m_createPrimitive->getTextInput("Z:")->getText();
		std::string size = m_createPrimitive->getTextInput("Taille:")->getText();
		std::string height = m_createPrimitive->getTextInput("Hauteur")->getText();
		if (x != "" && y != "" && z != "")
		{
			cone.setPosition(ofToDouble(x), ofToDouble(y), ofToDouble(z));
			if (height != "")
				cone.setHeight(ofToDouble(height));
			if (size != "")
				cone.setRadius(ofToDouble(size));
			m_scene.push_back(cone);
		}
	}
	if (e.target->getLabel() == "4:3")
	{
		m_camera.setAspectRatio(4.0f/3.0f);
	}
	if (e.target->getLabel() == "16:9")
	{
		m_camera.setAspectRatio(16.0f/9.0f);
	}
}

void ofApp::sliderEvent(ofxDatGuiSliderEvent e)
{
	if (e.target->getLabel() == "FOV:")
	{
		float fov = m_gui->getSlider("FOV:")->getValue();
		m_camera.setFov(fov);
	}
	if (e.target->getLabel() == "FarClip")
	{
		float farClip = m_gui->getSlider("FarClip")->getValue();
		m_camera.setFarClip(farClip);
	}
	if (e.target->getLabel() == "NearClip")
	{
		float nearClip = m_gui->getSlider("NearClip")->getValue();
		m_camera.setNearClip(nearClip);
	}
	if (e.target->getLabel() == "RotationX")
	{
		m_rotateX = m_gui->getSlider("RotationX")->getValue();
	}
	if (e.target->getLabel() == "RotationY")
	{
		m_rotateY = m_gui->getSlider("RotationY")->getValue();

	}
	if (e.target->getLabel() == "RotationZ")
	{
		m_rotateZ = m_gui->getSlider("RotationZ")->getValue();
	}
	if (e.target->getLabel() == "TransformationX")
	{
		m_transformX = m_gui->getSlider("TransformationX")->getValue();
	}
	if (e.target->getLabel() == "TransformationY")
	{
		m_transformY = m_gui->getSlider("TransformationY")->getValue();
	}
	if (e.target->getLabel() == "TransformationZ")
	{
		m_transformZ = m_gui->getSlider("TransformationZ")->getValue();
	}
	if (e.target->getLabel() == "Scale")
	{
		m_scale = m_gui->getSlider("Scale")->getValue();
	}
}

void ofApp::applyTransformation(of3dPrimitive prim)
{
	prim.setPosition(prim.getGlobalPosition().x + m_transformX, prim.getGlobalPosition().y + m_transformY, prim.getGlobalPosition().z + m_transformZ);
}

void ofApp::applyRotation(of3dPrimitive prim)
{
	prim.rotate(m_rotateX, ofVec3f(1,0,0));
	prim.rotate(m_rotateY, ofVec3f(0,1,0));
	prim.rotate(m_rotateZ, ofVec3f(0,0,1));
}

void ofApp::applyScale(of3dPrimitive prim)
{
	prim.setScale(m_scale);
}

void ofApp::applyChanges(of3dPrimitive prim)
{
	applyTransformation(prim);
	applyRotation(prim);
	applyScale(prim);
}