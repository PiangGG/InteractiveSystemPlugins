// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractiveSystemPlugins/Data/PackItem.h"
#include "WBP_Pack_RemoveItem_Box.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE_RetVal(bool,FReturnSelectBool);
UCLASS()
class INTERACTIVESYSTEMPLUGINS_API UWBP_Pack_RemoveItem_Box : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RemoveItem_Box",meta=(BindWidget))
	class USizeBox*SizeBox;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RemoveItem_Box",meta=(BindWidget))
	class UOverlay*Overlay;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RemoveItem_Box",meta=(BindWidget))
	class UImage *Image_Bg;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RemoveItem_Box",meta=(BindWidget))
	class UButton *Button_true;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RemoveItem_Box",meta=(BindWidget))
	class UButton *Button_false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RemoveItem_Box",meta=(BindWidget))
	class USpinBox*SpinBox;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RemoveItem_Box",meta=(BindWidget))
	class UTextBlock*TextBlock_Show;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RemoveItem_Box",meta=(BindWidget))
	class UTextBlock*TextBlock_Ture;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RemoveItem_Box",meta=(BindWidget))
	class UTextBlock*TextBlock_False;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RemoveItem_Box")
	FButtonStyle ButtonStyle;

	UPROPERTY()
	FReturnSelectBool ReturnSelectBool;

	UPROPERTY()
	bool OnClickOption = false;
	UPROPERTY()
	int RemoveNumber = 1;

	void SetParent(UUserWidget* parent);

	FPackItmeStruct PackItmeStruct;
	
	FPackItmeStruct& packItmeStruct = PackItmeStruct;
	
protected:
	UFUNCTION()
	void OnClickTrue();
	UFUNCTION()
	void OnClickFalse();

private:
	UPROPERTY()
	class UUserWidget* Parent;
};
