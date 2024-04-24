extends CharacterBody2D

@export var speed = 150

@onready var _animated_sprite = $AnimatedSprite2D

var player_cloth_status = "Cloth1"

# ------------------------------------------------------------------------------
# get_input:	copied from docs. 
#
# test movement for the player. likely not permanent
#
func get_input():
	var input_direction = Input.get_vector("Left", "Right", "Up", "Down")
	velocity = input_direction * speed

#
# play_anim:	Plays the sprites current animation
func play_anim():
	_animated_sprite.play(_animated_sprite.animation)

# ------------------------------------------------------------------------------
# process:	built-in animation method(?)
#
# use to process player animations
# var a used for direction retention
# 
var a = 0
func _process(_delta):
	var current_animation = "Cloth1_Idle_D"
	var input_dir = Vector2.ZERO
	
	if Input.is_action_pressed("Right"):
		input_dir.x += 1
	if Input.is_action_pressed("Left"):
		input_dir.x -= 1 
	if Input.is_action_pressed("Up"):
		input_dir.y -= 1
	if Input.is_action_pressed("Down"):
		input_dir.y += 1
	input_dir = input_dir.normalized()
	
	if input_dir.length() != 0:
		a = input_dir.angle() / (PI/4)
		a = wrapi(int(a), 0, 8)
		current_animation = player_cloth_status + "_Walk_"
		_animated_sprite.animation = current_animation + str(a)
	else:
		_animated_sprite.animation = player_cloth_status + "_Idle_" + str(a)
	### print(a)

func _physics_process(delta):
	get_input()
	play_anim()
	move_and_slide()
