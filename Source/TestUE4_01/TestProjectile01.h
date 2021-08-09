#pragma once

#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "TestProjectileSetting.h"
#include "TestProjectile01.generated.h"

class UBoxComponent;

UCLASS()
class ATestProjectile01 : public AActor
{
    GENERATED_BODY()

public:
    ATestProjectile01();

protected:
    virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY()
    UArrowComponent* ArrowComponent;

    UPROPERTY()
    UBoxComponent* CollisionComponent;

private:
    float Speed = 0.0f;
    FVector PositionStart;
    FVector Direction;
    FQuat Rotation;

    float TimeSpawned = 0.0f;
    float TimeDestroyForce = 0.0f;
    bool IsHitReflect = false;

public:
	TFunction<void(ATestProjectile01*, float)> OnTimeTrigger = nullptr;

public:
	static TSet<ATestProjectile01*> Projectiles;
	static void DestroyRequestAll();

public:
    void InitProjectile(FVector& InPosition, FVector& InDirection, float InScale, bool bIsHitReflect = false, float InTimeDestroy = DEFAULT_DESTROY, FColor InColor = FColor::Red);

private:
    void UpdateLocation(FVector LocationCurrent, float DeltaTime);
    
    virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void OnUpdatedOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
