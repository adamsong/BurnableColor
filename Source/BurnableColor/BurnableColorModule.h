#pragma once

#include "Modules/ModuleManager.h"

class FBurnableColorModule : public FDefaultGameModuleImpl {
public:
	virtual void StartupModule() override;

	virtual bool IsGameModule() const override { return true; }

private:
#if !WITH_EDITOR
	static void RegisterHooks();
	static bool HookIsValidFuel(const class AFGBuildableGeneratorFuel* Self, const TSubclassOf< class UFGItemDescriptor > Resource);
#endif
};

DECLARE_LOG_CATEGORY_EXTERN(LogBurnableColor, Log, Log);
