extends Panel

@onready var _item_display: Sprite2D = $CenterContainer/Panel/item_display

func update(item: InventoryItem):
	if !item:
		_item_display.visible = false
	else:
		_item_display.visible = true
		_item_display.texture = item.item_texture

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
