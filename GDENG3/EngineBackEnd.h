#pragma once

class EngineBackEnd
{
public:
	static EngineBackEnd* getInstance();
	static void initialize();
	static void destroy();

	enum EditorMode
	{
		EDITOR = 0,
		PLAY = 1,
		PAUSED = 2
	};

	// Setters
	void setMode(EditorMode mode);
	void startFrameStep();
	void endFrameStep();
	bool insideFrameStep();
	void Start();
	void Stop();

	EditorMode getMode();
private:
	EngineBackEnd();
	~EngineBackEnd();

	EngineBackEnd(EngineBackEnd const&){};				// Copy constructor is private
	EngineBackEnd& operator=(EngineBackEnd const&) {};	// Assignment operator is private

	static EngineBackEnd* sharedInstance;

	EditorMode editorMode = EditorMode::EDITOR;

	bool frameStepping = false;
	bool isStopped = false;
};