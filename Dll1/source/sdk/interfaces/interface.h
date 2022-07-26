#include <Windows.h>

namespace interfaces
{
    using createinterface_t = void* (__cdecl*)(const char*, int*);

	template <typename type>
	type* GetInterface(const wchar_t* dll_name, const char* interface_name)
	{
		const auto static CreateInterface = reinterpret_cast<createinterface_t>(
			GetProcAddress(GetModuleHandle(dll_name),
				"CreateInterface")
			); // Export create interface from engine.dll and initalize it once

		int return_buffer = 0;
		auto retrieved_interface = reinterpret_cast<type*>(CreateInterface(interface_name, &return_buffer));

		return retrieved_interface;
	}

}

class IClientEntityList
{
public:
    // Get IClientNetworkable interface for specified entity
    virtual void * GetClientNetworkable(int entnum) = 0;
    virtual void* GetClientNetworkableFromHandle(int hEnt) = 0;
    virtual void* GetClientUnknownFromHandle(int hEnt) = 0;

    // NOTE: This function is only a convenience wrapper.
    // It returns GetClientNetworkable( entnum )->GetIClientEntity().
    virtual void* GetClientEntity(int entnum) = 0;
    virtual void* GetClientEntityFromHandle(int hEnt) = 0;

    // Returns number of entities currently in use
    virtual int                    NumberOfEntities(bool bIncludeNonNetworkable) = 0;

    // Returns highest index actually used
    virtual int                    GetHighestEntityIndex(void) = 0;

    // Sizes entity list to specified size
    virtual void                SetMaxEntities(int maxents) = 0;
    virtual int                    GetMaxEntities() = 0;
};

class IBaseClientDLL
{
public:
	// Called once when the client DLL is loaded
	virtual int				Init(void* appSystemFactory,
		void* physicsFactory,
		void* pGlobals) = 0;

	virtual void			PostInit() = 0;

	// Called once when the client DLL is being unloaded
	virtual void			Shutdown(void) = 0;

	// Called once the client is initialized to setup client-side replay interface pointers
	virtual bool			ReplayInit(void* replayFactory) = 0;
	virtual bool			ReplayPostInit() = 0;

	// Called at the start of each level change
	virtual void			LevelInitPreEntity(char const* pMapName) = 0;
	// Called at the start of a new level, after the entities have been received and created
	virtual void			LevelInitPostEntity() = 0;
	// Called at the end of a level
	virtual void			LevelShutdown(void) = 0;

	// Request a pointer to the list of client datatable classes
	virtual void* GetAllClasses(void) = 0;

	// Called once per level to re-initialize any hud element drawing stuff
	virtual int				HudVidInit(void) = 0;
	// Called by the engine when gathering user input
	virtual void			HudProcessInput(bool bActive) = 0;
	// Called oncer per frame to allow the hud elements to think
	virtual void			HudUpdate(bool bActive) = 0;
	// Reset the hud elements to their initial states
	virtual void			HudReset(void) = 0;
	// Display a hud text message
	virtual void			HudText(const char* message) = 0;

	// Mouse Input Interfaces
	// Activate the mouse (hides the cursor and locks it to the center of the screen)
	virtual void			IN_ActivateMouse(void) = 0;
	// Deactivates the mouse (shows the cursor and unlocks it)
	virtual void			IN_DeactivateMouse(void) = 0;
	// This is only called during extra sound updates and just accumulates mouse x, y offets and recenters the mouse.
	//  This call is used to try to prevent the mouse from appearing out of the side of a windowed version of the engine if 
	//  rendering or other processing is taking too long
	virtual void			IN_Accumulate(void) = 0;
	// Reset all key and mouse states to their initial, unpressed state
	virtual void			IN_ClearStates(void) = 0;
	// If key is found by name, returns whether it's being held down in isdown, otherwise function returns false
	virtual bool			IN_IsKeyDown(const char* name, bool& isdown) = 0;
	// Notify the client that the mouse was wheeled while in game - called prior to executing any bound commands.
	virtual void			IN_OnMouseWheeled(int nDelta) = 0;
	// Raw keyboard signal, if the client .dll returns 1, the engine processes the key as usual, otherwise,
	//  if the client .dll returns 0, the key is swallowed.
	virtual int				IN_KeyEvent(int eventcode, void* keynum, const char* pszCurrentBinding) = 0;

	// This function is called once per tick to create the player CUserCmd (used for prediction/physics simulation of the player)
	// Because the mouse can be sampled at greater than the tick interval, there is a separate input_sample_frametime, which
	//  specifies how much additional mouse / keyboard simulation to perform.
	virtual void			CreateMove(
								int sequence_number,			// sequence_number of this cmd
								float input_sample_frametime,	// Frametime for mouse input sampling
								bool active) = 0;				// True if the player is active (not paused)

};

class CHLClient : public IBaseClientDLL
{
public:
	CHLClient();

	virtual int						Init(void* appSystemFactory, void* physicsFactory, void* pGlobals);

	virtual void					PostInit();
	virtual void					Shutdown(void);

	virtual bool					ReplayInit(void* fnReplayFactory);
	virtual bool					ReplayPostInit();

	virtual void					LevelInitPreEntity(const char* pMapName);
	virtual void					LevelInitPostEntity();
	virtual void					LevelShutdown(void);

	virtual void* GetAllClasses(void);

	virtual int						HudVidInit(void);
	virtual void					HudProcessInput(bool bActive);
	virtual void					HudUpdate(bool bActive);
	virtual void					HudReset(void);
	virtual void					HudText(const char* message);

	// Mouse Input Interfaces
	virtual void					IN_ActivateMouse(void);
	virtual void					IN_DeactivateMouse(void);
	virtual void					IN_Accumulate(void);
	virtual void					IN_ClearStates(void);
	virtual bool					IN_IsKeyDown(const char* name, bool& isdown);
	virtual void					IN_OnMouseWheeled(int nDelta);
	// Raw signal
	virtual int						IN_KeyEvent(int eventcode, void* keynum, const char* pszCurrentBinding);
	virtual void					IN_SetSampleTime(float frametime);
	// Create movement command
	virtual void					CreateMove(int sequence_number, float input_sample_frametime, bool active);
	virtual void					ExtraMouseSample(float frametime, bool active);
	virtual bool					WriteUsercmdDeltaToBuffer(void* buf, int from, int to, bool isnewcommand);
	virtual void					EncodeUserCmdToBuffer(void* buf, int slot);
	virtual void					DecodeUserCmdFromBuffer(void* buf, int slot);


	virtual void					View_Render(void* rect);
	virtual void					RenderView(const void* view, int nClearFlags, int whatToDraw);
	virtual void					View_Fade(void** pSF);

	virtual void					SetCrosshairAngle(const void* angle);

	virtual void					InitSprite(void* pSprite, const char* loadname);
	virtual void					ShutdownSprite(void* pSprite);

	virtual int						GetSpriteSize(void) const;

	virtual void					VoiceStatus(int entindex, void* bTalking);

	virtual void					InstallStringTableCallback(const char* tableName);

	virtual void					FrameStageNotify(void* curStage);

	virtual bool					DispatchUserMessage(int msg_type, void* msg_data);

	// Save/restore system hooks
	virtual void** SaveInit(int size);
	virtual void			SaveWriteFields(void**, const char*, void*, void**, void**, int);
	virtual void			SaveReadFields(void**, const char*, void*, void**, void**, int);
	virtual void			PreSave(void**);
	virtual void			Save(void**);
	virtual void			WriteSaveHeaders(void**);
	virtual void			ReadRestoreHeaders(void**);
	virtual void			Restore(void**, bool);
	virtual void			DispatchOnRestore();
	virtual void			WriteSaveGameScreenshot(const char* pFilename);

	// Given a list of "S(wavname) S(wavname2)" tokens, look up the localized text and emit
	//  the appropriate close caption if running with closecaption = 1
	virtual void			EmitSentenceCloseCaption(char const* tokenstream);
	virtual void			EmitCloseCaption(char const* captionname, float duration);

	virtual void* GetStandardRecvProxies();

	virtual bool			CanRecordDemo(char* errorMsg, int length) const;

	virtual void			OnDemoRecordStart(char const* pDemoBaseName);
	virtual void			OnDemoRecordStop();
	virtual void			OnDemoPlaybackStart(char const* pDemoBaseName);
	virtual void			OnDemoPlaybackStop();

	virtual bool			ShouldDrawDropdownConsole();

	// Get client screen dimensions
	virtual int				GetScreenWidth();
	virtual int				GetScreenHeight();
};