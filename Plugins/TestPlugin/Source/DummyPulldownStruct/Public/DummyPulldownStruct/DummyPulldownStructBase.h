﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DummyPulldownStructBase.generated.h"

/**
 * Base struct of the struct displayed as a pull-down menu.
 * To create a pull-down menu struct in C++, define a struct that inherits this struct.
 * If the inherited child struct is used only internally and cannot be used from within Blueprint and
 * cannot be selected by FPulldownStructType, it is necessary to specify "NotBlueprintType" and
 * "BlueprintInternalUseOnly" in the USTRUCT of the child struct.
 */
USTRUCT(BlueprintInternalUseOnly)
struct FPulldownStructBase
{
	GENERATED_BODY()

public:
	// Variable to store the item selected in the pull-down menu.
	// Stores the value used at runtime.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pulldown")
	FName SelectedValue;

public:
	// Constructor.
	FPulldownStructBase() : SelectedValue(NAME_None) {}
	explicit FPulldownStructBase(const FName& InSelectedValue) : SelectedValue(InSelectedValue) {}
	virtual ~FPulldownStructBase() = default;

	// Conversion functions.
	const FName& ToName() const { return SelectedValue; }
	FString ToString() const { return SelectedValue.ToString(); }
	FText ToText() const { return FText::FromName(SelectedValue); }
};

// Define a GetTypeHash function so that it can be used as a map key.
FORCEINLINE uint32 GetTypeHash(const FPulldownStructBase& PulldownStruct)
{
	return GetTypeHash(PulldownStruct.SelectedValue);
}

// A meta-struct that checks if it is a struct that inherits FPulldownStructBase.
template<class TPulldownStruct>
struct TIsPulldownStruct
{
public:
	static constexpr bool Value = (
		TIsDerivedFrom<TPulldownStruct, FPulldownStructBase>::IsDerived &&
		!TIsSame<TPulldownStruct, FPulldownStructBase>::Value
	);
};

// A function for comparing structures that inherit from FPulldownStructBase.
// Make it possible to compare only structures of the same type.
template<class TPulldownStruct, typename TEnableIf<TIsPulldownStruct<TPulldownStruct>::Value, nullptr_t>::Type = nullptr>
FORCEINLINE_DEBUGGABLE bool operator==(const TPulldownStruct& Lhs, const TPulldownStruct& Rhs)
{
	return (Lhs.SelectedValue == Rhs.SelectedValue);
}

template<class TPulldownStruct, typename TEnableIf<TIsPulldownStruct<TPulldownStruct>::Value, nullptr_t>::Type = nullptr>
FORCEINLINE_DEBUGGABLE bool operator!=(const TPulldownStruct& Lhs, const TPulldownStruct& Rhs)
{
	return !(Lhs == Rhs);
}
