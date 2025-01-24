// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorValidator_GitFileSize.h"

#include "AssetRegistry/AssetRegistryModule.h"

#define MAX_FILE_SIZE_BYTES 52428800 // 50 MiB

bool UEditorValidator_GitFileSize::CanValidateAsset_Implementation(UObject* InAsset) const
{
	return true;
}

EDataValidationResult UEditorValidator_GitFileSize::ValidateLoadedAsset_Implementation(UObject* InAsset,
	TArray<FText>& ValidationErrors)
{
	// Get the asset's package name.
	FString PackageName = InAsset->GetPackage()->GetName();

	// Convert the package name to a file path.
	FString FilePath = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

	// Get the file size.
	int64 FileSize = IFileManager::Get().FileSize(*FilePath);

	// Check if the file size exceeds the maximum allowed size.
	if (FileSize > MAX_FILE_SIZE_BYTES)
	{
		FText ErrorMessage = FText::Format(
			NSLOCTEXT("EditorValidator", "FileSizeExceeded", "Asset '{0}' exceeds the maximum file size of 50 MiB ({1} bytes) which will cause issues with Git"),
			FText::FromString(PackageName),
			FText::AsNumber(FileSize)
		);
		AssetFails(InAsset, ErrorMessage, ValidationErrors);
		return EDataValidationResult::Invalid;
	}

	return EDataValidationResult::Valid;
}
