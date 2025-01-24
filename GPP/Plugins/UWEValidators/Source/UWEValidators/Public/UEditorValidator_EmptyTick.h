// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorValidatorBase.h"
#include "UEditorValidator_EmptyTick.generated.h"

/**
 * 
 */
UCLASS()
class UWEVALIDATORS_API UUEditorValidator_EmptyTick : public UEditorValidatorBase
{
	GENERATED_BODY()

	virtual bool CanValidateAsset_Implementation(UObject* InAsset) const override;
	virtual EDataValidationResult ValidateLoadedAsset_Implementation(UObject* InAsset, UPARAM(ref) TArray<FText>& ValidationErrors) override;

	bool IsEmptyTick(class UK2Node_Event* EventNode);
};
