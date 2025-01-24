// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorValidator_BlueprintNaming.h"

bool UEditorValidator_BlueprintNaming::CanValidateAsset_Implementation(UObject* InAsset) const
{
	return InAsset->GetClass()->GetFName() == UBlueprint::StaticClass()->GetFName();
}

EDataValidationResult UEditorValidator_BlueprintNaming::ValidateLoadedAsset_Implementation(UObject* InAsset,
	TArray<FText>& ValidationErrors)
{
    if (UBlueprint* Blueprint = Cast<UBlueprint>(InAsset))
    {
        FString BlueprintName = Blueprint->GetName();

        // Check if the name starts with "BP_"
        if (!BlueprintName.StartsWith("BP_"))
        {
            FText ErrorMessage = FText::Format(
                NSLOCTEXT("BlueprintNamingValidator", "InvalidBlueprintName", "Blueprint '{0}' does not start with 'BP_'"),
                FText::FromString(BlueprintName)
            );
            AssetFails(InAsset, ErrorMessage, ValidationErrors);
            return EDataValidationResult::Invalid;
        }
    }

    return EDataValidationResult::Valid;
}
