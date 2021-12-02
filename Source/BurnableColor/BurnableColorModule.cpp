#include "BurnableColorModule.h"

#include "FGItemDescriptorInk.h"

#include "Buildables/FGBuildableGeneratorFuel.h"
#include "Patching/NativeHookManager.h"

void FBurnableColorModule::StartupModule() {
#if !WITH_EDITOR
	RegisterHooks();
#endif
}

#if !WITH_EDITOR
void FBurnableColorModule::RegisterHooks() {
	UE_LOG(LogBurnableColor, Log, TEXT("Registering hooks"));
	SUBSCRIBE_METHOD(AFGBuildableGeneratorFuel::IsValidFuel, [](auto& Scope, const AFGBuildableGeneratorFuel* Self, const TSubclassOf<UFGItemDescriptor> Resource)
	{
		if(HookIsValidFuel(Self, Resource))
		{
			Scope.Override(true);
		}
	});
}

bool FBurnableColorModule::HookIsValidFuel(const AFGBuildableGeneratorFuel* Self, const TSubclassOf< UFGItemDescriptor > Resource) {
	if(Resource == nullptr) return false;
	if (Self->GetFuelResourceForm() == EResourceForm::RF_LIQUID)
	{
		if (const TSubclassOf<UFGItemDescriptorInk> InkResource(Resource); InkResource != nullptr) {
			return true;
		}
	}
	return false;
}
#endif

IMPLEMENT_GAME_MODULE(FBurnableColorModule, BurnableColor);

DEFINE_LOG_CATEGORY(LogBurnableColor);