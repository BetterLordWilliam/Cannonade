extends CharacterBody2D

@export var speed = 150
@export var inventory = Inv

@onready var _body_sprite = $Body
@onready var _head_sprite = $Head
# @onready var _ui = $UI

var player_cloth_status = "Cloth1"
var player_head_status = "Male_Head1"

# ------------------------------------------------------------------------------
# get_input:	copied from docs. 
#
# test movement for the player. likely not permanent
#
func get_input():
	var input_direction = Input.get_vector("Left", "Right", "Up", "Down")
	velocity = input_direction * speed

# ------------------------------------------------------------------------------
# play_anim:	Plays the sprites current animation
func play_anim():
	_body_sprite.play(_body_sprite.animation)
	_head_sprite.play(_head_sprite.animation)

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
	
	# process movement input
	if Input.is_action_pressed("Right"):
		input_dir.x += 1
	if Input.is_action_pressed("Left"):
		input_dir.x -= 1 
	if Input.is_action_pressed("Up"):
		input_dir.y -= 1
	if Input.is_action_pressed("Down"):
		input_dir.y += 1
	input_dir = input_dir.normalized()
	
	## Actual movement
	if input_dir.length() != 0:
		a = input_dir.angle() / (PI/4)
		a = wrapi(int(a), 0, 8)
		_body_sprite.animation = player_cloth_status + "_Walk_" + str(a)
		_head_sprite.animation = player_head_status + "_Walk_" + str(a)
	else:
		_body_sprite.animation = player_cloth_status + "_Idle_" + str(a)
		_head_sprite.animation = player_head_status + "_Idle_" + str(a)
	### print(a)

func _physics_process(delta):
	get_input()
	play_anim()
	move_and_slide()
