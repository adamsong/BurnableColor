#include "BurnableColorModule.h"

#include "FGItemDescriptorInk.h"

#include "Patching/NativeHookManager.h"

#include "Buildables/FGBuildableGeneratorFuel.h"

void FBurnableColorModule::StartupModule() {
	RegisterHooks();
}

void FBurnableColorModule::RegisterHooks() {
#if !WITH_EDITOR
	SUBSCRIBE_METHOD(AFGBuildableGeneratorFuel::IsValidFuel, [](auto& scope, const AFGBuildableGeneratorFuel* self, TSubclassOf< UFGItemDescriptor > resource) {
		if (self->GetFuelResourceForm() == EResourceForm::RF_LIQUID) {
			TSubclassOf< UFGItemDescriptorInk > inkResource = resource;
			if (resource != nullptr) {
				scope.Override(true);
			}
		}
	});
#endif
}

IMPLEMENT_GAME_MODULE(FBurnableColorModule, BurnableColor);