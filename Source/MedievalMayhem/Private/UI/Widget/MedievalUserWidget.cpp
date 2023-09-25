// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MedievalUserWidget.h"

void UMedievalUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
