// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ValidatorSettings.generated.h"

/**
 * 
 */
UCLASS(config = UWEValidatorSettings)
class UWEVALIDATORS_API UValidatorSettings : public UObject
{
	GENERATED_BODY()

public:
	UValidatorSettings(const FObjectInitializer& obj);
	UPROPERTY(Config, EditAnywhere, Category = Settings)
		int32 SomeIntProperty;

	UPROPERTY(Config, EditAnywhere, Category = Settings)
		bool SomeBoolProperty;
};
