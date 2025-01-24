// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorValidatorBase.h"
#include "EditorValidator_GitFileSize.generated.h"

/**
 * 
 */
UCLASS()
class UWEVALIDATORS_API UEditorValidator_GitFileSize : public UEditorValidatorBase
{
	GENERATED_BODY()


	virtual bool CanValidateAsset_Implementation(UObject* InAsset) const override;
	virtual EDataValidationResult ValidateLoadedAsset_Implementation(UObject* InAsset, UPARAM(ref) TArray<FText>& ValidationErrors) override;
};
