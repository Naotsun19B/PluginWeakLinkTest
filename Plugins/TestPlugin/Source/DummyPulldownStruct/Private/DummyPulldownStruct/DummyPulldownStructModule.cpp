﻿// Copyright 2021-2023 Naotsun. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

namespace DummyPulldownStruct
{
	class FDummyPulldownStructModule : public IModuleInterface
	{
	public:
		// IModuleInterface interface.
		virtual void StartupModule() override;
		virtual void ShutdownModule() override;
		// End of IModuleInterface interface.
	};

	void FDummyPulldownStructModule::StartupModule()
	{
	}

	void FDummyPulldownStructModule::ShutdownModule()
	{
	}
}
	
IMPLEMENT_MODULE(DummyPulldownStruct::FDummyPulldownStructModule, DummyPulldownStruct)