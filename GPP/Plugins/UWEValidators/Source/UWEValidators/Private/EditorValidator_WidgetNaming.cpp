// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorValidator_WidgetNaming.h"

#include "Blueprint/UserWidget.h"

bool UEditorValidator_WidgetNaming::CanValidateAsset_Implementation(UObject* InAsset) const
{
    UBlueprint* Blueprint = Cast<UBlueprint>(InAsset);

	return Blueprint->GeneratedClass->IsChildOf(UUserWidget::StaticClass());
}

EDataValidationResult UEditorValidator_WidgetNaming::ValidateLoadedAsset_Implementation(UObject* InAsset,
	TArray<FText>& ValidationErrors)
{
    if (UBlueprint* Blueprint = Cast<UBlueprint>(InAsset))
    {
        FString WidgetName = Blueprint->GetName();

        // Check if the name starts with "BP_"
        if (!WidgetName.StartsWith("WBP_"))
        {
            FText ErrorMessage = FText::Format(
                NSLOCTEXT("WidgetNamingValidator", "InvalidWidgetName", "Widget '{0}' does not start with 'WBP_'"),
                FText::FromString(WidgetName)
            );
            AssetFails(InAsset, ErrorMessage, ValidationErrors);
            return EDataValidationResult::Invalid;
        }
    }

    return EDataValidationResult::Valid;
}
