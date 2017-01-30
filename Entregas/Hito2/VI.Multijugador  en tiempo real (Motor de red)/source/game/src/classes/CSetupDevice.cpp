#include "CSetupDevice.h"
#include <iostream>

using namespace std;

class SetupDeviceEventReceiver : public IEventReceiver {

	public:
		SetupDeviceEventReceiver(bool* quit, bool* start) {
			quitSetup = quit;
			startGame = start;
		}

		void setStartButton(gui::IGUIButton* button) {
			playAloneButton = button;
		}

        void setExitButton(gui::IGUIButton* button) {
			exitButton = button;
		}

		virtual bool OnEvent(const SEvent& event) {

			if (event.EventType == EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown) {
				switch(event.KeyInput.Key) {
					case KEY_ESCAPE: {
						// Quit the setup
						if (quitSetup) *quitSetup = true;
						return true;
					}
				}
			} else if (event.EventType == EET_GUI_EVENT) {
				if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED) {
					if (event.GUIEvent.Caller == playAloneButton) {
						if (startGame) *startGame = true;
						if (quitSetup) *quitSetup = true;
						return true;
					}
					if (event.GUIEvent.Caller == exitButton) {
                        if (quitSetup) *quitSetup = true;
						return true;
					}
				}
			}
		return false;

	}

	private:
		gui::IGUIButton* playAloneButton;
		bool* quitSetup;
		bool* startGame;

    private:
		gui::IGUIButton* exitButton;
		bool* quitGame;

};

CSetupDevice::CSetupDevice(const core::dimension2d<u32>& screenDim) {

	startGame = false;
	quitSetup = false;

	// Create a software based device to allow the user to choose some options
	receiver = new SetupDeviceEventReceiver(&quitSetup, &startGame);
	if (!receiver) {
		printf("Failed eventReceiver creation\n");
		setupDevice = NULL;
		return;
	}
	setupDevice = createDevice(video::EDT_OPENGL, screenDim, 24, false, false, true, receiver);
	if (!setupDevice) {
		printf("Failed setupDevice creation\n");
		return;
	}
	setupDevice->run(); // recreating the device makes run() return false first time so call it here so the render loop below won't quit early
	setupDevice->setWindowCaption(L"Setup");

	driver = setupDevice->getVideoDriver();
	gui = setupDevice->getGUIEnvironment();
	gui->getSkin()->setFont(gui->getFont("media/GillSans12.png"));
	// disable gui alpha
	for (s32 i=0; i<gui::EGDC_COUNT ; ++i) {
		video::SColor col = gui->getSkin()->getColor((gui::EGUI_DEFAULT_COLOR)i);
		col.setAlpha(255);
		gui->getSkin()->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
	}

	// add the lovely irrlicht-irrai logo
	//gui->addImage(driver->getTexture("media/irrlichtirrailogo.png"), core::position2di(screenDim.Width-137,screenDim.Height-110), true, NULL);

	// create button to start game
	s32 buttonWidth = 128;
	s32 buttonHeight = 32;
	playAloneButton = gui->addButton(core::rect<s32>((screenDim.Width/2)-(buttonWidth/2),(screenDim.Height-400)-buttonHeight, (screenDim.Width/2)+(buttonWidth/2),screenDim.Height-400));
	video::ITexture* buttonImage = driver->getTexture("media/playAlone_button.png");
	core::dimension2d<u32> buttonDim = buttonImage->getSize();
	playAloneButton->setImage(buttonImage, core::rect<s32>(0, 0, buttonDim.Width, buttonDim.Height));
	video::ITexture* buttonPressedImage = driver->getTexture("media/playAlone_pressed.png");
	core::dimension2d<u32> buttonPressedDim = buttonPressedImage->getSize();
    playAloneButton->setPressedImage(buttonPressedImage, core::rect<s32>(0, 0, buttonPressedDim.Width, buttonPressedDim.Height));
	playAloneButton->setUseAlphaChannel(true);
	receiver->setStartButton(playAloneButton);

	playOnlineButton = gui->addButton(core::rect<s32>((screenDim.Width/2)-(buttonWidth/2),(screenDim.Height-350)-buttonHeight, (screenDim.Width/2)+(buttonWidth/2),screenDim.Height-350));
	buttonImage = driver->getTexture("media/playOnline_button.png");
	playOnlineButton->setImage(buttonImage, core::rect<s32>(0, 0, buttonDim.Width, buttonDim.Height));
	buttonPressedImage = driver->getTexture("media/playOnline_pressed.png");
    playOnlineButton->setPressedImage(buttonPressedImage, core::rect<s32>(0, 0, buttonPressedDim.Width, buttonPressedDim.Height));
	playOnlineButton->setUseAlphaChannel(true);

	achievementsButton = gui->addButton(core::rect<s32>((screenDim.Width/2)-(buttonWidth/2),(screenDim.Height-300)-buttonHeight, (screenDim.Width/2)+(buttonWidth/2),screenDim.Height-300));
	buttonImage = driver->getTexture("media/achievements_button.png");
	achievementsButton->setImage(buttonImage, core::rect<s32>(0, 0, buttonDim.Width, buttonDim.Height));
	buttonPressedImage = driver->getTexture("media/achievements_pressed.png");
    achievementsButton->setPressedImage(buttonPressedImage, core::rect<s32>(0, 0, buttonPressedDim.Width, buttonPressedDim.Height));
	achievementsButton->setUseAlphaChannel(true);

	optionsButton = gui->addButton(core::rect<s32>((screenDim.Width/2)-(buttonWidth/2),(screenDim.Height-250)-buttonHeight, (screenDim.Width/2)+(buttonWidth/2),screenDim.Height-250));
	buttonImage = driver->getTexture("media/options_button.png");
	optionsButton->setImage(buttonImage, core::rect<s32>(0, 0, buttonDim.Width, buttonDim.Height));
	buttonPressedImage = driver->getTexture("media/options_pressed.png");
    optionsButton->setPressedImage(buttonPressedImage, core::rect<s32>(0, 0, buttonPressedDim.Width, buttonPressedDim.Height));
	optionsButton->setUseAlphaChannel(true);

	exitButton = gui->addButton(core::rect<s32>((screenDim.Width/2)-(buttonWidth/2),(screenDim.Height-200)-buttonHeight, (screenDim.Width/2)+(buttonWidth/2),screenDim.Height-200));
	buttonImage = driver->getTexture("media/exit_button.png");
	exitButton->setImage(buttonImage, core::rect<s32>(0, 0, buttonDim.Width, buttonDim.Height));
	buttonPressedImage = driver->getTexture("media/exit_pressed.png");
    exitButton->setPressedImage(buttonPressedImage, core::rect<s32>(0, 0, buttonPressedDim.Width, buttonPressedDim.Height));
	exitButton->setUseAlphaChannel(true);
	receiver->setExitButton(exitButton);

	backTexture = driver->getTexture("media/back.jpg");

	// create a combobox for selecting the driver type
	/*
	gui->addStaticText(L"Graphics Driver:", core::rect<s32>(screenDim.Width-285,20, screenDim.Width-170,50), false, true);
	gui::IGUIComboBox* box = gui->addComboBox(core::rect<s32>(screenDim.Width-160,20, screenDim.Width-10,40), NULL, 1);
	box->addItem(L"Software");
	box->addItem(L"Burnings Video");
	box->addItem(L"Direct3D8");
	box->addItem(L"Direct3D9");
	box->addItem(L"OpenGL");
	box->setSelected(3);
    */
}

CSetupDevice::~CSetupDevice() {

	shutdown();

}

void CSetupDevice::shutdown() {

	if (setupDevice) {
		setupDevice->closeDevice();
		setupDevice->drop();
		setupDevice = NULL;
	}

	if (receiver) {
		delete receiver;
		receiver = NULL;
	}

}

bool CSetupDevice::execute() {

	while (setupDevice->run() && !startGame && !quitSetup) {
		driver->beginScene(true, true, video::SColor(255,0,0,0));
		// draw a nice gradient background
		driver->draw2DImage(backTexture, core::position2d<s32>(0,0));
		// draw the GUI
		gui->drawAll();
		driver->endScene();
	}

	return !startGame;

}
