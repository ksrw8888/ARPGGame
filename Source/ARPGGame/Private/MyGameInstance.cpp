// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/FileManager.h"


static uint8* ReadFile(IPlatformFile& PlatformFile, FString path, uint32& len) 
{
	IFileHandle* FileHandle = PlatformFile.OpenRead(*path);
	if (FileHandle) {
		len = (uint32)FileHandle->Size();
		uint8* buf = new uint8[len];

		FileHandle->Read(buf, len);

		// Close the file again
		delete FileHandle;

		return buf;
	}

	return nullptr;
}

UMyGameInstance::UMyGameInstance() :state("main", this) 
{

}

void UMyGameInstance::Init() 
{

	GenerateBagUi();
	GenerateStory(2);

	InitArray();
	soul = 1000;

	state.onInitEvent.AddUObject(this, &UMyGameInstance::LuaStateInitCallback);
	state.init();

	state.setLoadFileDelegate([](const char* fn, FString& filepath)->TArray<uint8> {

		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		FString path = FPaths::ProjectContentDir();
		FString filename = UTF8_TO_TCHAR(fn);
		path /= "Lua";
		path /= filename.Replace(TEXT("."), TEXT("/"));

		TArray<uint8> Content;
		TArray<FString> luaExts = { UTF8_TO_TCHAR(".lua"), UTF8_TO_TCHAR(".luac") };
		for (auto& it : luaExts) {
			auto fullPath = path + *it;

			FFileHelper::LoadFileToArray(Content, *fullPath);
			if (Content.Num() > 0) {
				filepath = fullPath;
				return MoveTemp(Content);
			}
		}

		return MoveTemp(Content);
		});
}

void UMyGameInstance::GenerateStory(int quantity) {
	SetStoryQuantity(quantity);
	InitializeStory();
}


void UMyGameInstance::InitializeStory() {

	for (auto& i : bStory)
		i = false;

}

void UMyGameInstance::InitArray() {
	level.SetNum(2);
	coefficient.SetNum(2);

	for (auto& i : level)
		i = 0;

	coefficient[0] = 500;
	coefficient[1] = 100;
}

void UMyGameInstance::Shutdown() {
	state.close();
}

static int32 PrintLog(NS_SLUA::lua_State* L) {
	FString str;
	size_t len;
	const char* s = luaL_tolstring(L, 1, &len);
	if (s) str += UTF8_TO_TCHAR(s);
	NS_SLUA::Log::Log("PrintLog %s", TCHAR_TO_UTF8(*str));
	return 0;
}

void UMyGameInstance::LuaStateInitCallback() {
	NS_SLUA::lua_State* L = state.getLuaState();
	lua_pushcfunction(L, PrintLog);
	lua_setglobal(L, "PrintLog");
}

FName UMyGameInstance::GetChoiceStory() {

	int index = 0;
	FString choiceStr = "";
	for (auto& i : bStory) {

		if (!i) {
			choiceStr = FString::FromInt(index);
			break;
		}
		else
			index++;

	}

	StroyHappened(index);
	return FName(*choiceStr);

}
