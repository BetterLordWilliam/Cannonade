extends Control

@onready var inventory: Inv = preload("res://src/scenes/player/player_inv.tres")
@onready var slots: Array = $NinePatchRect/GridContainer.get_children()

var is_open = false

# ------------------------------------------------------------------------------
# update_slots:		checks slots, updates slots
#
# uses the function from the inv_ui_slot
#
func update_slots():
	for i in range(min(inventory.items.size(), slots.size())):
		slots[i].update(inventory.items[i])

# ------------------------------------------------------------------------------
# _process:		called on scene load, disables inventory view
#
func _ready():
	update_slots()
	close()

# ------------------------------------------------------------------------------
# _process:		process inventory related inputs
#
# will show inventory if the inventory is not being shown
# will hide inventory if the inventory is being shown
func _process(delta):
	if Input.is_action_just_pressed("Inventory Access"):
		if (is_open):
			close()
		else:
			open()

# ------------------------------------------------------------------------------
# _process:		set visibility true, is_open true
#
func open():
	self.visible = true
	is_open = true
	
# ------------------------------------------------------------------------------
# close:	set visibility false, is_open false
#
func close():
	self.visible = false
	is_open = false
