// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	abilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	abilitySystemComponent->SetIsReplicated(true);
	attributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
	
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::AquireAbility() {
	if (abilitySystemComponent) {
		for (auto& ability : AbilityToAquire)
			abilitySystemComponent->GiveAbility(FGameplayAbilitySpec(ability, 1, 0));
		abilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

TSubclassOf<UGameplayAbility> ABaseCharacter::GetAbilityToAquire(int value)
{
	return AbilityToAquire[value];
}

/*
UGameplayEffect* ABaseCharacter::GetHealthEnergeGameplayEffect()
{
	return &HealthEnergeGameplayEffect;
}
*/
UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const {
	return abilitySystemComponent;
}

float ABaseCharacter::GetHealth() const {
	return attributeSet->Gethealth();
}

void ABaseCharacter::SetHealth(float value) {
	attributeSet->health = value;
}

void ABaseCharacter::SetDHealth(float value) {
	attributeSet->health = attributeSet->health.GetCurrentValue() - value;
	//OnDamaged();
}

void ABaseCharacter::SubHealth(float value) {
	attributeSet->health = attributeSet->health.GetCurrentValue() - value;
}

void ABaseCharacter::SetAttribute(FTableAttributeSet AttributeSet) {
	SetHealth(AttributeSet.health);
	SetMaxHealth(AttributeSet.maxHealth);
	SetEnergy(AttributeSet.energy);
	SetMaxEnergy(AttributeSet.maxEnergy);
	SetAttack(AttributeSet.attack);
}

float ABaseCharacter::GetMaxHealth() const {
	return attributeSet->GetmaxHealth();
}

void ABaseCharacter::SetMaxHealth(float value) {
	attributeSet->maxHealth = value;
}

float ABaseCharacter::GetEnergy() const {
	return attributeSet->Getenergy();
}

void ABaseCharacter::SetEnergy(float value) {
	if (value >= attributeSet->GetmaxEnergy())
		attributeSet->energy = attributeSet->GetmaxEnergy();
	else
		attributeSet->energy = value;
}

float ABaseCharacter::GetMaxEnergy() const {
	return attributeSet->GetmaxEnergy();
}

void ABaseCharacter::SetMaxEnergy(float value) {
	attributeSet->maxEnergy = value;
}

float ABaseCharacter::GetMoveSpeed() const {
	return attributeSet->GetmoveSpeed();
}

float ABaseCharacter::GetAttack() const {
	return attributeSet->Getattack();
}

float ABaseCharacter::GetDefense() const {
	return attributeSet->Getdefense();
}

float ABaseCharacter::GetExperience() const {
	return attributeSet->Getexperience();
}

float ABaseCharacter::GetDamage() const
{
	return attributeSet->Getdamage();
}

void ABaseCharacter::SetPlus()
{
	UMyGameInstance* instance = Cast<UMyGameInstance>(GetGameInstance());

	auto Plus = [](auto value, auto level, auto coefficient) {
		return value + level * coefficient;
	};

	float values[2] = { 0.0, 0.0 };
	values[0] = GetHealth();
	values[1] = GetAttack();

	for (int i = 0; i < 2; i++) {
		values[i] = Plus(values[i], instance->GetLevel(i), instance->GetCoefficient(i));
	}

	SetMaxHealth(values[0]);
	SetHealth(values[0]);
	SetAttack(values[1]);
}


// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &ABaseCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABaseCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABaseCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABaseCharacter::TouchStopped);

}

void ABaseCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ABaseCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ABaseCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::Turn(float Rate)
{
	Super::AddControllerYawInput(Rate);
}

void ABaseCharacter::LookUp(float Rate)
{
	Super::AddControllerPitchInput(Rate);
}

void ABaseCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		if (!Roll)
			AddMovementInput(Direction, Value);
	}
	InputX = Value;

}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		if (!Roll)
			AddMovementInput(Direction, Value);
			
	}
	InputY = Value;
}

