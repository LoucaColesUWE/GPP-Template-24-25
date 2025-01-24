// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorValidator_EmptyTick.h"

#include "Engine/Blueprint.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraphSchema_K2.h"
#include "K2Node_Event.h"
#include "Engine/MemberReference.h"

bool UEditorValidator_EmptyTick::CanValidateAsset_Implementation(UObject* InAsset) const
{
	return InAsset && InAsset->IsA<UBlueprint>();
}

EDataValidationResult UEditorValidator_EmptyTick::ValidateLoadedAsset_Implementation(UObject* InAsset, UPARAM(ref) TArray<FText>& ValidationErrors)
{
	static const FName EventTickName(TEXT("ReceiveTick"));

	UBlueprint* Blueprint = Cast<UBlueprint>(InAsset);
	if (!Blueprint) return EDataValidationResult::NotValidated;

	for (UEdGraph* Graph : Blueprint->UbergraphPages)
	{
		for (UEdGraphNode* Node : Graph->Nodes)
		{
			UK2Node_Event* EventNode = Cast<UK2Node_Event>(Node);
			if (EventNode && EventNode->EventReference.GetMemberName() == EventTickName)
			{
				if (IsEmptyTick(EventNode))
				{
					
					//Context.AddError(FText::FromString(TEXT("Empty Tick nodes still produce overhead, please use or remove it.")));
					AssetFails(InAsset, FText::FromString(TEXT("Empty Tick nodes still produce overhead, please use or remove it.")), ValidationErrors);
					return EDataValidationResult::Invalid;
				}
			}
		}
	}

	return EDataValidationResult::Valid;
}

bool UEditorValidator_EmptyTick::IsEmptyTick(UK2Node_Event* EventNode)
{
	if (EventNode->IsAutomaticallyPlacedGhostNode()) return false; // Ghost nodes aren't real nodes

	UEdGraphPin* ExecThenPin = EventNode->FindPin(UEdGraphSchema_K2::PN_Then);
	return ExecThenPin && ExecThenPin->LinkedTo.IsEmpty();
}
