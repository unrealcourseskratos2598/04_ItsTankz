// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	SetRootComponent(PhysicsConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(PhysicsConstraint);

	Wheel1 = CreateDefaultSubobject<USphereComponent>(FName("Wheel1"));
	Wheel1->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Wheel Constraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

	if (!Axle || !Wheel1) { return; }
	Axle->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Axle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel1->SetNotifyRigidBodyCollision(true);
	Wheel1->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetupConstraints();
		
}

void ASprungWheel::SetupConstraints()
{
	if (!GetAttachParentActor()) { return; }
	auto BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }

	PhysicsConstraint->SetConstrainedComponents(
		BodyRoot,
		NAME_None,
		Axle, // DO NOT Cast Axle to Primitive as it loses its physics simulations
		NAME_None);

	AxleWheelConstraint->SetConstrainedComponents(
		Axle,
		NAME_None,
		Wheel1, // DO NOT Cast Wheel to Primitive as it loses its physics simulations
		NAME_None);

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame = 0;
	}

}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}


void ASprungWheel::ApplyForce()
{
	Wheel1->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}
 


