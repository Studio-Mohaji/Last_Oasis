// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Last_Oasis/Data/DataAssetBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDataAssetBase() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UPrimaryDataAsset();
ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
LAST_OASIS_API UClass* Z_Construct_UClass_UDataAssetBase();
LAST_OASIS_API UClass* Z_Construct_UClass_UDataAssetBase_NoRegister();
UPackage* Z_Construct_UPackage__Script_Last_Oasis();
// End Cross Module References

// Begin Class UDataAssetBase
void UDataAssetBase::StaticRegisterNativesUDataAssetBase()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UDataAssetBase);
UClass* Z_Construct_UClass_UDataAssetBase_NoRegister()
{
	return UDataAssetBase::StaticClass();
}
struct Z_Construct_UClass_UDataAssetBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Data/DataAssetBase.h" },
		{ "ModuleRelativePath", "Data/DataAssetBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemIndex_MetaData[] = {
		{ "Category", "Data" },
		{ "ModuleRelativePath", "Data/DataAssetBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemName_MetaData[] = {
		{ "Category", "Data" },
		{ "ModuleRelativePath", "Data/DataAssetBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "Category", "Data" },
		{ "ModuleRelativePath", "Data/DataAssetBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Icon_MetaData[] = {
		{ "Category", "DataAssetBase" },
		{ "ModuleRelativePath", "Data/DataAssetBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IsUsable_MetaData[] = {
		{ "Category", "Data" },
		{ "ModuleRelativePath", "Data/DataAssetBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IsCombinable_MetaData[] = {
		{ "Category", "Data" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Player can use\n" },
#endif
		{ "ModuleRelativePath", "Data/DataAssetBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Player can use" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IsStackable_MetaData[] = {
		{ "Category", "Data" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Use for Crafting\n" },
#endif
		{ "ModuleRelativePath", "Data/DataAssetBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Use for Crafting" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxStackCount_MetaData[] = {
		{ "Category", "Data" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// stack of inventory\n" },
#endif
		{ "ModuleRelativePath", "Data/DataAssetBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "stack of inventory" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UseValue_MetaData[] = {
		{ "Category", "Data" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Max of stack inventory\n" },
#endif
		{ "ModuleRelativePath", "Data/DataAssetBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max of stack inventory" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ItemIndex;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemName;
	static const UECodeGen_Private::FTextPropertyParams NewProp_Description;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Icon;
	static void NewProp_IsUsable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsUsable;
	static void NewProp_IsCombinable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsCombinable;
	static void NewProp_IsStackable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsStackable;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxStackCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_UseValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDataAssetBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UDataAssetBase_Statics::NewProp_ItemIndex = { "ItemIndex", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDataAssetBase, ItemIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemIndex_MetaData), NewProp_ItemIndex_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UDataAssetBase_Statics::NewProp_ItemName = { "ItemName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDataAssetBase, ItemName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemName_MetaData), NewProp_ItemName_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UDataAssetBase_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDataAssetBase, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDataAssetBase_Statics::NewProp_Icon = { "Icon", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDataAssetBase, Icon), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Icon_MetaData), NewProp_Icon_MetaData) };
void Z_Construct_UClass_UDataAssetBase_Statics::NewProp_IsUsable_SetBit(void* Obj)
{
	((UDataAssetBase*)Obj)->IsUsable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDataAssetBase_Statics::NewProp_IsUsable = { "IsUsable", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDataAssetBase), &Z_Construct_UClass_UDataAssetBase_Statics::NewProp_IsUsable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IsUsable_MetaData), NewProp_IsUsable_MetaData) };
void Z_Construct_UClass_UDataAssetBase_Statics::NewProp_IsCombinable_SetBit(void* Obj)
{
	((UDataAssetBase*)Obj)->IsCombinable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDataAssetBase_Statics::NewProp_IsCombinable = { "IsCombinable", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDataAssetBase), &Z_Construct_UClass_UDataAssetBase_Statics::NewProp_IsCombinable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IsCombinable_MetaData), NewProp_IsCombinable_MetaData) };
void Z_Construct_UClass_UDataAssetBase_Statics::NewProp_IsStackable_SetBit(void* Obj)
{
	((UDataAssetBase*)Obj)->IsStackable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDataAssetBase_Statics::NewProp_IsStackable = { "IsStackable", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDataAssetBase), &Z_Construct_UClass_UDataAssetBase_Statics::NewProp_IsStackable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IsStackable_MetaData), NewProp_IsStackable_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UDataAssetBase_Statics::NewProp_MaxStackCount = { "MaxStackCount", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDataAssetBase, MaxStackCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxStackCount_MetaData), NewProp_MaxStackCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UDataAssetBase_Statics::NewProp_UseValue = { "UseValue", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDataAssetBase, UseValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UseValue_MetaData), NewProp_UseValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDataAssetBase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDataAssetBase_Statics::NewProp_ItemIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDataAssetBase_Statics::NewProp_ItemName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDataAssetBase_Statics::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDataAssetBase_Statics::NewProp_Icon,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDataAssetBase_Statics::NewProp_IsUsable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDataAssetBase_Statics::NewProp_IsCombinable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDataAssetBase_Statics::NewProp_IsStackable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDataAssetBase_Statics::NewProp_MaxStackCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDataAssetBase_Statics::NewProp_UseValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDataAssetBase_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UDataAssetBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UPrimaryDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_Last_Oasis,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDataAssetBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDataAssetBase_Statics::ClassParams = {
	&UDataAssetBase::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UDataAssetBase_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UDataAssetBase_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDataAssetBase_Statics::Class_MetaDataParams), Z_Construct_UClass_UDataAssetBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UDataAssetBase()
{
	if (!Z_Registration_Info_UClass_UDataAssetBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDataAssetBase.OuterSingleton, Z_Construct_UClass_UDataAssetBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDataAssetBase.OuterSingleton;
}
template<> LAST_OASIS_API UClass* StaticClass<UDataAssetBase>()
{
	return UDataAssetBase::StaticClass();
}
UDataAssetBase::UDataAssetBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UDataAssetBase);
UDataAssetBase::~UDataAssetBase() {}
// End Class UDataAssetBase

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_JAEHAK_Documents_GitHub_Project_Casino_Last_Oasis_Last_Oasis_Source_Last_Oasis_Data_DataAssetBase_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDataAssetBase, UDataAssetBase::StaticClass, TEXT("UDataAssetBase"), &Z_Registration_Info_UClass_UDataAssetBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDataAssetBase), 4224955774U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_JAEHAK_Documents_GitHub_Project_Casino_Last_Oasis_Last_Oasis_Source_Last_Oasis_Data_DataAssetBase_h_3106744395(TEXT("/Script/Last_Oasis"),
	Z_CompiledInDeferFile_FID_Users_JAEHAK_Documents_GitHub_Project_Casino_Last_Oasis_Last_Oasis_Source_Last_Oasis_Data_DataAssetBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_JAEHAK_Documents_GitHub_Project_Casino_Last_Oasis_Last_Oasis_Source_Last_Oasis_Data_DataAssetBase_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
