// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Last_Oasis/Last_OasisGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLast_OasisGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
LAST_OASIS_API UClass* Z_Construct_UClass_ALast_OasisGameMode();
LAST_OASIS_API UClass* Z_Construct_UClass_ALast_OasisGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_Last_Oasis();
// End Cross Module References

// Begin Class ALast_OasisGameMode
void ALast_OasisGameMode::StaticRegisterNativesALast_OasisGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ALast_OasisGameMode);
UClass* Z_Construct_UClass_ALast_OasisGameMode_NoRegister()
{
	return ALast_OasisGameMode::StaticClass();
}
struct Z_Construct_UClass_ALast_OasisGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Last_OasisGameMode.h" },
		{ "ModuleRelativePath", "Last_OasisGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALast_OasisGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ALast_OasisGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Last_Oasis,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALast_OasisGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ALast_OasisGameMode_Statics::ClassParams = {
	&ALast_OasisGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ALast_OasisGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ALast_OasisGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ALast_OasisGameMode()
{
	if (!Z_Registration_Info_UClass_ALast_OasisGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALast_OasisGameMode.OuterSingleton, Z_Construct_UClass_ALast_OasisGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ALast_OasisGameMode.OuterSingleton;
}
template<> LAST_OASIS_API UClass* StaticClass<ALast_OasisGameMode>()
{
	return ALast_OasisGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ALast_OasisGameMode);
ALast_OasisGameMode::~ALast_OasisGameMode() {}
// End Class ALast_OasisGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Unreal_github_shuby_Last_Oasis_Last_Oasis_Source_Last_Oasis_Last_OasisGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALast_OasisGameMode, ALast_OasisGameMode::StaticClass, TEXT("ALast_OasisGameMode"), &Z_Registration_Info_UClass_ALast_OasisGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALast_OasisGameMode), 2806718977U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_github_shuby_Last_Oasis_Last_Oasis_Source_Last_Oasis_Last_OasisGameMode_h_243257890(TEXT("/Script/Last_Oasis"),
	Z_CompiledInDeferFile_FID_Unreal_github_shuby_Last_Oasis_Last_Oasis_Source_Last_Oasis_Last_OasisGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_github_shuby_Last_Oasis_Last_Oasis_Source_Last_Oasis_Last_OasisGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
