GUI& GUI::Instance(int w, int h) {
	if(instance != nullptr && (w == -1 && h == -1)) {
		return *instance;
	}
	if(instance != nullptr && w != -1 && h != -1) {
		throw "Runtime resize!";
	}
	if(instance == nullptr && (w == -1 || h == -1)) {
		throw "No window size set!";
	}
	else {
		instance = new GUI(w, h);
		return *instance;
	}
}

void GUI::onDisplay() {
	instance->draw();
}

void GUI::onMouse(int button, int state, int x, int y) {
	instance->mouse(button, state, x, y);
}

GUI* GUI::instance = nullptr;
