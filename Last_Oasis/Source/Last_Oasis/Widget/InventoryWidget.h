// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Blueprint/UserWidget.h"
#include "../Actor/MyActor.h"
#include "InventoryWidget.generated.h"

class UItemInfoWidget;
class UInventorySlotWidget;
class UDataAssetBase;
class UItemListDataAsset;
/**
 * 
 */
UCLASS()
class LAST_OASIS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // 아이템 정보 위젯
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    UItemInfoWidget* ItemInfoWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TSubclassOf<UInventorySlotWidget> ItemSlotWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	AMyActor* InventoryActor;
	//UItemListDataAsset* InventoryItems;

    UPROPERTY(meta = (BindWidget))
    UGridPanel* GridBox;

    UPROPERTY()
    TArray<UInventorySlotWidget*> InventorySlots;

    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable)
    void InitializeSlots();

    UFUNCTION(BlueprintCallable)
    void SlotUpdate();
};
