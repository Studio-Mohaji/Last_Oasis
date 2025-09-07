// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/CraftingManager.h"

// Sets default values
ACraftingManager::ACraftingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACraftingManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACraftingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACraftingManager::StoryItemCraftingEvent(int32 index)
{
	OnCraftingEvent.Broadcast(index);
}

